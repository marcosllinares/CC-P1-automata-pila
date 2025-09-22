#pragma once

#include "pda/Types.hpp"
#include "pda/State.hpp"
#include "pda/Transition.hpp"
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <optional>

namespace pda {

// High-level PDA simulator interface (no implementation here).
class PDA {
public:
    PDA();

    // Configuration setters (after parsing)
    void setAcceptanceMode(AcceptanceMode mode);
    void setAlphabet(const std::unordered_set<Symbol>& sigma);
    void setStackAlphabet(const std::unordered_set<Symbol>& gamma);
    void setStates(const std::unordered_set<StateId>& states);
    void setInitialState(const StateId& q0);
    void setInitialStackSymbol(Symbol Z0);
    void setFinalStates(const std::unordered_set<StateId>& finals);
    void addTransition(const Transition& t);

    // Queries
    AcceptanceMode acceptanceMode() const noexcept;
    const std::unordered_set<Symbol>& alphabet() const noexcept;
    const std::unordered_set<Symbol>& stackAlphabet() const noexcept;
    const std::unordered_set<StateId>& states() const noexcept;
    const StateId& initialState() const noexcept;
    Symbol initialStackSymbol() const noexcept;
    const std::unordered_set<StateId>& finalStates() const noexcept;
    const std::vector<Transition>& transitions() const noexcept;

    // Simulation (deferred)
    bool accepts(const std::string& word) const;

private:
    AcceptanceMode mode_{AcceptanceMode::EmptyStack};
    std::unordered_set<Symbol> sigma_{};
    std::unordered_set<Symbol> gamma_{};
    std::unordered_set<StateId> states_{};
    StateId q0_{};
    Symbol z0_{};
    std::unordered_set<StateId> finals_{};
    std::vector<Transition> transitions_{};
};

} // namespace pda
