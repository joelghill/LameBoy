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

uint8_t Execute01(SM83State* state) {
    uint8_t b = state->MemoryAt(state->programCounter() + 1);
    uint8_t c = state->MemoryAt(state->programCounter() + 2);

    state->setB(b);
    state->setC(c);
    state->IncrementProgramCounter(3);

    return 12;
}

uint8_t Execute02(SM83State* state) {
    uint8_t a = state->a();
    uint16_t bc = state->bc();

    state->SetMemoryAt(bc, a);
    state->IncrementProgramCounter(1);

    return 8;
}

uint8_t Execute03(SM83State* state) {
    uint16_t bc = state->bc();
    state->setBC(bc + 1);
    state->IncrementProgramCounter(1);

    return 8;
}

uint8_t Execute04(SM83State* state) {
    bool h = false;
    bool z = false;
    uint8_t b = state->b();
    uint8_t inc_b = b + 1;

    state->setB(inc_b);
    state->IncrementProgramCounter(1);

    uint8_t f = state->f();

    // Set the H flag
    if (inc_b < b) {
        f = f | H_FLAG;
    } else {
        f = f & NOT_H_FLAG;
    }

    // Set the Z flag
    if (inc_b == 0) {
        f = f | Z_FLAG;
    } else {
        f = f & NOT_Z_FLAG;
    }

    // Set N to 0
    f = f & NOT_N_FLAG;

    state->setF(f);
    return 4;
}
