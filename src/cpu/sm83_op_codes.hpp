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
 * @brief Adds a number to a SM83 register
 *
 * @param state The SM83 state object to operate on
 * @param reg_getter The getter for the register value
 * @param reg_setter The setter for the register value
 * @param value The value to add to the register
 * @post F register is updated with CPU flags
 */
void AddToRegister(SM83State* state, uint8_t (SM83State::*reg_getter)(), void (SM83State::*reg_setter)(uint8_t), uint8_t value);

/**
 * @brief Adds a number to a 16bit SM83 register
 *
 * @param state The SM83 state object to operate on
 * @param reg_getter The getter for the register value
 * @param reg_setter The setter for the register value
 * @param value The value to add to the register
 * @post F register is updated with CPU flags. H and C carry flags are updated
 */
void AddToRegister(SM83State* state, uint16_t (SM83State::*reg_getter)(), void (SM83State::*reg_setter)(uint16_t), uint16_t value);

/**
 * @brief Subtracts a number from a SM83 register
 *
 * @param state The SM83 state object to operate on
 * @param reg_getter The getter for the register value
 * @param reg_setter The setter for the register value
 * @param value The value to subtract from the register
 * @post F register is updated with CPU flags
 */
void SubFromRegister(SM83State* state, uint8_t (SM83State::*reg_getter)(), void (SM83State::*reg_setter)(uint8_t), uint8_t value);

/**
 * @brief Rotates the provided register to the right
 *
 * @param state The SM83 State to operate on
 * @param reg_getter The getter for the register to rotate
 * @param reg_setter The setter for the register to rotate
 * @param through_carry A value indicating whether or not the carry flag rotates into the register
 */
void RotateRight(SM83State* state, uint8_t (SM83State::*reg_getter)(), void (SM83State::*reg_setter)(uint8_t), bool through_carry);

/**
 * @brief Rotates the provided register to the left
 *
 * @param state The SM83 State to operate on
 * @param reg_getter The getter for the register to rotate
 * @param reg_setter The setter for the register to rotate
 * @param through_carry A value indicating whether or not the carry flag rotates into the register
 */
void RotateLeft(SM83State* state, uint8_t (SM83State::*reg_getter)(), void (SM83State::*reg_setter)(uint8_t), bool through_carry);
/**
 * @brief NOP
 *
 * Moves the program counter forward 1 byte
 *
 * @param state The SM83 State to operate on
 * @return uint8_t The number of CPU cycles
 */
uint8_t Execute00(SM83State* state);

/**
 * @brief LD BC, d16 - Load the immediate 2 bytes in memory after the program counter into BC
 *
 * @param state The current state to operate on
 * @return uint8_t The number of cpu cycles to perform operation (12)
 */
uint8_t Execute01(SM83State* state);

/**
 * @brief LD DE, d16 - Load the immediate 2 bytes in memory after the program counter into DE
 *
 * @param state The current state to operate on
 * @return uint8_t The number of cpu cycles to perform operation (12)
 */
uint8_t Execute11(SM83State* state);

/**
 * @brief LD HL, d16 - Load the immediate 2 bytes in memory after the program counter into HL
 *
 * @param state The current state to operate on
 * @return uint8_t The number of cpu cycles to perform operation (12)
 */
uint8_t Execute21(SM83State* state);

/**
 * @brief LD (BC), A - Load the 8bit value stored in register A into memory at the address stored in BC
 *
 * @param state The current state to operate on
 * @return uint8_t The number of cpu cycles to perform operation (8)
 */
uint8_t Execute02(SM83State* state);

/**
 * @brief LD (DE), A - Load the 8bit value stored in register A into memory at the address stored in DE
 *
 * @param state The current state to operate on
 * @return uint8_t The number of cpu cycles to perform operation (8)
 */
uint8_t Execute12(SM83State* state);

/**
 * @brief LD (HL+), A - Load the 8bit value stored in register A into memory at the address stored in HL
 *
 * @param state The current state to operate on
 * @return uint8_t The number of cpu cycles to perform operation (8)
 * @post HL = HL + 1
 */
uint8_t Execute22(SM83State* state);

/**
 * @brief INC BC - Increment BC by one
 *
 * @param state The current state to operate on
 * @return uint8_t The number of cpu cycles to perform operation (8)
 */
uint8_t Execute03(SM83State* state);

/**
 * @brief INC DE - Increment DE by one
 *
 * @param state The current state to operate on
 * @return uint8_t The number of cpu cycles to perform operation (8)
 */
uint8_t Execute13(SM83State* state);

/**
 * @brief INC HL - Increment HL by one
 *
 * @param state The current state to operate on
 * @return uint8_t The number of cpu cycles to perform operation (8)
 */
uint8_t Execute23(SM83State* state);

/**
 * @brief INC B - Increment B by one
 *
 * @param state The current state to operate on
 * @return uint8_t The number of cpu cycles to perform operation (4)
 * @post Z, H, N flags set by function. C flag unaffected.
 */
uint8_t Execute04(SM83State* state);

/**
 * @brief INC D - Increment D by one
 *
 * @param state The current state to operate on
 * @return uint8_t The number of cpu cycles to perform operation (4)
 * @post Z, H, N flags set by function. C flag unaffected.
 */
uint8_t Execute14(SM83State* state);

/**
 * @brief INC H - Increment H by one
 *
 * @param state The current state to operate on
 * @return uint8_t The number of cpu cycles to perform operation (4)
 * @post Z, H, N flags set by function. C flag unaffected.
 */
uint8_t Execute24(SM83State* state);

/**
 * @brief DEC B - Decrement B by one
 *
 * @param state The current state to operate on
 * @return uint8_t The number of cpu cycles to perform operation (4)
 * @post Z, H, N flags set by function. C flag unaffected.
 */
uint8_t Execute05(SM83State* state);

/**
 * @brief DEC D - Decrement D by one
 *
 * @param state The current state to operate on
 * @return uint8_t The number of cpu cycles to perform operation (4)
 * @post Z, H, N flags set by function. C flag unaffected.
 */
uint8_t Execute15(SM83State* state);

/**
 * @brief DEC H - Decrement H by one
 *
 * @param state The current state to operate on
 * @return uint8_t The number of cpu cycles to perform operation (4)
 * @post Z, H, N flags set by function. C flag unaffected.
 */
uint8_t Execute25(SM83State* state);

/**
 * @brief LD B, d8 - Loads the immediate 8 bits after the PC into the B register
 *
 * @param state The current state to operate on
 * @return uint8_t The number of cpu cycles to perform operation (8)
 */
uint8_t Execute06(SM83State* state);

/**
 * @brief LD D, d8 - Loads the immediate 8 bits after the PC into the D register
 *
 * @param state The current state to operate on
 * @return uint8_t The number of cpu cycles to perform operation (8)
 */
uint8_t Execute16(SM83State* state);

/**
 * @brief LD H, d8 - Loads the immediate 8 bits after the PC into the D register
 *
 * @param state The current state to operate on
 * @return uint8_t The number of cpu cycles to perform operation (8)
 */
uint8_t Execute26(SM83State* state);

/**
 * @brief RLCA - Rotates the accumulator to the left
 *
 * @param state The current state to operate on
 * @return uint8_t The number of cpu cycles to perform operation (4)
 * @post Z, H, N flags set to 0. C flag set by function.
 */
uint8_t Execute07(SM83State* state);

/**
 * @brief RLA - Rotates the accumulator to the left through the carry flag
 *
 * @param state The current state to operate on
 * @return uint8_t The number of cpu cycles to perform operation (4)
 * @post Z, H, N flags set to 0. C flag set by function.
 */
uint8_t Execute17(SM83State* state);

/**
 * @brief LD (a16), SP - Put the stack pointer into the next two bytes
 * @param state The current state to operate on
 * @return uint8_t The number of cpu cycles to perform operation (20)
 */
uint8_t Execute08(SM83State* state);

/**
 * @brief JR r8 - relative jump to PC + signed digit. PC=PC+/-r8
 * @param state The current state to operate on
 * @return uint8_t The number of cpu cycles to perform operation (12)
 */
uint8_t Execute18(SM83State* state);

/**
 * @brief ADD HL, BC - Add register BC to HL
 * @param state The current state to operate on
 * @return uint8_t The number of cpu cycles to perform operation (8)
 */
uint8_t Execute09(SM83State* state);

/**
 * @brief ADD HL, DE - Add register DE to HL
 * @param state The current state to operate on
 * @return uint8_t The number of cpu cycles to perform operation (8)
 */
uint8_t Execute19(SM83State* state);

/**
 * @brief LD A, (BC) - Load the value at address BC into register A
 * @param state The current state to operate on
 * @return uint8_t The number of cpu cycles to perform operation (8)
 */
uint8_t Execute0A(SM83State* state);

/**
 * @brief LD A, (DE) - Load the value at address DE into register A
 * @param state The current state to operate on
 * @return uint8_t The number of cpu cycles to perform operation (8)
 */
uint8_t Execute1A(SM83State* state);

/**
 * @brief DEC BC - Decrement Register BC by 1
 * @param state The current state to operate on
 * @return uint8_t The number of cpu cycles to perform operation (8)
 */
uint8_t Execute0B(SM83State* state);

/**
 * @brief DEC DE - Decrement Register DE by 1
 * @param state The current state to operate on
 * @return uint8_t The number of cpu cycles to perform operation (8)
 */
uint8_t Execute1B(SM83State* state);

/**
 * @brief INC C - Increment C by one
 * @param state The current state to operate on
 * @return uint8_t The number of cpu cycles to perform operation (4)
 */
uint8_t Execute0C(SM83State* state);

/**
 * @brief INC E - Increment E by one
 * @param state The current state to operate on
 * @return uint8_t The number of cpu cycles to perform operation (4)
 */
uint8_t Execute1C(SM83State* state);

/**
 * @brief DEC C - Decrement C by one
 * @param state The current state to operate on
 * @return uint8_t The number of cpu cycles to perform operation (4)
 */
uint8_t Execute0D(SM83State* state);

/**
 * @brief DEC E - Decrement D by one
 * @param state The current state to operate on
 * @return uint8_t The number of cpu cycles to perform operation (4)
 */
uint8_t Execute1D(SM83State* state);

/**
 * @brief LD C, d8 - Load immediate 8 bits into register C
 * @param state The current state to operate on
 * @return uint8_t The number of cpu cycles to perform operation (8)
 */
uint8_t Execute0E(SM83State* state);

/**
 * @brief LD E, d8 - Load immediate 8 bits into register E
 * @param state The current state to operate on
 * @return uint8_t The number of cpu cycles to perform operation (8)
 */
uint8_t Execute1E(SM83State* state);

/**
 * @brief RRCA - Rotates the accumulator to the right
 *
 * @param state The current state to operate on
 * @return uint8_t The number of cpu cycles to perform operation (4)
 * @post Z, H, N flags set to 0. C flag set by function.
 */
uint8_t Execute0F(SM83State* state);

/**
 * @brief RRA - Rotates the accumulator to the right through the carry flag
 *
 * @param state The current state to operate on
 * @return uint8_t The number of cpu cycles to perform operation (4)
 * @post Z, H, N flags set to 0. C flag set by function.
 */
uint8_t Execute1F(SM83State* state);

/**
 * @brief JR NZ, r8 - Conditional relative jump if the zero flag is not set
 *
 * @param state The current state to operate on
 * @return uint8_t The number of cpu cycles to perform operation. 12 if jump, 8 otherwise
 * @post PC = PC + r8
 */
uint8_t Execute20(SM83State* state);

/**
 * @brief DAA - Decimal adjust accumulator.
 *
 * The DAA instruction adjusts the results of a binary addition or subtraction (as stored in the accumulator and flags)
 * to retroactively turn it into a BCD addition or subtraction. It does so by adding or subtracting 6 from the result's upper nybble,
 * lower nybble, or both.
 *
 * @param state The current state to operate on
 * @return uint8_t The number of cpu cycles to perform operation (4).
 * @post F flags are set as needed
 */
uint8_t Execute27(SM83State* state);

#endif