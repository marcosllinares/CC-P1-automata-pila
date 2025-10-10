#include "../include/Symbol.hpp"

/**
 * @file Symbol.cpp
 * @brief Implementación de la clase Symbol
 *
 * `Symbol` representa un símbolo (cadena) utilizado en alfabetos, estados
 * y en los símbolos apilables del autómata de pila.
 */

/**
 * @brief Constructor por defecto de Symbol
 *
 * Inicializa el símbolo a la cadena vacía.
 */
Symbol::Symbol() : symbol_("") {}

/**
 * @brief Construye un Symbol a partir de un std::string
 *
 * @param symbol Cadena que representa el símbolo
 */
Symbol::Symbol(const std::string &symbol) : symbol_(symbol) {}

/**
 * @brief Construye un Symbol a partir de un carácter
 *
 * Útil para crear símbolos de un solo carácter.
 *
 * @param symbol Carácter a almacenar como símbolo
 */
Symbol::Symbol(char symbol) : symbol_(1, symbol) {}

/**
 * @brief Constructor de copia
 */
Symbol::Symbol(const Symbol &other) : symbol_(other.symbol_) {}

/**
 * @brief Operador de asignación
 */
Symbol &Symbol::operator=(const Symbol &other) {
  if (this != &other) {
    symbol_ = other.symbol_;
  }
  return *this;
}

/**
 * @brief Operador de comparación (para std::set)
 */
bool Symbol::operator<(const Symbol &other) const {
  return symbol_ < other.symbol_;
}

/**
 * @brief Operador de igualdad
 */
bool Symbol::operator==(const Symbol &other) const {
  return symbol_ == other.symbol_;
}

/**
 * @brief Operador de desigualdad
 */
bool Symbol::operator!=(const Symbol &other) const {
  return symbol_ != other.symbol_;
}

/**
 * @brief Obtiene la representación en std::string del símbolo
 * @return const std::string& Referencia a la cadena interna
 */
const std::string &Symbol::getValue() const { return symbol_; }

/**
 * @brief Asigna un nuevo valor al símbolo
 * @param symbol Nueva cadena para el símbolo
 */
void Symbol::setValue(const std::string &symbol) { symbol_ = symbol; }

/**
 * @brief Convierte el símbolo a std::string
 * @return std::string Copia de la cadena interna
 */
std::string Symbol::toString() const { return symbol_; }
