/**
 * @brief Implementation of all SM83 Op Codes
 *
 */

#include <iostream>
#include "./sm83_op_codes.hpp"
#include "./sm83_state.hpp"

using namespace std;

// Runs for 4 cycles and moves program counter forward 1 byte
// No other side effects
uint8_t Execute00(SM83State* state) {
    state->IncrementProgramCounter(1);
    return 4;
}
