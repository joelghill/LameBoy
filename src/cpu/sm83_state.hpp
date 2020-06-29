/**
 * @file sm83_state.hpp
 * @author Joel Hill (@joelghill)
 * @brief
 * @version 0.1
 * @date 2020-06-23
 *
 * @copyright Copyright (c) 2020
 *
 */
#ifndef SM83_STATE_H
#define SM83_STATE_H

#include <iostream>

using namespace std;

class SM83State
{

private:

    // SM83 has a 16bit memory bus with 65,536 addresses
    uint8_t* memory_bus_;

    // 8 8bit CPU Registers
    uint8_t a_register_;
    uint8_t b_register_;
    uint8_t c_register_;
    uint8_t d_register_;
    uint8_t e_register_;
    uint8_t h_register_;
    uint8_t l_register_;

    // The F register holds the cpu flags.
    uint8_t f_register_;

    // 16bit sudo Registers
    uint16_t stack_pointer_;
    uint16_t program_counter_;

public:
    /**
     * @brief Constructs a new SM83State instance
     *
     * @param memory_bus_ptr Pointer to the memory bus. Expects size of at least 65,536
     */
    SM83State(uint8_t* memory_bus_ptr);

    /**
     * @brief Destroys the SM83State instance
     *
     */
    ~SM83State() = default;

    /**
     * @brief Gets the A register Value
     *
     * @return uint8_t
     */
    uint8_t a();

    /**
     * @brief Sets the A register to an 8bit value
     *
     * @param value
     */
    void setA(uint8_t value);

    /**
     * @brief Gets the F register Value
     *
     * @return uint8_t
     */
    uint8_t f();

    /**
     * @brief Sets the F register to an 8bit value
     *
     * @param value
     */
    void setF(uint8_t value);

    /**
     * @brief Gets the AF register Value
     *
     * @return uint8_t
     */
    uint16_t af();

    /**
     * @brief Sets the AF register to an 16bit value
     *
     * @param value
     */
    void setAF(uint16_t value);

    /**
     * @brief Gets the B register Value
     *
     * @return uint8_t
     */
    uint8_t b();

    /**
     * @brief Sets the B register to an 8bit value
     *
     * @param value
     */
    void setB(uint8_t value);

    /**
     * @brief Gets the C register Value
     *
     * @return uint8_t
     */
    uint8_t c();

    /**
     * @brief Sets the F register to an 8bit value
     *
     * @param value
     */
    void setC(uint8_t value);

    /**
     * @brief Gets the BC register Value
     *
     * @return uint8_t
     */
    uint16_t bc();

    /**
     * @brief Sets the AF register to an 16bit value
     *
     * @param value
     */
    void setBC(uint16_t value);

    /**
     * @brief Gets the D register Value
     *
     * @return uint8_t
     */
    uint8_t d();

    /**
     * @brief Sets the D register to an 8bit value
     *
     * @param value
     */
    void setD(uint8_t value);

    /**
     * @brief Gets the E register Value
     *
     * @return uint8_t
     */
    uint8_t e();

    /**
     * @brief Sets the E register to an 8bit value
     *
     * @param value
     */
    void setE(uint8_t value);

    /**
     * @brief Gets the BC register Value
     *
     * @return uint8_t
     */
    uint16_t de();

    /**
     * @brief Sets the DE register to an 16bit value
     *
     * @param value
     */
    void setDE(uint16_t value);

    /**
     * @brief Gets the H register Value
     *
     * @return uint8_t
     */
    uint8_t h();

    /**
     * @brief Sets the H register to an 8bit value
     *
     * @param value
     */
    void setH(uint8_t value);

    /**
     * @brief Gets the L register Value
     *
     * @return uint8_t
     */
    uint8_t l();

    /**
     * @brief Sets the L register to an 8bit value
     *
     * @param value
     */
    void setL(uint8_t value);

    /**
     * @brief Gets the HL register Value
     *
     * @return uint8_t
     */
    uint16_t hl();

    /**
     * @brief Sets the HL register to an 16bit value
     *
     * @param value
     */
    void setHL(uint16_t value);

    /**
     * @brief Gets the program counter
     *
     */
    uint16_t programCounter();

    /**
     * @brief Sets the Program Counter
     *
     * @param value The value to set the program counter to
     */
    void setProgramCounter(uint16_t value);

    /**
     * @brief Increments the program counter by a set number of bytes
     *
     * PC = PC + n
     *
     * @param num_bytes The number of bytes to increment the program counter by
     */
    void IncrementProgramCounter(uint8_t num_bytes);
};

#endif