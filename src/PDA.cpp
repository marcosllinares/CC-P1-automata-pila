#include "../include/PDA.hpp"

PDA::PDA() {}

PDA::PDA(const PDA &other)
    : mode_(other.mode_), states_(other.states_),
      chainAlphabet_(other.chainAlphabet_),
      stackAlphabet_(other.stackAlphabet_), initialState_(other.initialState_),
      initialStackSymbol_(other.initialStackSymbol_), finals_(other.finals_),
      transitions_(other.transitions_) {}

// Configuration setters
void PDA::setAcceptanceMode(AcceptanceMode mode) { mode_ = mode; }

void PDA::setChainAlphabet(const Alphabet &sigma) { chainAlphabet_ = sigma; }

void PDA::setStackAlphabet(const Alphabet &gamma) { stackAlphabet_ = gamma; }

void PDA::setStates(const std::set<State> &states) { states_ = states; }

void PDA::setInitialState(const Symbol &q0) { initialState_ = q0; }

void PDA::setInitialStackSymbol(const Symbol &Z0) { initialStackSymbol_ = Z0; }

void PDA::setFinalStates(const std::set<State> &finals) { finals_ = finals; }

void PDA::addTransition(const Transition &t) { transitions_.push_back(t); }

// Getters
AcceptanceMode PDA::acceptanceMode() const noexcept { return mode_; }

const Alphabet &PDA::chainAlphabet() const noexcept { return chainAlphabet_; }

const Alphabet &PDA::stackAlphabet() const noexcept { return stackAlphabet_; }

const std::set<State> &PDA::states() const noexcept { return states_; }

const Symbol &PDA::initialState() const noexcept { return initialState_; }

const Symbol &PDA::initialStackSymbol() const noexcept {
  return initialStackSymbol_;
}

const std::set<State> &PDA::finalStates() const noexcept { return finals_; }

const std::vector<Transition> &PDA::transitions() const noexcept {
  return transitions_;
}
