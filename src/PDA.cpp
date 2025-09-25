#include "../include/PDA.hpp"

PDA::PDA() {}

PDA::PDA(const PDA &other) 
  : mode_(other.mode_),
    states_(other.states_),
    chainAlphabet_(other.chainAlphabet_),
    stackAlphabet_(other.stackAlphabet_),
    initialState_(other.initialState_),
    initialStackSymbol_(other.initialStackSymbol_),
    finals_(other.finals_),
    transitions_(other.transitions_) {}
