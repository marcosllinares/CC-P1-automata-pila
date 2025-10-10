#include "../include/State.hpp"

/**
 * @file State.cpp
 * @brief Implementación mínima de la clase State
 *
 * Este archivo contiene la implementación del constructor por defecto de
 * `State`. El tipo `State` encapsula un identificador (`Symbol`) que
 * representa el nombre del estado.
 */

/**
 * @brief Constructor por defecto de State
 *
 * Inicializa el identificador del estado con un `Symbol` vacío.
 */
State::State() : id_(Symbol()) {}
