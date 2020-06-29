/**
 * @brief Definitions for C++ implementation of all SM83 Op Codes
 *
 */

#ifndef SM83_OP_CODES_H
#define SM83_OP_CODES_H

#include <iostream>
#include "./sm83_state.hpp"

using namespace std;

/**
 * @brief NOP
 *
 * Moves the program counter forward 1 byte
 *
 * @param state The SM83 State to operate on
 * @return uint8_t The number of CPU cycles
 */
uint8_t Execute00(SM83State* state);

#endif