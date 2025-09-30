#pragma once

#include "State.hpp"
#include "Symbol.hpp"
#include <string>
#include <vector>

// Transition representation for PDA:
// (q_from, input_symbol in Σ ∪ {ε}, stack_pop_symbol in Γ) -> (q_to,
// stack_push_symbols in Γ*)
class Transition {
public:
  Transition();
  Transition(const State &q_from, const Symbol &input_symbol,
             const Symbol &stack_pop_symbol, const State &q_to,
             const std::vector<Symbol> &stack_push_symbols)
      : q_from_(q_from), input_symbol_(input_symbol),
        stack_pop_symbol_(stack_pop_symbol), q_to_(q_to),
        stack_push_symbols_(stack_push_symbols) {}

  // Getters
  const State &getFromState() const { return q_from_; }
  const Symbol &getInputSymbol() const { return input_symbol_; }
  const Symbol &getStackPopSymbol() const { return stack_pop_symbol_; }
  const State &getToState() const { return q_to_; }
  const std::vector<Symbol> &getStackPushSymbols() const {
    return stack_push_symbols_;
  }

private:
  State q_from_;
  Symbol input_symbol_;
  Symbol stack_pop_symbol_;
  State q_to_;
  std::vector<Symbol> stack_push_symbols_; // Can push multiple symbols
};
