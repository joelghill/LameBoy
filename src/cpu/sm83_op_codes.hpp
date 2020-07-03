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
 * @brief LD (BC), A - Load the 8bit value stored in register A into memory at the address stored in BC
 *
 * @param state The current state to operate on
 * @return uint8_t The number of cpu cycles to perform operation (8)
 */
uint8_t Execute02(SM83State* state);

/**
 * @brief INC BC - Increment BC by one
 *
 * @param state The current state to operate on
 * @return uint8_t The number of cpu cycles to perform operation (8)
 */
uint8_t Execute03(SM83State* state);

/**
 * @brief INC B - Increment B by one
 *
 * @param state The current state to operate on
 * @return uint8_t The number of cpu cycles to perform operation (4)
 * @post Z, H, N flags set by function. C flag unaffected.
 */
uint8_t Execute04(SM83State* state);

/**
 * @brief DEC B - Decrement B by one
 *
 * @param state The current state to operate on
 * @return uint8_t The number of cpu cycles to perform operation (4)
 * @post Z, H, N flags set by function. C flag unaffected.
 */
uint8_t Execute05(SM83State* state);

/**
 * @brief LD B, d8 - Loads the immediate 8 bits after the PC into the B register
 *
 * @param state The current state to operate on
 * @return uint8_t The number of cpu cycles to perform operation (8)
 */
uint8_t Execute06(SM83State* state);

/**
 * @brief RLCA - Rotates the accumulator to the left
 *
 * @param state The current state to operate on
 * @return uint8_t The number of cpu cycles to perform operation (4)
 * @post Z, H, N flags set to 0. C flag set by function.
 */
uint8_t Execute07(SM83State* state);

/**
 * @brief LD (a16), SP - Put the stack pointer into the next two bytes
 * @param state The current state to operate on
 * @return uint8_t The number of cpu cycles to perform operation (20)
 */
uint8_t Execute08(SM83State* state);

/**
 * @brief ADD HL, BC - Add register BC to HL
 * @param state The current state to operate on
 * @return uint8_t The number of cpu cycles to perform operation (8)
 */
uint8_t Execute09(SM83State* state);

/**
 * @brief LD A, (BC) - Load the value at address BC into register A
 * @param state The current state to operate on
 * @return uint8_t The number of cpu cycles to perform operation (8)
 */
uint8_t Execute0A(SM83State* state);

/**
 * @brief DEC BC - Decrement Register BC by 1
 * @param state The current state to operate on
 * @return uint8_t The number of cpu cycles to perform operation (8)
 */
uint8_t Execute0B(SM83State* state);

/**
 * @brief INC C - Increment C by one
 * @param state The current state to operate on
 * @return uint8_t The number of cpu cycles to perform operation (4)
 */
uint8_t Execute0C(SM83State* state);

#endif