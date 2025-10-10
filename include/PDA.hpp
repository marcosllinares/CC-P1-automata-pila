#pragma once

#include "Alphabet.hpp"
#include "State.hpp"
#include "Symbol.hpp"
#include "Transition.hpp"
#include <set>
#include <stack>
#include <string>
#include <vector>

enum class AcceptanceMode { EmptyStack, FinalState };

const Symbol BLANK(".");

// Interfaz de simulador de PDA de alto nivel
class PDA {
public:
  PDA();
  PDA(const PDA &other);

  // Setters (after parsing)
  void setAcceptanceMode(AcceptanceMode mode);
  void setChainAlphabet(const Alphabet &sigma);
  void setStackAlphabet(const Alphabet &gamma);
  void setStates(const std::set<State> &states);
  void setInitialState(const Symbol &q0);
  void setInitialStackSymbol(const Symbol &Z0);
  void setFinalStates(const std::set<State> &finals);
  void addTransition(const Transition &t);

  // Getters
  AcceptanceMode acceptanceMode() const noexcept;
  const Alphabet &chainAlphabet() const noexcept;
  const Alphabet &stackAlphabet() const noexcept;
  const std::set<State> &states() const noexcept;
  const Symbol &initialState() const noexcept;
  const Symbol &initialStackSymbol() const noexcept;
  const std::set<State> &finalStates() const noexcept;
  const std::vector<Transition> &transitions() const noexcept;

  std::vector<Transition> GetPosibleTransitions(State q_actual, Symbol input_actual, Symbol stack_pop_symbol_actual);
  // Simulacion
  bool accepts_recursive(std::string input_string, int input_string_position, State actual_state, std::stack<Symbol>);

private:
  AcceptanceMode mode_{AcceptanceMode::FinalState};
  std::set<State> states_{}; // Q
  Alphabet chainAlphabet_{}; // Σ
  Alphabet stackAlphabet_{}; // Γ
  Symbol initialState_{};
  Symbol initialStackSymbol_{};
  std::set<State> finals_{};              // F
  std::vector<Transition> transitions_{}; // δ
};
