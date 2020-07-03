/**
 * @brief Implementation of all SM83 Op Codes
 *
 */

#include <iostream>
#include "./sm83_op_codes.hpp"
#include "./sm83_state.hpp"

using namespace std;

void AddToRegister(SM83State* state, uint8_t (SM83State::*reg_getter)(), void (SM83State::*reg_setter)(uint8_t), uint8_t value) {

    bool h = false;
    bool z = false;

    uint8_t reg_value = ((*state).*reg_getter)();
    uint8_t new_reg_value = reg_value + value;
    ((*state).*reg_setter)(new_reg_value);

    // Set the H flag
    uint8_t f_flag = state->f();

    if (new_reg_value < reg_value) {
        f_flag = f_flag | H_FLAG;
    } else {
        f_flag = f_flag & NOT_H_FLAG;
    }

    // Set the Z flag
    if (new_reg_value == 0) {
        f_flag = f_flag | Z_FLAG;
    } else {
        f_flag = f_flag & NOT_Z_FLAG;
    }

    // Set N to 0
    f_flag = f_flag & NOT_N_FLAG;

    state->setF(f_flag);
}

void SubFromRegister(SM83State* state, uint8_t (SM83State::*reg_getter)(), void (SM83State::*reg_setter)(uint8_t), uint8_t value) {
    bool h = false;
    bool z = false;

    uint8_t reg_value = ((*state).*reg_getter)();
    uint8_t new_reg_value = reg_value - value;
    ((*state).*reg_setter)(new_reg_value);

    // Set the H flag
    uint8_t f_flag = state->f();

    if (new_reg_value > reg_value) {
        f_flag = f_flag | H_FLAG;
    } else {
        f_flag = f_flag & NOT_H_FLAG;
    }

    // Set the Z flag
    if (new_reg_value == 0) {
        f_flag = f_flag | Z_FLAG;
    } else {
        f_flag = f_flag & NOT_Z_FLAG;
    }

    // Set N to 0
    f_flag = f_flag | N_FLAG;

    state->setF(f_flag);
}

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
    AddToRegister(state, &SM83State::b, &SM83State::setB, 1);
    state->IncrementProgramCounter(1);
    return 4;
}

uint8_t Execute05(SM83State* state) {
    SubFromRegister(state, &SM83State::b, &SM83State::setB, 1);
    state->IncrementProgramCounter(1);
    return 4;
}

uint8_t Execute06(SM83State* state) {
    uint8_t data = state->MemoryAt(state->programCounter() + 1);
    state->setB(data);

    state->IncrementProgramCounter(2);
    return 8;
}