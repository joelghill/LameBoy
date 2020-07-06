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

void AddToRegister(SM83State* state, uint16_t (SM83State::*reg_getter)(), void (SM83State::*reg_setter)(uint16_t), uint16_t value) {

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

    if ((new_reg_value & 0x00FF) < (reg_value & 0x00FF)) {
        f_flag = f_flag | C_FLAG;
    } else {
        f_flag = f_flag & NOT_C_FLAG;
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

void RotateRight(SM83State* state, uint8_t (SM83State::*reg_getter)(), void (SM83State::*reg_setter)(uint8_t), bool through_carry) {
    // Z, N, H, and C will all be zero to start
    uint8_t f_flag = 0b00000000;

    // Get the register value to rotate
    uint8_t reg_value = ((*state).*reg_getter)();

    // Shift to the right 1 bit
    uint8_t new_reg_value = reg_value >> 1;

    // If the least sig bit was set, CY is set as well
    if ((reg_value & 0b00000001) > 0) {
        f_flag = f_flag | C_FLAG;
    }

    // If we are rotating through the C flag....
    if (through_carry == true) {
        // ... and the C flag was set...
        if (state->cFlag() == true) {
            // ... then the most sig fig in the register is set as well
            new_reg_value = new_reg_value | 0b10000000;
        }
    // Otherwise the previous least sig fig is set to the most sig fig
    } else if ((reg_value & 0b00000001) > 0) {
        new_reg_value = new_reg_value | 0b10000000;
    }

    if (new_reg_value == 0) {
        f_flag = f_flag | Z_FLAG;
    }

    ((*state).*reg_setter)(new_reg_value);
    state->setF(f_flag);
}

void RotateLeft(SM83State* state, uint8_t (SM83State::*reg_getter)(), void (SM83State::*reg_setter)(uint8_t), bool through_carry) {
    // Z, N, H, and C will all be zero to start
    uint8_t f_flag = 0b00000000;

    // Get the register value to rotate
    uint8_t reg_value = ((*state).*reg_getter)();

    // Shift to the right 1 bit
    uint8_t new_reg_value = reg_value << 1;

    // If the most sig bit was set, CY is set as well
    if ((reg_value & 0b10000000) > 0) {
        f_flag = f_flag | C_FLAG;
    }

    // If we are rotating through the C flag....
    if (through_carry == true) {
        // ... and the C flag was set...
        if (state->cFlag() == true) {
            // ... then the least sig fig in the register is set as well
            new_reg_value = new_reg_value | 0b00000001;
        }
    // Otherwise the least sig fig is set to the previous least sig fig
    } else if ((reg_value & 0b10000000) > 0) {
        new_reg_value = new_reg_value | 0b00000001;
    }

    if (new_reg_value == 0) {
        f_flag = f_flag | Z_FLAG;
    }

    ((*state).*reg_setter)(new_reg_value);
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

uint8_t Execute11(SM83State* state) {
    uint8_t d = state->MemoryAt(state->programCounter() + 1);
    uint8_t e = state->MemoryAt(state->programCounter() + 2);

    state->setD(d);
    state->setE(e);
    state->IncrementProgramCounter(3);

    return 12;
}

uint8_t Execute21(SM83State* state) {
    uint8_t h = state->MemoryAt(state->programCounter() + 1);
    uint8_t l = state->MemoryAt(state->programCounter() + 2);

    state->setH(h);
    state->setL(l);
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

uint8_t Execute12(SM83State* state) {
    uint8_t a = state->a();
    uint16_t de = state->de();

    state->SetMemoryAt(de, a);
    state->IncrementProgramCounter(1);

    return 8;
}

uint8_t Execute22(SM83State* state) {
    uint8_t a = state->a();
    uint16_t hl = state->hl();

    state->SetMemoryAt(hl, a);
    state->setHL(hl + 1);
    state->IncrementProgramCounter(1);

    return 8;
}

uint8_t Execute03(SM83State* state) {
    uint16_t bc = state->bc();
    state->setBC(bc + 1);
    state->IncrementProgramCounter(1);

    return 8;
}

uint8_t Execute13(SM83State* state) {
    uint16_t de = state->de();
    state->setDE(de + 1);
    state->IncrementProgramCounter(1);

    return 8;
}

uint8_t Execute23(SM83State* state) {
    uint16_t hl = state->hl();
    state->setHL(hl + 1);
    state->IncrementProgramCounter(1);

    return 8;
}

uint8_t Execute04(SM83State* state) {
    AddToRegister(state, &SM83State::b, &SM83State::setB, 1);
    state->IncrementProgramCounter(1);
    return 4;
}

uint8_t Execute14(SM83State* state) {
    AddToRegister(state, &SM83State::d, &SM83State::setD, 1);
    state->IncrementProgramCounter(1);
    return 4;
}

uint8_t Execute24(SM83State* state) {
    AddToRegister(state, &SM83State::h, &SM83State::setH, 1);
    state->IncrementProgramCounter(1);
    return 4;
}

uint8_t Execute05(SM83State* state) {
    SubFromRegister(state, &SM83State::b, &SM83State::setB, 1);
    state->IncrementProgramCounter(1);
    return 4;
}

uint8_t Execute15(SM83State* state) {
    SubFromRegister(state, &SM83State::d, &SM83State::setD, 1);
    state->IncrementProgramCounter(1);
    return 4;
}

uint8_t Execute25(SM83State* state) {
    SubFromRegister(state, &SM83State::h, &SM83State::setH, 1);
    state->IncrementProgramCounter(1);
    return 4;
}

uint8_t Execute06(SM83State* state) {
    uint8_t data = state->MemoryAt(state->programCounter() + 1);
    state->setB(data);

    state->IncrementProgramCounter(2);
    return 8;
}

uint8_t Execute16(SM83State* state) {
    uint8_t data = state->MemoryAt(state->programCounter() + 1);
    state->setD(data);

    state->IncrementProgramCounter(2);
    return 8;
}

uint8_t Execute26(SM83State* state) {
    uint8_t data = state->MemoryAt(state->programCounter() + 1);
    state->setH(data);

    state->IncrementProgramCounter(2);
    return 8;
}

uint8_t Execute07(SM83State* state) {
    RotateLeft(state, &SM83State::a, &SM83State::setA, false);
    state->IncrementProgramCounter(1);
    return 4;
}

uint8_t Execute17(SM83State* state) {
    RotateLeft(state, &SM83State::a, &SM83State::setA, true);
    state->IncrementProgramCounter(1);
    return 4;
}

uint8_t Execute08(SM83State* state) {
    uint16_t pc = state->programCounter();
    uint16_t sp = state->stackPointer();

    uint8_t sp_a = (uint8_t)((sp | 0b11110000) >> 8);
    uint8_t sp_b = (uint8_t)(sp);

    state->SetMemoryAt(pc + 1, sp_a);
    state->SetMemoryAt(pc + 2, sp_b);

    state->IncrementProgramCounter(3);
    return 20;
}

uint8_t Execute18(SM83State* state) {
    uint16_t pc = state->programCounter();
    int8_t r8 = (int8_t)state->MemoryAt(pc + 1);

    state->setProgramCounter((uint16_t)(pc + r8));
    return 12;
}

uint8_t Execute09(SM83State* state) {
    uint16_t bc = state->bc();
    AddToRegister(state, &SM83State::hl, &SM83State::setHL, bc);

    state->IncrementProgramCounter(1);
    return 8;
}

uint8_t Execute19(SM83State* state) {
    uint16_t de = state->de();
    AddToRegister(state, &SM83State::hl, &SM83State::setHL, de);

    state->IncrementProgramCounter(1);
    return 8;
}

uint8_t Execute0A(SM83State* state) {
    uint16_t bc = state->bc();
    uint8_t value = state->MemoryAt(bc);

    state->setA(value);
    state->IncrementProgramCounter(1);
    return 8;
}

uint8_t Execute1A(SM83State* state) {
    uint16_t de = state->de();
    uint8_t value = state->MemoryAt(de);

    state->setA(value);
    state->IncrementProgramCounter(1);
    return 8;
}

uint8_t Execute0B(SM83State* state) {
    uint16_t bc = state->bc();
    state->setBC(bc - 1);
    state->IncrementProgramCounter(1);

    return 8;
}

uint8_t Execute1B(SM83State* state) {
    uint16_t de = state->de();
    state->setDE(de - 1);
    state->IncrementProgramCounter(1);

    return 8;
}

uint8_t Execute0C(SM83State* state) {
    AddToRegister(state, &SM83State::c, &SM83State::setC, 1);
    state->IncrementProgramCounter(1);\
    return 4;
}

uint8_t Execute1C(SM83State* state) {
    AddToRegister(state, &SM83State::e, &SM83State::setE, 1);
    state->IncrementProgramCounter(1);\
    return 4;
}

uint8_t Execute0D(SM83State* state) {
    SubFromRegister(state, &SM83State::c, &SM83State::setC, 1);
    state->IncrementProgramCounter(1);
    return 4;
}

uint8_t Execute1D(SM83State* state) {
    SubFromRegister(state, &SM83State::e, &SM83State::setE, 1);
    state->IncrementProgramCounter(1);
    return 4;
}

uint8_t Execute0E(SM83State* state) {
    uint8_t data = state->MemoryAt(state->programCounter() + 1);
    state->setC(data);

    state->IncrementProgramCounter(2);
    return 8;
}

uint8_t Execute1E(SM83State* state) {
    uint8_t data = state->MemoryAt(state->programCounter() + 1);
    state->setE(data);

    state->IncrementProgramCounter(2);
    return 8;
}

uint8_t Execute0F(SM83State* state) {
    RotateRight(state, &SM83State::a, &SM83State::setA, false);
    state->IncrementProgramCounter(1);
    return 4;
}

uint8_t Execute1F(SM83State* state) {
    RotateRight(state, &SM83State::a, &SM83State::setA, true);
    state->IncrementProgramCounter(1);
    return 4;
}

uint8_t Execute20(SM83State* state) {
    bool nc = state->zFlag() == false;
    uint16_t pc = state->programCounter();

    // If the zero flag is not set, jump to address in the next 8 bits.
    if (nc == true) {
        int8_t address = state->MemoryAt(pc + 1);
        state->setProgramCounter(pc + address);
        return 12;
    }
    else {
        state->setProgramCounter(pc + 2);
        return 8;
    }
}

uint8_t Execute27(SM83State* state) {

    uint8_t a = state->a();
    uint f = state->f();

    bool z_flag = state->zFlag();
    bool c_flag = state->cFlag();
    bool h_flag = state->hFlag();

    if (state->nFlag() == false) {
        // after an addition, adjust if (half-)carry occurred or if result is out of bounds
        if (c_flag || a > 0x99) {
            state->setA(a += 0x60);
            f = f | C_FLAG;
        }
        if (h_flag || (a & 0x0f) > 0x09) {
            a += 0x6;
        }
    } else {  // after a subtraction, only adjust if (half-)carry occurred
        if (c_flag) {
            a -= 0x60;
        }
        if (h_flag) {
            a -= 0x6;
        }
    }
    // these flags are always updated
    if (a == 0) {
        f = f | Z_FLAG;
    } else {
        f = f & NOT_Z_FLAG;
    }
    // h flag is always cleared
    f = f & NOT_H_FLAG;

    // Write the new registers
    state->setA(a);
    state->setF(f);
}