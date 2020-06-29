/**
 * @file sm83_state.cpp
 * @author Joel Hill (@joelghill)
 * @brief
 * @version 0.1
 * @date 2020-06-26
 *
 * @copyright Copyright (c) 2020
 *
 */

#include <iostream>
#include "./sm83_state.hpp"

using namespace std;

SM83State::SM83State(uint8_t* memory_bus_ptr) {

    // Sets the pointer to the memory bus array
    this->memory_bus_ = memory_bus_ptr;
}

uint16_t SM83State::programCounter() {
    return this->program_counter_;
}

void SM83State::setProgramCounter(uint16_t value) {
    this->program_counter_ = value;
}

void SM83State::IncrementProgramCounter(uint8_t num_bytes) {
    this->program_counter_ = this->program_counter_ + num_bytes;
}
