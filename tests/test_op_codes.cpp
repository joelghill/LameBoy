#include <gtest/gtest.h>
#include "../src/cpu/sm83_state.hpp"
#include "../src/cpu/sm83_op_codes.hpp"

namespace {

/**
 * @brief
 *
 */
class OpCodesTest : public ::testing::Test {
protected:

    uint8_t* memory_;
    SM83State* state_;
    uint16_t program_counter_ = 0x100;


    void SetUp() override {
        // Code here will be called immediately after the constructor (right
        // before each test).
        this->memory_ = new uint8_t[65536];
        this->state_ = new SM83State(this->memory_);
        this->state_->setProgramCounter(this->program_counter_);
    }

    void TearDown() override {
        delete this->state_;
        delete this->memory_;
    }
};

TEST_F(OpCodesTest, TestExecute00) {
    // Ensure that the operation takes 4 cycles
    ASSERT_EQ(Execute00(this->state_), 4);
    // And that the
    ASSERT_EQ(this->state_->programCounter(), program_counter_ + 1);
}

TEST_F(OpCodesTest, TestExecute01) {
    this->state_->SetMemoryAt(this->program_counter_ + 1, 0x04);
    this->state_->SetMemoryAt(this->program_counter_ + 2, 0x02);

    // Ensure that the
    ASSERT_EQ(Execute01(this->state_), 12);
    ASSERT_EQ(this->state_->programCounter(), program_counter_ + 3);

    ASSERT_EQ(this->state_->b(), 0x04);
    ASSERT_EQ(this->state_->c(), 0x02);
    ASSERT_EQ(this->state_->bc(), 0x0402);
}

TEST_F(OpCodesTest, TestExecute02) {
    uint8_t a = 0x42;
    uint8_t b = 0x02;
    uint8_t c = 0x00;

    this->state_->setA(a);
    this->state_->setB(b);
    this->state_->setC(c);

    // Ensure that the
    ASSERT_EQ(Execute02(this->state_), 8);
    ASSERT_EQ(this->state_->programCounter(), this->program_counter_ + 1);
    ASSERT_EQ(this->state_->MemoryAt((uint16_t)b << 8 | c), a);
}

TEST_F(OpCodesTest, TestExecute03) {
    uint16_t bc = 0x1987;

    this->state_->setB(0x19);
    this->state_->setC(0x87);

    // Ensure that the function returns 8 cycles
    ASSERT_EQ(Execute03(this->state_), 8);
    // 8 bit instruction, PC incremented by 1
    ASSERT_EQ(this->state_->programCounter(), this->program_counter_ + 1);
    // BC = BC++
    ASSERT_EQ(this->state_->bc(), bc + 1);
}

TEST_F(OpCodesTest, TestExecute04) {
    uint8_t b = 0x19;
    this->state_->setB(b);

    // Ensure that the function returns 4 cycles
    ASSERT_EQ(Execute04(this->state_), 4);
    // 8 bit instruction, PC incremented by 1
    ASSERT_EQ(this->state_->programCounter(), this->program_counter_ + 1);
    // B = B++
    ASSERT_EQ(this->state_->b(), b + 1);
    // Z should equal 0 since the result did not result in 0
    ASSERT_EQ(this->state_->zFlag(), 0);
    // N is always set to 0 after this operation
    ASSERT_EQ(this->state_->nFlag(), 0);
    // H Should be zero since this did not result in a carry
    ASSERT_EQ(this->state_->hFlag(), 0);
}

TEST_F(OpCodesTest, TestExecute04_Z1N0H1) {
    uint8_t b = 0xFF;
    this->state_->setB(b);

    // Ensure that the function returns 4 cycles
    ASSERT_EQ(Execute04(this->state_), 4);
    // 8 bit instruction, PC incremented by 1
    ASSERT_EQ(this->state_->programCounter(), this->program_counter_ + 1);
    // B = B++
    ASSERT_EQ(this->state_->b(), 0);
    // Z should equal 1 since the result was 0
    ASSERT_EQ(this->state_->zFlag(), 1);
    // N is always set to 0 after this operation
    ASSERT_EQ(this->state_->nFlag(), 0);
    // H Should be 1 since this resulted in a carry
    ASSERT_EQ(this->state_->hFlag(), 1);
}

TEST_F(OpCodesTest, TestExecute05_Z1N1H0) {
    uint8_t b = 0x01;
    this->state_->setB(b);

    // Ensure that the function returns 4 cycles
    ASSERT_EQ(Execute05(this->state_), 4);
    // 8 bit instruction, PC incremented by 1
    ASSERT_EQ(this->state_->programCounter(), this->program_counter_ + 1);
    // B = B--
    ASSERT_EQ(this->state_->b(), b - 1);
    // Z should equal 1 since the result of the operation was 0
    ASSERT_EQ(this->state_->zFlag(), 1);
    // N is always set to 1 after this operation
    ASSERT_EQ(this->state_->nFlag(), 1);
    // H Should be zero since this did not result in a carry
    ASSERT_EQ(this->state_->hFlag(), 0);
}

TEST_F(OpCodesTest, TestExecute05_Z0N1H1) {
    uint8_t b = 0x00;
    this->state_->setB(b);

    // Ensure that the function returns 4 cycles
    ASSERT_EQ(Execute05(this->state_), 4);
    // 8 bit instruction, PC incremented by 1
    ASSERT_EQ(this->state_->programCounter(), this->program_counter_ + 1);
    // B = B--
    ASSERT_EQ(this->state_->b(), 0xFF);
    // Z should equal 0 since the result was not 0
    ASSERT_EQ(this->state_->zFlag(), 0);
    // N is always set to 0 after this operation
    ASSERT_EQ(this->state_->nFlag(), 1);
    // H Should be 1 since this resulted in a carry
    ASSERT_EQ(this->state_->hFlag(), 1);
}

TEST_F(OpCodesTest, TestExecute06) {
    uint8_t data = 0x42;
    uint16_t pc = state_->programCounter();
    this->state_->SetMemoryAt(pc+1, data);

    // Ensure that the
    ASSERT_EQ(Execute06(this->state_), 8);
    ASSERT_EQ(this->state_->programCounter(), this->program_counter_ + 2);
    ASSERT_EQ(this->state_->b(), data);
}

TEST_F(OpCodesTest, TestExecute07_Z0N0H0C1) {
    uint8_t a = 0b10000000;
    state_->setA(a);

    ASSERT_EQ(Execute07(this->state_), 4);
    ASSERT_EQ(this->state_->programCounter(), this->program_counter_ + 1);
    ASSERT_EQ(this->state_->a(), 0b00000001);

    // Check the state of the CPU flags
    ASSERT_EQ(this->state_->zFlag(), false);
    ASSERT_EQ(this->state_->nFlag(), false);
    ASSERT_EQ(this->state_->hFlag(), false);
    ASSERT_EQ(this->state_->cFlag(), true);
}

TEST_F(OpCodesTest, TestExecute07_Z1N0H0C0) {
    uint8_t a = 0b00000000;
    state_->setA(a);

    ASSERT_EQ(Execute07(this->state_), 4);
    ASSERT_EQ(this->state_->programCounter(), this->program_counter_ + 1);
    ASSERT_EQ(this->state_->a(), 0b00000000);

    // Check the state of the CPU flags
    ASSERT_EQ(this->state_->zFlag(), true);
    ASSERT_EQ(this->state_->nFlag(), false);
    ASSERT_EQ(this->state_->hFlag(), false);
    ASSERT_EQ(this->state_->cFlag(), false);
}

TEST_F(OpCodesTest, TestExecute08) {
    uint8_t sp_a = 0xA3;
    uint8_t sp_b = 0x0E;
    state_->setStackPointer(0xA30E);

    ASSERT_EQ(Execute08(this->state_), 20);
    ASSERT_EQ(this->state_->programCounter(), this->program_counter_ + 3);
    ASSERT_EQ(this->state_->MemoryAt(this->program_counter_ + 1), sp_a);
    ASSERT_EQ(this->state_->MemoryAt(this->program_counter_ + 2), sp_b);
}

TEST_F(OpCodesTest, TestExecute09_N0H1C1) {
    uint16_t hl = 0xFFFF;
    uint16_t bc = 0x0001;

    this->state_->setHL(hl);
    this->state_->setBC(bc);

    ASSERT_EQ(Execute09(this->state_), 8);
    ASSERT_EQ(this->state_->programCounter(), this->program_counter_ + 1);
    ASSERT_EQ(state_->hl(), (uint16_t)(hl + bc));

    // Check the state of the CPU flags
    ASSERT_EQ(this->state_->nFlag(), false);
    ASSERT_EQ(this->state_->hFlag(), true);
    ASSERT_EQ(this->state_->cFlag(), true);
}

TEST_F(OpCodesTest, TestExecute0A) {
    uint16_t bc = 0xAAAA;
    uint8_t value = 42;

    this->state_->setBC(bc);
    this->state_->SetMemoryAt(bc, value);

    ASSERT_EQ(Execute0A(this->state_), 8);
    ASSERT_EQ(this->state_->a(), value);
}

TEST_F(OpCodesTest, TestExecute0B) {
    uint16_t bc = 0x1987;

    this->state_->setB(0x19);
    this->state_->setC(0x87);

    // Ensure that the function returns 8 cycles
    ASSERT_EQ(Execute0B(this->state_), 8);
    // 8 bit instruction, PC incremented by 1
    ASSERT_EQ(this->state_->programCounter(), this->program_counter_ + 1);
    // BC = BC++
    ASSERT_EQ(this->state_->bc(), bc - 1);
}

TEST_F(OpCodesTest, TestExecute0C) {
    uint8_t c = 0x19;
    this->state_->setC(c);

    // Ensure that the function returns 4 cycles
    ASSERT_EQ(Execute0C(this->state_), 4);
    // 8 bit instruction, PC incremented by 1
    ASSERT_EQ(this->state_->programCounter(), this->program_counter_ + 1);
    // C = C++
    ASSERT_EQ(this->state_->c(), c + 1);
    // Z should equal 0 since the result did not result in 0
    ASSERT_EQ(this->state_->zFlag(), 0);
    // N is always set to 0 after this operation
    ASSERT_EQ(this->state_->nFlag(), 0);
    // H Should be zero since this did not result in a carry
    ASSERT_EQ(this->state_->hFlag(), 0);
}

TEST_F(OpCodesTest, TestExecute0C_Z1N0H1) {
    uint8_t c = 0xFF;
    this->state_->setC(c);

    // Ensure that the function returns 4 cycles
    ASSERT_EQ(Execute0C(this->state_), 4);
    // 8 bit instruction, PC incremented by 1
    ASSERT_EQ(this->state_->programCounter(), this->program_counter_ + 1);
    // C = C++
    ASSERT_EQ(this->state_->c(), 0);
    // Z should equal 1 since the result was 0
    ASSERT_EQ(this->state_->zFlag(), 1);
    // N is always set to 0 after this operation
    ASSERT_EQ(this->state_->nFlag(), 0);
    // H Should be 1 since this resulted in a carry
    ASSERT_EQ(this->state_->hFlag(), 1);
}

}  // namespace

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}