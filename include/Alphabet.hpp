#pragma once

#include "Symbol.hpp"
#include <string>
#include <set>

class Alphabet {
public:
  Alphabet();
  Alphabet(std::string);
  int GetSize() { return alphabet_.size(); }
  Alphabet GetInstance() { return *this; }
  std::set<Symbol> GetAlphabet() { return alphabet_; }
  bool BelongsToAlphabet(const Symbol& symbol);

private:
  std::set<Symbol> alphabet_;
};

