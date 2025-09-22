#include <iostream>
#include <string>
#include <optional>
#include <fstream>

#include "pda/Types.hpp"
#include "pda/Parser.hpp"
#include "pda/PDA.hpp"
#include "pda/TraceLogger.hpp"

int main(int argc, char** argv) {
    std::cout << "PDA Simulator (skeleton)\n";
    std::cout << "Usage: ./pda <definition_file> [--trace] [--mode=APv|APf]" << std::endl;
    return 0;
}
