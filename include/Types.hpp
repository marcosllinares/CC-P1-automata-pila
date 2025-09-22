#pragma once

#include <string>
#include <unordered_set>
#include <unordered_map>
#include <vector>
#include <optional>
#include <iosfwd>

namespace pda {

// Single-character input and stack symbols by spec; store as char for Σ, Γ.
using Symbol = char;        // elements of Σ and Γ
using StateId = std::string; // names like q0, q1, ...

// Special epsilon marker used in files as '.' but parsed to '\0' here,
// leaving actual '.' available if needed.
constexpr Symbol EPSILON = '\0';

// Acceptance mode: by empty stack (APv) or final state (APf)
enum class AcceptanceMode { EmptyStack, FinalState };

// Forward declarations
class Transition;
class PDA;
class Parser;
class TraceLogger;

} // namespace pda
