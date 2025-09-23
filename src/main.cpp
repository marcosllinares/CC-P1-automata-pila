#include <iostream>
#include <string>
#include <optional>
#include <fstream>

#include "Types.hpp"
#include "Parser.hpp"
#include "PDA.hpp"
#include "TraceLogger.hpp"

int main(int argc, char** argv) {
    std::cout << "PDA Simulator (skeleton)\n";
    std::cout << "Usage: ./pda <definition_file> [--trace] [--mode=APv|APf]" << std::endl;
    return 0;
}
