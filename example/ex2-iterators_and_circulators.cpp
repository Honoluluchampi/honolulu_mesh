#include <OpenMesh/Core/IO/MeshIO.hh>
#include <OpenMesh/Core/Mesh/TriMesh_ArrayKernelT.hh>

//lib
#include <utility.hpp>

// std
#include <iostream>
#include <vector>
#include <string>

using MyMesh = OpenMesh::TriMesh_ArrayKernelT<>;

int main(int argc, char **argv)
{
  MyMesh mesh;
  if (!OpenMesh::IO::read_mesh(mesh, std::string(std::getenv("HNLL_MODEL_DIR")) + "/" + argv[2]))
    std::cerr << "cannnot read mesh" << std::endl;

  // storage for the computed centers of gravity
  std::vector<MyMesh::Point> cogs;
  std::vector<MyMesh::Point>::iterator cog_it;
  cogs.reserve(mesh.n_vertices());

  // smmoting mesh argv[1] times
  MyMesh::VertexIter v_it, v_end(mesh.vertices_end());
  MyMesh::VertexVertexIter vv_it;
  // store barycenter point
  MyMesh::Point cog;
  MyMesh::Scalar valence;
  unsigned int i, N(atoi(argv[1]));

  for (i=0; i < N; ++i) {
    cogs.clear();
    // reputate for all vertices
    for (v_it = mesh.vertices_begin(); v_it != v_end; ++v_it) {
      // first point
      cog[0] = cog[1] = cog[2] = valence = 0.0f;
    
      for (vv_it = mesh.vv_iter(*v_it); vv_it.is_valid(); ++vv_it) {
        cog += mesh.point(*vv_it);
        ++valence;
      }
      cogs.push_back(cog/valence);
    }
    for (v_it = mesh.vertices_begin(), cog_it = cogs.begin(); v_it != v_end; ++v_it, ++cog_it) {
      if (!mesh.is_boundary(*v_it))
        mesh.set_point(*v_it, *cog_it);
    }
  }

  // write
  if (!OpenMesh::IO::write_mesh(mesh, std::string(std::getenv("HNLL_MODEL_DIR")) + "/processed/" + getFileName(std::string(argv[2]))))
    std::cerr << "cannot write mesh" << std::endl;
}