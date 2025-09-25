#include "../include/Alphabet.hpp"

Alphabet::Alphabet() {}

/**
 * @brief Construct a new Alphabet:: Alphabet object
 * Constructor a parti de un std::string.
 *
 * @param word
 */
Alphabet::Alphabet(std::string word) {
  for (char c : word) {
    // Separados por un espacio
    if (c != ' ')
      alphabet_.insert(Symbol(c));
  }
}

bool Alphabet::BelongsToAlphabet(const Symbol& symbol) {
  return alphabet_.find(symbol) != alphabet_.end();
}
