#include <fstream>
#include <iostream>

#include "../include/PDA.hpp"
#include "../include/Parser.hpp"
#include "../include/TraceLogger.hpp"

void printPDAStatus(const PDA& pda, bool trace, std::string filename) {
  std::cout << "Successfully parsed PDA from file: " << filename << std::endl;

  // Display basic information about the parsed PDA
  std::cout << "\n=== PDA Information ===" << std::endl;
  std::cout << "Acceptance Mode: "
            << (pda.acceptanceMode() == AcceptanceMode::FinalState
                    ? "Final State"
                    : "Empty Stack")
            << std::endl;

  std::cout << "States: " << pda.states().size() << std::endl;
  std::cout << "Initial State: " << pda.initialState().getValue() << std::endl;
  std::cout << "Initial Stack Symbol: " << pda.initialStackSymbol().getValue()
            << std::endl;

  std::cout << "Final States: ";
  for (const auto &state : pda.finalStates()) {
    std::cout << state.GetId().getValue() << " ";
  }
  std::cout << std::endl;

  std::cout << "Input Alphabet Size: " << pda.chainAlphabet().GetSize()
            << std::endl;
  std::cout << "Stack Alphabet Size: " << pda.stackAlphabet().GetSize()
            << std::endl;
  std::cout << "Transitions: " << pda.transitions().size() << std::endl;

  if (trace) {
    std::cout << "\n=== Transitions ===" << std::endl;
    for (const auto &transition : pda.transitions()) {
      std::cout << "(" << transition.getFromState().GetId().getValue() << ", "
                << transition.getInputSymbol().getValue() << ", "
                << transition.getStackPopSymbol().getValue() << ") -> ("
                << transition.getToState().GetId().getValue() << ", ";

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

int main(int argc, char **argv) {
  std::cout << "PDA Simulator\n";

  // Usage ()
  if (argc < 2) {
    std::cout << "Usage: ./bin/pda <definition_file> [--trace] [--mode=APv|APf]"
              << std::endl;
    return 1;
  }


  std::string filename = argv[1];
  bool trace = false;
  std::string mode = "APf"; // Default mode

  // Parse command line arguments
  for (int i = 2; i < argc; i++) {
    std::string arg = argv[i];
    if (arg == "--trace") {
      trace = true;
    } else if (arg.substr(0, 7) == "--mode=") {
      mode = arg.substr(7);
    }
  }

  try {
    // Create parser and parse the PDA
    Parser parser;
    PDA pda = parser.parseFromFile(filename);

    printPDAStatus(pda, trace, filename);
    return 0;

  } catch (const std::exception &e) {
    std::cerr << "Error: " << e.what() << std::endl;
    return 1;
  }
}

