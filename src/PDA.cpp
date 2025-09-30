#include "../include/PDA.hpp"

PDA::PDA() {}

PDA::PDA(const PDA &other)
    : mode_(other.mode_), states_(other.states_), chainAlphabet_(other.chainAlphabet_), stackAlphabet_(other.stackAlphabet_),
      initialState_(other.initialState_), initialStackSymbol_(other.initialStackSymbol_), finals_(other.finals_),
      transitions_(other.transitions_) {}

std::vector<Transition> PDA::GetPosibleTransitions(State q_actual, Symbol string_input_symbol_actual, Symbol stack_pop_symbol_actual) {
  std::vector<Transition> posible_transitions;
  for (int i = 0; i < transitions_.size(); i++) {
    if (q_actual == transitions_[i].getFromState() && 
        stack_pop_symbol_actual == transitions_[i].getStackPopSymbol() &&
        (string_input_symbol_actual == transitions_[i].getInputSymbol() || transitions_[i].getInputSymbol() == BLANK)) {
      posible_transitions.push_back(transitions_[i]);
    }
  }
  // Si cambio el criterio de que estado decido probar primero tengo que ordenar
  // este vector
  return posible_transitions;
}


bool PDA::accepts_recursive(std::string input_string, int position_input_string, State actual_state, std::stack<Symbol> actual_stack){

  if (position_input_string == input_string.length()) {
    if (mode_ == AcceptanceMode::FinalState) {
      // return finals_.find(actual_state); 
    }
    // else { //AcceptanceMode::EmptyStack
    // }
  }

  if (actual_stack.empty()) {
    // return false; //??
  }

  Symbol actual_input_string = input_string[position_input_string];
  Symbol actual_top_stack_symbol = actual_stack.top();
  std::vector<Transition> actual_posible_transitions = GetPosibleTransitions(actual_state, actual_input_string, actual_top_stack_symbol);
  
  // Me quedé por el punto 4.

  return false;
}

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

const Symbol &PDA::initialStackSymbol() const noexcept { return initialStackSymbol_; }

const std::set<State> &PDA::finalStates() const noexcept { return finals_; }

const std::vector<Transition> &PDA::transitions() const noexcept { return transitions_; }
