#include <string>

static std::string getFileName(const std::string& str)
{
  std::string res;
  auto it = str.end() - 1;
  for (it; it != str.begin(); it--) {
    if (*it == '/') break;
  }

  if (it - 1 == str.begin()) return str;
  
  for (it++; it != str.end(); it++) {
    res.push_back(*it);
  }
  return res;
}