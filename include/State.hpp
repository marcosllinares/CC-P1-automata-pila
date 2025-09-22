#pragma once

#include "Types.hpp"
#include <string>
#include <unordered_set>

namespace pda {

// Forward declarations
class Transition;

class State {
public:
    State() = default;
    explicit State(StateId id);

    // Observers
    const StateId& id() const noexcept;

    // Mutators
    void setId(StateId id);

private:
    StateId id_{};
};

} // namespace pda
