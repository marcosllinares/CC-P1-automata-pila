#pragma once

#include <string>

// Declaraciones adelantadas
class Transition;

class State {
public:
  State();
  State(const std::string &id) : id_(id) {}

  std::string GetId() const { return id_; }
  void SetId(const std::string &id) { id_ = id; }

  // Operadores de comparación para uso en std::set
  bool operator<(const State &other) const { return id_ < other.id_; }
  bool operator==(const State &other) const { return id_ == other.id_; }

private:
  std::string id_;
};
