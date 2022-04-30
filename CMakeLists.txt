# c++20 is available in version 3.16 or later
cmake_minimum_required(VERSION 3.16)

project(honolulu_mesh VERSION 1.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(app main.cpp)

set(OPEN_MESH_LIB_DIR $ENV{OPEN_MESH_DIR}/build/Build/lib)
set(OPEN_MESH_INCLUDE_DIR $ENV{OPEN_MESH_DIR}/src/)

target_include_directories(app PUBLIC
  ${OPEN_MESH_INCLUDE_DIR}
)

target_link_directories(app PUBLIC
  ${OPEN_MESH_LIB_DIR}
)

target_link_libraries(app PUBLIC 
  OpenMeshCore
  OpenMeshTools
)