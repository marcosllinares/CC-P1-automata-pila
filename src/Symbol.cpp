#include "../include/Symbol.hpp"

Symbol::Symbol() : symbol_("") {}

Symbol::Symbol(const std::string& symbol) : symbol_(symbol) {}

Symbol::Symbol(char symbol) : symbol_(1, symbol) {}

Symbol::Symbol(const Symbol& other) : symbol_(other.symbol_) {}

Symbol& Symbol::operator=(const Symbol& other) {
  if (this != &other) {
    symbol_ = other.symbol_;
  }
  return *this;
}

bool Symbol::operator<(const Symbol& other) const {
  return symbol_ < other.symbol_;
}

bool Symbol::operator==(const Symbol& other) const {
  return symbol_ == other.symbol_;
}

bool Symbol::operator!=(const Symbol& other) const {
  return symbol_ != other.symbol_;
}

const std::string& Symbol::getValue() const {
  return symbol_;
}

void Symbol::setValue(const std::string& symbol) {
  symbol_ = symbol;
}

std::string Symbol::toString() const {
  return symbol_;
}