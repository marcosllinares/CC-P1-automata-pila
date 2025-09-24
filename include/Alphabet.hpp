#pragma once

#include <string>
#include <unordered_set>

class Alphabet {
public:
  Alphabet();
  Alphabet(std::string);
  int GetSize() { return alphabet_.size(); }
  Alphabet GetInstance() { return *this; }
  std::unordered_set<char> GetAlphabet() { return alphabet_; }
  bool BelongsToAlphabet(char);

private:
  std::unordered_set<char> alphabet_;
};

