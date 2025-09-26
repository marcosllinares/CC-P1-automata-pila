#pragma once

#include "Alphabet.hpp"
#include "State.hpp"
#include "Transition.hpp"
#include "Symbol.hpp"
#include <set>
#include <string>
#include <vector>

enum class AcceptanceMode { EmptyStack, FinalState };

const Symbol BLANK(".");

// High-level PDA simulator interface
class PDA {
public:
  PDA();
  PDA(const PDA &other);

  // Setters (after parsing)
  void setAcceptanceMode(AcceptanceMode mode);
  void setChainAlphabet(const Alphabet& sigma);
  void setStackAlphabet(const Alphabet& gamma);
  void setStates(const std::set<State>& states);
  void setInitialState(const Symbol& q0);
  void setInitialStackSymbol(const Symbol& Z0);
  void setFinalStates(const std::set<State>& finals);
  void addTransition(const Transition& t);

  // Getters
  AcceptanceMode acceptanceMode() const noexcept;
  const Alphabet& chainAlphabet() const noexcept;
  const Alphabet& stackAlphabet() const noexcept;
  const std::set<State>& states() const noexcept;
  const Symbol& initialState() const noexcept;
  const Symbol& initialStackSymbol() const noexcept;
  const std::set<State>& finalStates() const noexcept;
  const std::vector<Transition>& transitions() const noexcept;

  // Simulation
  // bool accepts(const std::string& word) const;

private:
  AcceptanceMode mode_{AcceptanceMode::FinalState};
  std::set<State> states_{}; // Q
  Alphabet chainAlphabet_{};         // Σ
  Alphabet stackAlphabet_{};         // Γ
  Symbol initialState_{};
  Symbol initialStackSymbol_{};
  std::set<State> finals_{};              // F
  std::vector<Transition> transitions_{}; // δ
};
