#pragma once

#include "PDA.hpp"
#include <string>
#include <vector>

class PDA;

// Parser for the provided input file format.
class Parser {
public:
  Parser();

  // Parse a PDA from a file
  PDA parseFromFile(const std::string &filename);

private:
  // Helper methods
  std::vector<std::string> split(const std::string &str, char delimiter);
  std::string trim(const std::string &str);
  bool isComment(const std::string &line);
};
