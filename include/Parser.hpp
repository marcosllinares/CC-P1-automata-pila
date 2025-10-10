#pragma once

#include "PDA.hpp"
#include <string>
#include <string>
#include <vector>

class PDA;

// Parser for PDA files and input strings files.
class Parser {
public:
  Parser();

  // Parse a PDA from a definition file (antes parseFromFile)
  PDA parsePDAFromFile(const std::string &filename);

  // Parse input strings from a file: devuelve vector con cada línea
  // no vacía y sin comentarios. Cada línea representa una cadena de entrada.
  std::vector<std::string> parseInputFromFile(const std::string &filename);

private:
  // Helper methods
  std::vector<std::string> split(const std::string &str, char delimiter);
  std::string trim(const std::string &str);
  bool isComment(const std::string &line);
};
