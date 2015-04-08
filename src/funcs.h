#pragma once
#include <vector>
#include <string>

class Funcs {
public:
  Funcs();
  ~Funcs();
  std::vector<std::string> split(const std::string&, char);
};
