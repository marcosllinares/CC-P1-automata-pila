#pragma once

#include "State.hpp"
#include <string>

// Transition representation for PDA:
// (q_from, input_symbol in Σ ∪ {ε}, stack_pop_symbol in Γ) -> (q_to, stack_push_symbol in Γ*)
class Transition {
public:
  Transition();
  Transition(std::string word);
  Transition(State q_from, char input_symbol, char stack_pop_symbol, State q_to, char stack_push_symbol)
    : q_from_(q_from),
      input_symbol_(input_symbol),
      stack_pop_symbol_(stack_pop_symbol),
      q_to_(q_to),
      stack_push_symbol_(stack_push_symbol) {}

private:
  State q_from_;
  char input_symbol_;
  char stack_pop_symbol_;
  State q_to_;
  char stack_push_symbol_;
};
