#pragma once

#include "Alphabet.hpp"
#include "State.hpp"
#include "Transition.hpp"
#include <set>
#include <string>
#include <vector>

enum class AcceptanceMode { EmptyStack, FinalState };

const char BLANK = '.';

// High-level PDA simulator interface
class PDA {
public:
  PDA();
  PDA(const PDA &other);

  // Configuration setters (after parsing)
  // void setAcceptanceMode(AcceptanceMode mode);
  // void setAlphabet(const std::set<Symbol>& sigma);
  // void setStackAlphabet(const std::set<Symbol>& gamma);
  // void setStates(const std::set<StateId>& states);
  // void setInitialState(const StateId& q0);
  // void setInitialStackSymbol(Symbol Z0);
  // void setFinalStates(const std::set<StateId>& finals);
  // void addTransition(const Transition& t);

  // Queries
  // AcceptanceMode acceptanceMode() const noexcept;
  // const std::set<Symbol>& alphabet() const noexcept;
  // const std::set<Symbol>& stackAlphabet() const noexcept;
  // const std::set<StateId>& states() const noexcept;
  // const StateId& initialState() const noexcept;
  // Symbol initialStackSymbol() const noexcept;
  // const std::set<StateId>& finalStates() const noexcept;
  // const std::vector<Transition>& transitions() const noexcept;

  // Simulation (deferred)
  // bool accepts(const std::string& word) const;

private:
  AcceptanceMode mode_{AcceptanceMode::FinalState};
  std::set<State> states_{}; // Q
  Alphabet chainAlphabet_{};         // Σ
  Alphabet stackAlphabet_{};         // Γ
  std::string initialState_{};
  char initialStackSymbol_{};
  std::set<State> finals_{};              // F
  std::vector<Transition> transitions_{}; // δ
};
