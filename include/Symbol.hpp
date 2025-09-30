#pragma once

#include <string>

class Symbol {
public:
  Symbol();
  Symbol(const std::string &symbol);
  Symbol(char symbol);
  Symbol(const Symbol &other);

  // Assignment operator
  Symbol &operator=(const Symbol &other);

  // Comparison operators for std::set usage
  bool operator<(const Symbol &other) const;
  bool operator==(const Symbol &other) const;
  bool operator!=(const Symbol &other) const;

  // Getters
  const std::string &getValue() const;

  // Setters
  void setValue(const std::string &symbol);

  // Conversion to string
  std::string toString() const;

private:
  std::string symbol_;
};
