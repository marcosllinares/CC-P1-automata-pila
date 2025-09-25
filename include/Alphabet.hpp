#pragma once

#include "Symbol.hpp"
#include <string>
#include <set>

class Alphabet {
public:
  Alphabet();
  Alphabet(std::string);
  int GetSize() const { return alphabet_.size(); }
  Alphabet GetInstance() const { return *this; }
  std::set<Symbol> GetAlphabet() const { return alphabet_; }
  bool BelongsToAlphabet(const Symbol& symbol) const;

private:
  std::set<Symbol> alphabet_;
};

