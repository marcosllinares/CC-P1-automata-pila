#include "../include/Parser.hpp"
#include "../include/Alphabet.hpp"
#include "../include/PDA.hpp"
#include "../include/State.hpp"
#include "../include/Symbol.hpp"
#include "../include/Transition.hpp"
#include <algorithm>
#include <fstream>
#include <iostream>
#include <set>
#include <sstream>
#include <vector>

Parser::Parser() {}

/**
 * @brief Parsea un archivo de definición de PDA y construye un objeto PDA
 *
 * El formato esperado del archivo es el siguiente (línea por línea, se
 * permiten comentarios que comiencen con '#'):
 * 1) Lista de estados (separados por espacios)
 * 2) Alfabeto de entrada (símbolos separados por espacios)
 * 3) Alfabeto de pila (símbolos separados por espacios)
 * 4) Estado inicial
 * 5) Símbolo inicial de la pila
 * 6) Estados finales (separados por espacios)
 * 7+) Transiciones, una por línea con el formato:
 *    origen símbolo_entrada símbolo_a_desapilar destino símbolos_a_apilar
 *
 * Nota: Este método lanza std::runtime_error si encuentra errores de formato
 * o si no puede abrir el archivo.
 *
 * @param filename Ruta al fichero de definición del autómata.
 * @return PDA Objeto PDA construido a partir del fichero.
 */
PDA Parser::parseFromFile(const std::string &filename) {
  std::ifstream file(filename);
  if (!file.is_open()) {
    throw std::runtime_error("Cannot open file: " + filename);
  }

  PDA pda;
  std::string line;
  int lineNumber = 0;

  // Skip comments and empty lines to get to actual data
  auto getNextDataLine = [&]() -> std::string {
    while (std::getline(file, line)) {
      lineNumber++;
      line = trim(line);
      if (!line.empty() && !isComment(line)) {
        return line;
      }
    }
    return "";
  };

  try {
    // Line 1: States
    line = getNextDataLine();
    if (line.empty())
      throw std::runtime_error("Missing states definition");

    std::vector<std::string> stateNames = split(line, ' ');
    std::set<State> states;
    for (const auto &stateName : stateNames) {
      states.insert(State(Symbol(stateName)));
    }
    pda.setStates(states);

    // Line 2: Input alphabet
    line = getNextDataLine();
    if (line.empty())
      throw std::runtime_error("Missing input alphabet definition");

    Alphabet chainAlphabet(line);
    pda.setChainAlphabet(chainAlphabet);

    // Line 3: Stack alphabet
    line = getNextDataLine();
    if (line.empty())
      throw std::runtime_error("Missing stack alphabet definition");

    Alphabet stackAlphabet(line);
    pda.setStackAlphabet(stackAlphabet);

    // Line 4: Initial state
    line = getNextDataLine();
    if (line.empty())
      throw std::runtime_error("Missing initial state definition");

    pda.setInitialState(Symbol(trim(line)));

    // Line 5: Initial stack symbol
    line = getNextDataLine();
    if (line.empty())
      throw std::runtime_error("Missing initial stack symbol definition");

    pda.setInitialStackSymbol(Symbol(trim(line)));

    // Line 6: Final states
    line = getNextDataLine();
    if (line.empty())
      throw std::runtime_error("Missing final states definition");

    std::vector<std::string> finalStateNames = split(line, ' ');
    std::set<State> finalStates;
    for (const auto &stateName : finalStateNames) {
      finalStates.insert(State(Symbol(stateName)));
    }
    pda.setFinalStates(finalStates);

    // Remaining lines: Transitions
    while ((line = getNextDataLine()) != "") {
      std::vector<std::string> parts = split(line, ' ');
      if (parts.size() != 5) {
        throw std::runtime_error("Invalid transition format at line " +
                                 std::to_string(lineNumber));
      }

      State fromState{Symbol(parts[0])};
      Symbol inputSymbol{parts[1]};
      Symbol stackPopSymbol{parts[2]};
      State toState{Symbol(parts[3])};

      // Parse stack push symbols (can be multiple symbols or empty)
      std::vector<Symbol> stackPushSymbols;
      std::string pushString = parts[4];
      if (pushString != ".") { // "." represents epsilon (empty)
        for (char c : pushString) {
          stackPushSymbols.push_back(Symbol(std::string(1, c)));
        }
      }

      Transition transition{fromState, inputSymbol, stackPopSymbol, toState,
                            stackPushSymbols};
      pda.addTransition(transition);
    }

    // Set acceptance mode to FinalState (APf format)
    pda.setAcceptanceMode(AcceptanceMode::FinalState);

  } catch (const std::exception &e) {
    throw std::runtime_error("Parse error at line " +
                             std::to_string(lineNumber) + ": " + e.what());
  }

  return pda;
}

/**
 * @brief Divide una cadena en tokens separados por un delimitador
 *
 * Este método elimina espacios alrededor de cada token y descarta
 * tokens vacíos resultantes.
 *
 * @param str Cadena a dividir
 * @param delimiter Carácter delimitador
 * @return std::vector<std::string> Vector con los tokens encontrados
 */
std::vector<std::string> Parser::split(const std::string &str, char delimiter) {
  std::vector<std::string> tokens;
  std::stringstream ss(str);
  std::string token;

  while (std::getline(ss, token, delimiter)) {
    token = trim(token);
    if (!token.empty()) {
      tokens.push_back(token);
    }
  }

  return tokens;
}

/**
 * @brief Elimina espacios en blanco al inicio y final de una cadena
 *
 * @param str Cadena a limpiar
 * @return std::string Cadena recortada
 */
std::string Parser::trim(const std::string &str) {
  size_t start = str.find_first_not_of(" \t\r\n");
  if (start == std::string::npos)
    return "";

  size_t end = str.find_last_not_of(" \t\r\n");
  return str.substr(start, end - start + 1);
}

/**
 * @brief Comprueba si una línea es un comentario
 *
 * Una línea se considera comentario si está vacía o comienza por '#'.
 *
 * @param line Línea a comprobar
 * @return true Si la línea es comentario
 * @return false Si la línea no es comentario
 */
bool Parser::isComment(const std::string &line) {
  return line.empty() || line[0] == '#';
}
