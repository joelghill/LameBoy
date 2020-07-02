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
 * @post Z, H flags set by function. N flag reset. C flag unaffected.
 */
uint8_t Execute04(SM83State* state);

#endif