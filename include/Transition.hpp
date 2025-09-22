#pragma once

#include "Types.hpp"
#include <string>
#include <vector>
#include <utility>

namespace pda {

// Transition representation for PDA:
// (q_from, input_symbol in Σ ∪ {ε}, stack_pop_symbol in Γ) -> (q_to, stack_push_string in Γ*)
class Transition {
public:
    Transition();
    Transition(StateId from, Symbol input, Symbol stackTop, StateId to, std::vector<Symbol> pushSeq);

    // Accessors
    const StateId& from() const noexcept;
    const StateId& to() const noexcept;
    Symbol input() const noexcept;
    Symbol stackTop() const noexcept;
    const std::vector<Symbol>& pushSeq() const noexcept;

private:
    StateId from_{};
    Symbol input_{EPSILON};
    Symbol stackTop_{};
    StateId to_{};
    std::vector<Symbol> pushSeq_{}; // topmost element is at back or front? define in implementation/README
};

} // namespace pda
