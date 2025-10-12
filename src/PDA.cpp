#include "../include/PDA.hpp"
#include <stdexcept>
#include <sstream>
#include <iostream>

/**
 * @file PDA.cpp
 * @brief Implementación de la clase PDA (autómata de pila)
 *
 * Contiene constructores, búsqueda de transiciones posibles, la
 * función recursiva de aceptación y los setters/getters básicos.
 */

/**
 * @brief Constructor por defecto de PDA
 */
PDA::PDA() {}

/**
 * @brief Constructor de copia de PDA
 *
 * Copia los atributos principales del autómata.
 *
 * @param other PDA a copiar
 */
PDA::PDA(const PDA &other)
    : mode_(other.mode_), states_(other.states_), chainAlphabet_(other.chainAlphabet_), stackAlphabet_(other.stackAlphabet_),
      initialState_(other.initialState_), initialStackSymbol_(other.initialStackSymbol_), finals_(other.finals_),
      transitions_(other.transitions_) {}

/**
 * @brief Obtiene las transiciones aplicables desde un estado dado
 *
 * Recorre la lista de transiciones y devuelve aquellas cuyo estado de
 * origen coincide con `q_actual`, cuyo símbolo a desapilar coincide con
 * `stack_pop_symbol_actual` y cuyo símbolo de entrada coincide con
 * `string_input_symbol_actual` o es la marca de epsilon (BLANK).
 *
 * @param q_actual Estado actual desde el que buscar transiciones
 * @param string_input_symbol_actual Símbolo actual de la cadena de entrada
 * @param stack_pop_symbol_actual Símbolo que debe coincidir con el tope de la pila
 * @return std::vector<Transition> Vector con las transiciones aplicables
 */
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

/**
 * @brief Función recursiva que prueba si el autómata acepta una cadena
 *
 * Implementa un algoritmo de backtracking: para la configuración actual
 * (estado, posición en la cadena, pila) obtiene las transiciones
 * aplicables, aplica cada una (modificando estado/pila/posición) y llama
 * recursivamente. Si alguna rama conduce a una configuración de aceptación
 * devuelve true.
 *
 * @param input_string Cadena de entrada a procesar (se copia internamente)
 * @param position_input_string Índice de la posición actual en la cadena
 * @param actual_state Estado actual del autómata
 * @param actual_stack Pila actual (se copia internamente)
 * @param trace Si es true, imprime información de trazado
 * @return true Si la cadena es aceptada desde esta configuración
 * @return false En caso contrario
 */
bool PDA::accepts_recursive(std::string input_string, int position_input_string, State actual_state, std::stack<Symbol> actual_stack, bool trace) {
  // Inicializar control de iteraciones y conjunto de configuraciones visitadas
  std::set<std::string> visited;
  int iterationsLeft = maxIterations_;
  return accepts_recursive_impl(input_string, position_input_string, actual_state, actual_stack, visited, iterationsLeft, trace);
}

// Helper recursivo con control de iteraciones y detección de configuraciones repetidas
bool PDA::accepts_recursive_impl(const std::string &input_string, int position_input_string, State actual_state, std::stack<Symbol> actual_stack,
                                 std::set<std::string> &visited, int &iterationsLeft, bool trace) {
  // Control de iteraciones global
  if (iterationsLeft <= 0) {
    return false;
  }
  --iterationsLeft;

  // Serializar configuración (estado|posición|pila)
  std::ostringstream oss;
  oss << actual_state.GetId() << "|" << position_input_string << "|";
  // Serializar pila desde el tope hacia abajo (top-first)
  std::stack<Symbol> tmp = actual_stack;
  while (!tmp.empty()) {
    oss << tmp.top().toString();
    tmp.pop();
    if (!tmp.empty()) oss << ",";
  }
  std::string config = oss.str();

  // Si ya visitamos esta configuración, evitar bucle infinito
  if (visited.find(config) != visited.end()) {
    return false;
  }
  visited.insert(config);

  // Si hemos consumido toda la cadena, comprobamos aceptación por estado final
  if (position_input_string >= (int)input_string.length()) {
    if (mode_ == AcceptanceMode::FinalState && finals_.find(actual_state) != finals_.end()) {
      return true;
    }
    // Nota: no retornamos inmediatamente si no estamos en estado final;
    // debemos seguir explorando transiciones epsilon que podrían
    // llevar a un estado final (epsilon-closure).
  }

  // Caso: pila vacía => no hay transiciones posibles que necesiten desapilar
  if (actual_stack.empty()) {
    return false;
  }

  // Símbolo de entrada actual: si estamos al final de la cadena usar BLANK
  Symbol actual_input_string_symbol = (position_input_string >= (int)input_string.length()) ? BLANK
                                                                                         : Symbol(input_string[position_input_string]);
  Symbol actual_top_stack_symbol = actual_stack.top();

  // Obtener transiciones aplicables (incluye transiciones epsilon)
  std::vector<Transition> actual_posible_transitions =
      GetPosibleTransitions(actual_state, actual_input_string_symbol, actual_top_stack_symbol);

  for (const auto &transition : actual_posible_transitions) {
    State new_state = transition.getToState();
    std::stack<Symbol> new_stack = actual_stack;
    new_stack.pop();
    std::vector<Symbol> symbols_to_stack = transition.getStackPushSymbols();
    if (!symbols_to_stack.empty()) {
      for (auto it = symbols_to_stack.rbegin(); it != symbols_to_stack.rend(); ++it) {
        new_stack.push(*it);
      }
    }

    int new_position = (transition.getInputSymbol() == BLANK) ? position_input_string : position_input_string + 1;

    // Imprimir información de traza si está habilitada
    if (trace) {
      printTrace(actual_state, position_input_string, actual_input_string_symbol, 
                 actual_top_stack_symbol, transition, new_stack);
    }

    if (accepts_recursive_impl(input_string, new_position, new_state, new_stack, visited, iterationsLeft, trace)) {
      return true;
    }
    // Seguimos probando otras transiciones
  }

  return false;
}

/**
 * @name Configuration setters
 * Métodos para configurar el autómata tras el parseo.
 */
//@{
void PDA::setAcceptanceMode(AcceptanceMode mode) { mode_ = mode; }

void PDA::setChainAlphabet(const Alphabet &sigma) { chainAlphabet_ = sigma; }

void PDA::setStackAlphabet(const Alphabet &gamma) { stackAlphabet_ = gamma; }

void PDA::setStates(const std::set<State> &states) { states_ = states; }

void PDA::setInitialState(const Symbol &q0) { initialState_ = q0; }

void PDA::setInitialStackSymbol(const Symbol &Z0) { initialStackSymbol_ = Z0; }

void PDA::setFinalStates(const std::set<State> &finals) { finals_ = finals; }

void PDA::addTransition(const Transition &t) { transitions_.push_back(t); }
//@}

/**
 * @name Consultores (getters)
 */
//@{
AcceptanceMode PDA::acceptanceMode() const noexcept { return mode_; }

const Alphabet &PDA::chainAlphabet() const noexcept { return chainAlphabet_; }

const Alphabet &PDA::stackAlphabet() const noexcept { return stackAlphabet_; }

const std::set<State> &PDA::states() const noexcept { return states_; }

const Symbol &PDA::initialState() const noexcept { return initialState_; }

const Symbol &PDA::initialStackSymbol() const noexcept { return initialStackSymbol_; }

const std::set<State> &PDA::finalStates() const noexcept { return finals_; }

const std::vector<Transition> &PDA::transitions() const noexcept { return transitions_; }
//@}

// Control de seguridad: setters/getters para maxIterations_
void PDA::setMaxIterations(int maxIter) { maxIterations_ = maxIter; }

int PDA::maxIterations() const noexcept { return maxIterations_; }

// Valida que los atributos del autómata pertenezcan a los alfabetos/estados
// Lanza std::runtime_error si encuentra alguna inconsistencia
void PDA::validatePDA() const {
  // initial state debe pertenecer a states_
  if (states_.find(State(initialState_.toString())) == states_.end()) {
    throw std::runtime_error("Initial state '" + initialState_.toString() + "' is not declared in states");
  }

  // initial stack symbol debe pertenecer al alfabeto de pila
  if (!stackAlphabet_.BelongsToAlphabet(initialStackSymbol_)) {
    throw std::runtime_error("Initial stack symbol '" + initialStackSymbol_.toString() + "' is not in the stack alphabet");
  }

  // final states deben pertenecer a states_
  for (const auto &fs : finals_) {
    if (states_.find(fs) == states_.end()) {
      throw std::runtime_error("Final state '" + fs.GetId() + "' is not declared in states");
    }
  }

  // transiciones: comprobar estados y símbolos
  for (const auto &t : transitions_) {
    // estados origen y destino
    if (states_.find(t.getFromState()) == states_.end()) {
      throw std::runtime_error("Transition from-state '" + t.getFromState().GetId() + "' is not declared in states");
    }
    if (states_.find(t.getToState()) == states_.end()) {
      throw std::runtime_error("Transition to-state '" + t.getToState().GetId() + "' is not declared in states");
    }

    // símbolo de entrada: o está en el alfabeto de cadena o es BLANK
    const Symbol &inSym = t.getInputSymbol();
    if (!(inSym == BLANK) && !chainAlphabet_.BelongsToAlphabet(inSym)) {
      throw std::runtime_error("Transition input symbol '" + inSym.toString() + "' is not in the chain alphabet");
    }

    // símbolo a desapilar debe estar en el alfabeto de pila
    if (!stackAlphabet_.BelongsToAlphabet(t.getStackPopSymbol())) {
      throw std::runtime_error("Transition stack-pop symbol '" + t.getStackPopSymbol().toString() + "' is not in the stack alphabet");
    }

    // símbolos a apilar deben pertenecer al alfabeto de pila (si no son BLANK)
    for (const auto &s : t.getStackPushSymbols()) {
      if (s == BLANK) continue;
      if (!stackAlphabet_.BelongsToAlphabet(s)) {
        throw std::runtime_error("Transition stack-push symbol '" + s.toString() + "' is not in the stack alphabet");
      }
    }
  }
}

/**
 * @brief Imprime información detallada sobre la definición del PDA
 * 
 * Muestra la información básica del autómata incluyendo modo de aceptación,
 * estados, alfabetos y opcionalmente las transiciones si trace está activado.
 * 
 * @param trace Si es true, muestra también todas las transiciones
 * @param filename Nombre del archivo de donde se cargó el PDA (opcional)
 */
void PDA::printPDADefinition(bool trace, const std::string& filename) const {
  if (!filename.empty()) {
    std::cout << "\nSuccessfully parsed PDA from file: " << filename << std::endl;
  }

  // Mostrar información básica sobre el PDA analizado
  std::cout << "=== PDA Information ===" << std::endl;
  std::cout << "Acceptance Mode: " << (mode_ == AcceptanceMode::FinalState ? "Final State" : "Empty Stack")
            << std::endl;

  std::cout << "States: {";
  bool first = true;
  for (const auto &state : states_) {
    if (!first) std::cout << ", ";
    std::cout << state.GetId();
    first = false;
  }
  std::cout << "}" << std::endl;

  std::cout << "Initial State: " << initialState_.getValue() << std::endl;
  std::cout << "Initial Stack Symbol: " << initialStackSymbol_.getValue() << std::endl;

  std::cout << "Final States: {";
  first = true;
  for (const auto &state : finals_) {
    if (!first) std::cout << ", ";
    std::cout << state.GetId();
    first = false;
  }
  std::cout << "}" << std::endl;

  std::cout << "Input Alphabet: {";
  first = true;
  for (const auto &symbol : chainAlphabet_.GetAlphabet()) {
    if (!first) std::cout << ", ";
    std::cout << symbol.getValue();
    first = false;
  }
  std::cout << "}" << std::endl;

  std::cout << "Stack Alphabet: {";
  first = true;
  for (const auto &symbol : stackAlphabet_.GetAlphabet()) {
    if (!first) std::cout << ", ";
    std::cout << symbol.getValue();
    first = false;
  }
  std::cout << "}" << std::endl;

  std::cout << "Transitions: " << transitions_.size() << std::endl;

  if (trace) {
    std::cout << "\n=== Transitions ===" << std::endl;
    for (const auto &transition : transitions_) {
      std::cout << "(" << transition.getFromState().GetId() << ", " << transition.getInputSymbol().getValue() << ", "
            << transition.getStackPopSymbol().getValue() << ") -> (" << transition.getToState().GetId() << ", ";

      if (transition.getStackPushSymbols().empty()) {
        std::cout << ".";
      } else {
        for (const auto &symbol : transition.getStackPushSymbols()) {
          std::cout << symbol.getValue();
        }
      }
      std::cout << ")" << std::endl;
    }
  }
}

/**
 * @brief Imprime información de traza de una transición
 * 
 * Muestra el estado actual, la posición en la cadena, el símbolo de entrada,
 * el tope de la pila, la transición aplicada y el estado de la pila después
 * de aplicar la transición.
 * 
 * @param currentState Estado actual del autómata
 * @param position Posición actual en la cadena de entrada
 * @param inputSymbol Símbolo de entrada actual
 * @param stackTop Símbolo del tope de la pila antes de la transición
 * @param transition Transición que se está aplicando
 * @param stackAfter Estado de la pila después de aplicar la transición
 */
void PDA::printTrace(const State& currentState, int position, const Symbol& inputSymbol, 
                     const Symbol& stackTop, const Transition& transition, 
                     const std::stack<Symbol>& stackAfter) const {
  std::cout << "TRACE: Pos=" << position << " | (" << transition.getFromState().GetId() 
            << ", " << transition.getInputSymbol().getValue() 
            << ", " << transition.getStackPopSymbol().getValue() 
            << ") -> (" << transition.getToState().GetId() << ", ";
  
  if (transition.getStackPushSymbols().empty()) {
    std::cout << ".";
  } else {
    for (const auto &symbol : transition.getStackPushSymbols()) {
      std::cout << symbol.getValue();
    }
  }
  
  std::cout << ") | Stack after: [";
  std::stack<Symbol> tempStack = stackAfter;
  std::vector<Symbol> stackContent;
  while (!tempStack.empty()) {
    stackContent.push_back(tempStack.top());
    tempStack.pop();
  }
  
  for (size_t i = 0; i < stackContent.size(); ++i) {
    if (i > 0) std::cout << ", ";
    std::cout << stackContent[i].getValue();
  }
  std::cout << "]" << std::endl;
}
