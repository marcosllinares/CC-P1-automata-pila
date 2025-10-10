#pragma once

#include "PDA.hpp"
#include <string>
#include <string>
#include <vector>

class PDA;

// Parser para archivos de PDA y archivos de cadenas de entrada
class Parser {
public:
  Parser();

  // Analiza un PDA desde un archivo de definición
  PDA parsePDAFromFile(const std::string &filename);

  // Analiza cadenas de entrada desde un archivo
  // Cada línea representa una cadena de entrada
  std::vector<std::string> parseInputFromFile(const std::string &filename);

private:
  std::vector<std::string> split(const std::string &str, char delimiter);
  std::string trim(const std::string &str);
  bool isComment(const std::string &line);
};
