#pragma once

#include "Symbol.hpp"

// Forward declarations
// ? Es necesario
class Transition;

class State {
 public:
  State();
  State(const Symbol& id) : id_(id){}

  Symbol GetId() const { return id_; }
  void SetId(const Symbol& id) { id_ = id; }

  // Comparison operators for std::set usage
  bool operator<(const State& other) const { return id_ < other.id_; }
  bool operator==(const State& other) const { return id_ == other.id_; }

 private:
  Symbol id_;
};


