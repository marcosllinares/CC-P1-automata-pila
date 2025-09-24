#pragma once

#include <string>

// Forward declarations
// ? Es necesario
class Transition;

class State {
 public:
  State();
  State(std::string id) : id_(id){}

  std::string GetId() const { return id_; }
  void SetId(int id) { id_ = id; }

 private:
  std::string id_;
};


