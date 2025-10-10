#include "../include/Alphabet.hpp"

Alphabet::Alphabet() {}

/**
 * @brief Construye un alfabeto a partir de una cadena de caracteres
 *
 * El constructor toma una cadena donde los símbolos están separados por
 * espacios y crea un conjunto de `Symbol`. Por ejemplo, la cadena
 * "a b c" producirá los símbolos 'a', 'b' y 'c' en el alfabeto.
 *
 * @param word Cadena que contiene los símbolos del alfabeto separados por
 * espacios. Los espacios se ignoran.
 */
Alphabet::Alphabet(std::string word) {
  for (char c : word) {
    // Separados por un espacio
    if (c != ' ')
      alphabet_.insert(Symbol(c));
  }
}

/**
 * @brief Consulta si un símbolo pertenece al alfabeto
 *
 * Comprueba si el símbolo dado está presente en el conjunto interno
 * `alphabet_`.
 *
 * @param symbol Símbolo a comprobar.
 * @return true Si el símbolo pertenece al alfabeto.
 * @return false Si el símbolo no pertenece al alfabeto.
 */
bool Alphabet::BelongsToAlphabet(const Symbol& symbol) const {
  return alphabet_.find(symbol) != alphabet_.end();
}
