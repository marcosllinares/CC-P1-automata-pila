#pragma once

#include <string>
#include <set>

class Alphabet {
public:
  Alphabet();
  Alphabet(std::string);
  int GetSize() { return alphabet_.size(); }
  Alphabet GetInstance() { return *this; }
  std::set<char> GetAlphabet() { return alphabet_; }
  bool BelongsToAlphabet(char);

private:
  std::set<char> alphabet_;
};

