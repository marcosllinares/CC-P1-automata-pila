#pragma once

#include "pda/Types.hpp"
#include <iosfwd>
#include <string>
#include <vector>

namespace pda {

// Optional tracing facility to print each step of simulation.
class TraceLogger {
public:
    explicit TraceLogger(std::ostream* out = nullptr);

    void enable(bool on);
    bool enabled() const noexcept;

    // Log helpers (no-op if disabled). Details to be defined in impl.
    void logHeader(const std::string& title) const;
    void logStep(const std::string& state,
                 const std::string& remaining,
                 const std::string& stack,
                 const std::vector<std::string>& availableTransitions) const;

private:
    std::ostream* out_{nullptr};
    bool enabled_{false};
};

} // namespace pda
