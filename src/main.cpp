#include <fstream>
#include <iostream>

#include "../include/PDA.hpp"
#include "../include/Parser.hpp"
#include "../include/TraceLogger.hpp"

int main(int argc, char **argv) {
  std::cout << "PDA Simulator\n";

  // Usage: requiere definición de PDA y archivo de entradas
  if (argc < 3 || argc > 4) {
    std::cout << "Usage: ./bin/pda <definition_file> <inputs_file> [--trace]" << std::endl;
    return 1;
  }

  std::string filename = argv[1];
  std::string inputsFile = argv[2];
  bool trace = false;
  std::string mode = "APf"; // Modo por defecto y único implementado

  // Analizar Flag opcional para trazado
  if (argc == 4 && std::string(argv[3]) == "--trace") {
    trace = true;
  }

  try {
    // Parsear el PDA y las entradas
    Parser parser;
    PDA pda = parser.parsePDAFromFile(filename);
    std::vector<std::string> inputs = parser.parseInputFromFile(inputsFile);
    pda.validatePDA();
    
    if (trace) {
      pda.printPDADefinition(true, filename);
    }

    // Iterar sobre todas las cadenas de entrada y ejecutar la lógica existente por entrada
    for (const auto &input : inputs) {
      std::cout << "\n--- Processing input: " << input << " ---" << std::endl;
      // Preparar pila inicial
      std::stack<Symbol> initial_stack;
      initial_stack.push(pda.initialStackSymbol());
      // Estado inicial
      State init_state(pda.initialState().getValue());

      bool accepted = pda.accepts_recursive(input, 0, init_state, initial_stack, trace);
      std::cout << "Result: " << (accepted ? "ACCEPTED" : "REJECTED") << std::endl;

      // Si trace es true, se podría inicializar TraceLogger y pasar a la simulación
    }
    return 0;

  } catch (const std::exception &e) {
    std::cerr << "Error: " << e.what() << std::endl;
    return 1;
  }
}
