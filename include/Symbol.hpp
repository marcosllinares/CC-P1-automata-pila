#pragma once

#include <string>

class Symbol {
public:
  Symbol();
  Symbol(const std::string &symbol);
  Symbol(char symbol);
  Symbol(const Symbol &other);

  // Operador de asignación
  Symbol &operator=(const Symbol &other);

  // Operadores de comparación para uso en std::set
  bool operator<(const Symbol &other) const;
  bool operator==(const Symbol &other) const;
  bool operator!=(const Symbol &other) const;

  // Getters
  const std::string &getValue() const;

  // Setters
  void setValue(const std::string &symbol);

  // Conversión a string
  std::string toString() const;

private:
  std::string symbol_;
};
