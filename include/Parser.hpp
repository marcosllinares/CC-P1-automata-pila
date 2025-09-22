#pragma once

#include "Types.hpp"
#include <iosfwd>
#include <string>
#include <vector>
#include <optional>

namespace pda {

class PDA;

// Parser for the provided input file format.
class Parser {
public:
    Parser();

    // Parse a PDA definition from input stream.
    // On success, returns a fully configured PDA instance.
    // On failure, returns std::nullopt.
    std::optional<PDA> parse(std::istream& in) const;
};

} // namespace pda
