#include "../include/PDA.hpp"

PDA::PDA() {}

PDA::PDA(const PDA &other)
    : mode_(other.mode_), states_(other.states_), chainAlphabet_(other.chainAlphabet_), stackAlphabet_(other.stackAlphabet_),
      initialState_(other.initialState_), initialStackSymbol_(other.initialStackSymbol_), finals_(other.finals_),
      transitions_(other.transitions_) {}

std::vector<Transition> PDA::GetPosibleTransitions(State q_actual, Symbol string_input_symbol_actual, Symbol stack_pop_symbol_actual) {
  std::vector<Transition> posible_transitions;
  for (int i = 0; i < transitions_.size(); i++) {
    if (q_actual == transitions_[i].getFromState() && stack_pop_symbol_actual == transitions_[i].getStackPopSymbol() &&
        (string_input_symbol_actual == transitions_[i].getInputSymbol() || transitions_[i].getInputSymbol() == BLANK)) {
      posible_transitions.push_back(transitions_[i]);
    }
  }
  // Si cambio el criterio de que estado decido probar primero tengo que ordenar
  // este vector
  return posible_transitions;
}
// Posible mejora:
// std::string input_string se copia en cada recursión
// std::stack<Symbol> actual_stack también se copia
/*
posible solución:
bool PDA::accepts_recursive(const std::string& input_string, int position_input_string, 
                           const State& actual_state, std::stack<Symbol> actual_stack)
*/
bool PDA::accepts_recursive(std::string input_string, int position_input_string, State actual_state, std::stack<Symbol> actual_stack) {
  // Caso base 1: Hemos procesado toda la cadena de entrada
  if (position_input_string == input_string.length()) {
    if (mode_ == AcceptanceMode::FinalState) {
      return finals_.find(actual_state) != finals_.end();
    }
    // NO IMPLEMENTADO
    // else { //AcceptanceMode::EmptyStack
    // }
  }
  // Caso base 2: Pila vacía (generalmente error)
  if (actual_stack.empty()) {
    return false;
  }
  // Posible problema: Acceso fuera de rango
  // Si position_input_string >= input_string.length()
  Symbol actual_input_string_symbol = input_string[position_input_string];
  Symbol actual_top_stack_symbol = actual_stack.top();
  // GetPosibleTransitions se debe encargar de epsilon transiciones
  std::vector<Transition> actual_posible_transitions =
      GetPosibleTransitions(actual_state, actual_input_string_symbol, actual_top_stack_symbol);
  for (auto transition : actual_posible_transitions) {
    State new_state = transition.getToState();
    std::stack<Symbol> new_stack = actual_stack;
    new_stack.pop();
    std::vector<Symbol> symbols_to_stack = transition.getStackPushSymbols();
    // Problema: Si symbols_to_stack está vacío, symbols_to_stack[0] causará crash.
    if (symbols_to_stack[0] != BLANK) {
      // Apila los símbolos en orden inverso
      for (auto it = symbols_to_stack.rbegin(); it != symbols_to_stack.rend(); ++it) {
        new_stack.push(*it);
      }
    }
    // Determinar la nueva posición en la cadena de entrada
    int new_position = (transition.getInputSymbol() == BLANK) ? 
                    position_input_string : position_input_string + 1;
    // Llamada recursiva
    if (accepts_recursive(input_string, new_position, new_state, new_stack)) {
      return true;
    }
    // Si llegamos aquí, esta transición falló
    // El bucle continúa con la siguiente transición
  }

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
