#pragma once

#include <iosfwd>
#include <string>
#include <vector>

// Facilidad opcional de rastreo para imprimir cada paso de la simulación.
class TraceLogger {
public:
  explicit TraceLogger(std::ostream *out = nullptr);

  void enable(bool on);
  bool enabled() const noexcept;

  // Ayudantes de registro (no operan si está desactivado). Detalles a definir en la implementación.
  void logHeader(const std::string &title) const;
  void logStep(const std::string &state, const std::string &remaining,
               const std::string &stack,
               const std::vector<std::string> &availableTransitions) const;

private:
  std::ostream *out_{nullptr};
  bool enabled_{false};
};
