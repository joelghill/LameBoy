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

TEST_F(OpCodesTest, TestExecute11) {
    this->state_->SetMemoryAt(this->program_counter_ + 1, 0x04);
    this->state_->SetMemoryAt(this->program_counter_ + 2, 0x02);

    // Ensure that the
    ASSERT_EQ(Execute11(this->state_), 12);
    ASSERT_EQ(this->state_->programCounter(), program_counter_ + 3);

    ASSERT_EQ(this->state_->d(), 0x04);
    ASSERT_EQ(this->state_->e(), 0x02);
    ASSERT_EQ(this->state_->de(), 0x0402);
}

TEST_F(OpCodesTest, TestExecute21) {
    this->state_->SetMemoryAt(this->program_counter_ + 1, 0x04);
    this->state_->SetMemoryAt(this->program_counter_ + 2, 0x02);

    // Ensure that the
    ASSERT_EQ(Execute21(this->state_), 12);
    ASSERT_EQ(this->state_->programCounter(), program_counter_ + 3);

    ASSERT_EQ(this->state_->h(), 0x04);
    ASSERT_EQ(this->state_->l(), 0x02);
    ASSERT_EQ(this->state_->hl(), 0x0402);
}

TEST_F(OpCodesTest, TestExecute31) {
    this->state_->SetMemoryAt(this->program_counter_ + 1, 0x04);
    this->state_->SetMemoryAt(this->program_counter_ + 2, 0x02);

    // Ensure that the
    ASSERT_EQ(Execute31(this->state_), 12);
    ASSERT_EQ(this->state_->programCounter(), program_counter_ + 3);

    ASSERT_EQ(this->state_->stackPointer(), 0x0402);
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

TEST_F(OpCodesTest, TestExecute12) {
    uint8_t a = 0x42;
    uint8_t d = 0x02;
    uint8_t e = 0x00;

    this->state_->setA(a);
    this->state_->setD(d);
    this->state_->setE(e);

    // Ensure that the
    ASSERT_EQ(Execute12(this->state_), 8);
    ASSERT_EQ(this->state_->programCounter(), this->program_counter_ + 1);
    ASSERT_EQ(this->state_->MemoryAt((uint16_t)d << 8 | e), a);
}

TEST_F(OpCodesTest, TestExecute22) {
    uint8_t a = 0x42;
    uint8_t h = 0x02;
    uint8_t l = 0x00;
    uint16_t hl = 0x0200;

    this->state_->setA(a);
    this->state_->setH(h);
    this->state_->setL(l);

    // Ensure that the
    ASSERT_EQ(Execute22(this->state_), 8);
    ASSERT_EQ(this->state_->programCounter(), this->program_counter_ + 1);
    ASSERT_EQ(this->state_->MemoryAt(hl), a);
    ASSERT_EQ(this->state_->hl(), hl + 1);
}

TEST_F(OpCodesTest, TestExecute32) {
    uint8_t a = 0x42;
    uint8_t h = 0x02;
    uint8_t l = 0x00;
    uint16_t hl = 0x0200;

    this->state_->setA(a);
    this->state_->setH(h);
    this->state_->setL(l);

    // Ensure that the
    ASSERT_EQ(Execute32(this->state_), 8);
    ASSERT_EQ(this->state_->programCounter(), this->program_counter_ + 1);
    ASSERT_EQ(this->state_->MemoryAt(hl), a);
    ASSERT_EQ(this->state_->hl(), hl - 1);
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

TEST_F(OpCodesTest, TestExecute13) {
    uint16_t de = 0x1987;

    this->state_->setD(0x19);
    this->state_->setE(0x87);

    // Ensure that the function returns 8 cycles
    ASSERT_EQ(Execute13(this->state_), 8);
    // 8 bit instruction, PC incremented by 1
    ASSERT_EQ(this->state_->programCounter(), this->program_counter_ + 1);
    // BC = BC++
    ASSERT_EQ(this->state_->de(), de + 1);
}

TEST_F(OpCodesTest, TestExecute23) {
    uint16_t hl = 0x1987;

    this->state_->setH(0x19);
    this->state_->setL(0x87);

    // Ensure that the function returns 8 cycles
    ASSERT_EQ(Execute23(this->state_), 8);
    // 8 bit instruction, PC incremented by 1
    ASSERT_EQ(this->state_->programCounter(), this->program_counter_ + 1);
    // BC = BC++
    ASSERT_EQ(this->state_->hl(), hl + 1);
}

TEST_F(OpCodesTest, TestExecute33) {
    uint16_t sp = 0x1987;
    this->state_->setStackPointer(sp);

    // Ensure that the function returns 8 cycles
    ASSERT_EQ(Execute33(this->state_), 8);
    // 8 bit instruction, PC incremented by 1
    ASSERT_EQ(this->state_->programCounter(), this->program_counter_ + 1);
    // BC = BC++
    ASSERT_EQ(this->state_->stackPointer(), sp + 1);
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

TEST_F(OpCodesTest, TestExecute14) {
    uint8_t d = 0x19;
    this->state_->setD(d);

    // Ensure that the function returns 4 cycles
    ASSERT_EQ(Execute14(this->state_), 4);
    // 8 bit instruction, PC incremented by 1
    ASSERT_EQ(this->state_->programCounter(), this->program_counter_ + 1);
    // B = B++
    ASSERT_EQ(this->state_->d(), d + 1);
    // Z should equal 0 since the result did not result in 0
    ASSERT_EQ(this->state_->zFlag(), 0);
    // N is always set to 0 after this operation
    ASSERT_EQ(this->state_->nFlag(), 0);
    // H Should be zero since this did not result in a carry
    ASSERT_EQ(this->state_->hFlag(), 0);
}

TEST_F(OpCodesTest, TestExecute14_Z1N0H1) {
    uint8_t d = 0xFF;
    this->state_->setD(d);

    // Ensure that the function returns 4 cycles
    ASSERT_EQ(Execute14(this->state_), 4);
    // 8 bit instruction, PC incremented by 1
    ASSERT_EQ(this->state_->programCounter(), this->program_counter_ + 1);
    // B = B++
    ASSERT_EQ(this->state_->d(), 0);
    // Z should equal 1 since the result was 0
    ASSERT_EQ(this->state_->zFlag(), 1);
    // N is always set to 0 after this operation
    ASSERT_EQ(this->state_->nFlag(), 0);
    // H Should be 1 since this resulted in a carry
    ASSERT_EQ(this->state_->hFlag(), 1);
}

TEST_F(OpCodesTest, TestExecute24) {
    uint8_t h = 0x19;
    this->state_->setH(h);

    // Ensure that the function returns 4 cycles
    ASSERT_EQ(Execute24(this->state_), 4);
    // 8 bit instruction, PC incremented by 1
    ASSERT_EQ(this->state_->programCounter(), this->program_counter_ + 1);
    // B = B++
    ASSERT_EQ(this->state_->h(), h + 1);
    // Z should equal 0 since the result did not result in 0
    ASSERT_EQ(this->state_->zFlag(), 0);
    // N is always set to 0 after this operation
    ASSERT_EQ(this->state_->nFlag(), 0);
    // H Should be zero since this did not result in a carry
    ASSERT_EQ(this->state_->hFlag(), 0);
}

TEST_F(OpCodesTest, TestExecute24_Z1N0H1) {
    uint8_t h = 0xFF;
    this->state_->setH(h);

    // Ensure that the function returns 4 cycles
    ASSERT_EQ(Execute24(this->state_), 4);
    // 8 bit instruction, PC incremented by 1
    ASSERT_EQ(this->state_->programCounter(), this->program_counter_ + 1);
    // B = B++
    ASSERT_EQ(this->state_->h(), 0);
    // Z should equal 1 since the result was 0
    ASSERT_EQ(this->state_->zFlag(), 1);
    // N is always set to 0 after this operation
    ASSERT_EQ(this->state_->nFlag(), 0);
    // H Should be 1 since this resulted in a carry
    ASSERT_EQ(this->state_->hFlag(), 1);
}

TEST_F(OpCodesTest, TestExecute34_Z1N0H1) {
    uint16_t hl = 0x9021;
    this->state_->setHL(hl);

    uint8_t value = 0xFF;
    state_->SetMemoryAt(hl, value);

    // Ensure that the function returns 12 cycles
    ASSERT_EQ(Execute34(this->state_), 12);
    // 8 bit instruction, PC incremented by 1
    ASSERT_EQ(this->state_->programCounter(), this->program_counter_ + 1);
    ASSERT_EQ(this->state_->MemoryAt(hl), 0);
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

TEST_F(OpCodesTest, TestExecute15_Z1N1H0) {
    uint8_t d = 0x01;
    this->state_->setD(d);

    // Ensure that the function returns 4 cycles
    ASSERT_EQ(Execute15(this->state_), 4);
    // 8 bit instruction, PC incremented by 1
    ASSERT_EQ(this->state_->programCounter(), this->program_counter_ + 1);
    // B = B--
    ASSERT_EQ(this->state_->d(), d - 1);
    // Z should equal 1 since the result of the operation was 0
    ASSERT_EQ(this->state_->zFlag(), 1);
    // N is always set to 1 after this operation
    ASSERT_EQ(this->state_->nFlag(), 1);
    // H Should be zero since this did not result in a carry
    ASSERT_EQ(this->state_->hFlag(), 0);
}

TEST_F(OpCodesTest, TestExecute15_Z0N1H1) {
    uint8_t d = 0x00;
    this->state_->setD(d);

    // Ensure that the function returns 4 cycles
    ASSERT_EQ(Execute15(this->state_), 4);
    // 8 bit instruction, PC incremented by 1
    ASSERT_EQ(this->state_->programCounter(), this->program_counter_ + 1);
    // B = B--
    ASSERT_EQ(this->state_->d(), 0xFF);
    // Z should equal 0 since the result was not 0
    ASSERT_EQ(this->state_->zFlag(), 0);
    // N is always set to 0 after this operation
    ASSERT_EQ(this->state_->nFlag(), 1);
    // H Should be 1 since this resulted in a carry
    ASSERT_EQ(this->state_->hFlag(), 1);
}

TEST_F(OpCodesTest, TestExecute25_Z1N1H0) {
    uint8_t h = 0x01;
    this->state_->setH(h);

    // Ensure that the function returns 4 cycles
    ASSERT_EQ(Execute25(this->state_), 4);
    // 8 bit instruction, PC incremented by 1
    ASSERT_EQ(this->state_->programCounter(), this->program_counter_ + 1);
    // B = B--
    ASSERT_EQ(this->state_->h(), h - 1);
    // Z should equal 1 since the result of the operation was 0
    ASSERT_EQ(this->state_->zFlag(), 1);
    // N is always set to 1 after this operation
    ASSERT_EQ(this->state_->nFlag(), 1);
    // H Should be zero since this did not result in a carry
    ASSERT_EQ(this->state_->hFlag(), 0);
}

TEST_F(OpCodesTest, TestExecute25_Z0N1H1) {
    uint8_t h = 0x00;
    this->state_->setH(h);

    // Ensure that the function returns 4 cycles
    ASSERT_EQ(Execute25(this->state_), 4);
    // 8 bit instruction, PC incremented by 1
    ASSERT_EQ(this->state_->programCounter(), this->program_counter_ + 1);
    // B = B--
    ASSERT_EQ(this->state_->h(), 0xFF);
    // Z should equal 0 since the result was not 0
    ASSERT_EQ(this->state_->zFlag(), 0);
    // N is always set to 0 after this operation
    ASSERT_EQ(this->state_->nFlag(), 1);
    // H Should be 1 since this resulted in a carry
    ASSERT_EQ(this->state_->hFlag(), 1);
}

TEST_F(OpCodesTest, TestExecute35_Z1N1H0) {
    uint16_t hl = 0x01FF;
    uint8_t value = 0x01;

    this->state_->setHL(hl);
    this->state_->SetMemoryAt(hl, value);

    // Ensure that the function returns 12 cycles
    ASSERT_EQ(Execute35(this->state_), 12);
    // 8 bit instruction, PC incremented by 1
    ASSERT_EQ(this->state_->programCounter(), this->program_counter_ + 1);
    ASSERT_EQ(this->state_->MemoryAt(hl), value - 1);
    // Z should equal 1 since the result of the operation was 0
    ASSERT_EQ(this->state_->zFlag(), 1);
    // N is always set to 1 after this operation
    ASSERT_EQ(this->state_->nFlag(), 1);
    // H Should be zero since this did not result in a carry
    ASSERT_EQ(this->state_->hFlag(), 0);
}

TEST_F(OpCodesTest, TestExecute35_Z0N1H1) {
    uint16_t hl = 0x01FF;
    uint8_t value = 0x00;

    this->state_->setHL(hl);
    this->state_->SetMemoryAt(hl, value);

    // Ensure that the function returns 12 cycles
    ASSERT_EQ(Execute35(this->state_), 12);
    // 8 bit instruction, PC incremented by 1
    ASSERT_EQ(this->state_->programCounter(), this->program_counter_ + 1);
    ASSERT_EQ(this->state_->MemoryAt(hl), 0xff);
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

TEST_F(OpCodesTest, TestExecute16) {
    uint8_t data = 0x42;
    uint16_t pc = state_->programCounter();
    this->state_->SetMemoryAt(pc+1, data);

    // Ensure that the
    ASSERT_EQ(Execute16(this->state_), 8);
    ASSERT_EQ(this->state_->programCounter(), this->program_counter_ + 2);
    ASSERT_EQ(this->state_->d(), data);
}

TEST_F(OpCodesTest, TestExecute26) {
    uint8_t data = 0x42;
    uint16_t pc = state_->programCounter();
    this->state_->SetMemoryAt(pc+1, data);

    // Ensure that the
    ASSERT_EQ(Execute26(this->state_), 8);
    ASSERT_EQ(this->state_->programCounter(), this->program_counter_ + 2);
    ASSERT_EQ(this->state_->h(), data);
}

TEST_F(OpCodesTest, TestExecute36) {
    uint8_t data = 0x42;
    uint16_t pc = state_->programCounter();
    uint16_t hl = 0x87AB;

    this->state_->SetMemoryAt(pc+1, data);
    this->state_->setHL(hl);

    ASSERT_EQ(Execute36(this->state_), 12);
    ASSERT_EQ(this->state_->programCounter(), this->program_counter_ + 2);
    ASSERT_EQ(this->state_->MemoryAt(hl), data);
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

TEST_F(OpCodesTest, TestExecute17_Z0N0H0C1) {
    uint8_t a = 0b10000000;
    state_->setA(a);
    state_->setF(C_FLAG);

    ASSERT_EQ(Execute17(this->state_), 4);
    ASSERT_EQ(this->state_->programCounter(), this->program_counter_ + 1);
    ASSERT_EQ(this->state_->a(), 0b00000001);

    // Check the state of the CPU flags
    ASSERT_EQ(this->state_->zFlag(), false);
    ASSERT_EQ(this->state_->nFlag(), false);
    ASSERT_EQ(this->state_->hFlag(), false);
    ASSERT_EQ(this->state_->cFlag(), true);
}

TEST_F(OpCodesTest, TestExecute17_Z1N0H0C0) {
    uint8_t a = 0b00000000;
    state_->setA(a);
    state_->setF(0b00000000);

    ASSERT_EQ(Execute17(this->state_), 4);
    ASSERT_EQ(this->state_->programCounter(), this->program_counter_ + 1);
    ASSERT_EQ(this->state_->a(), 0b00000000);

    // Check the state of the CPU flags
    ASSERT_EQ(this->state_->zFlag(), true);
    ASSERT_EQ(this->state_->nFlag(), false);
    ASSERT_EQ(this->state_->hFlag(), false);
    ASSERT_EQ(this->state_->cFlag(), false);
}

TEST_F(OpCodesTest, TestExecute37) {
    uint8_t f = 0b11100000;
    state_->setF(f);

    ASSERT_EQ(Execute37(this->state_), 4);
    ASSERT_EQ(this->state_->programCounter(), this->program_counter_ + 1);
    ASSERT_EQ(this->state_->f(), 0b10010000);

    // Check the state of the CPU flags
    ASSERT_EQ(this->state_->zFlag(), true);
    ASSERT_EQ(this->state_->nFlag(), false);
    ASSERT_EQ(this->state_->hFlag(), false);
    ASSERT_EQ(this->state_->cFlag(), true);
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

TEST_F(OpCodesTest, TestExecute18) {
    int8_t r8 = -1; // -1
    state_->SetMemoryAt(this->program_counter_ + 1, r8);

    ASSERT_EQ(Execute18(this->state_), 12);
    ASSERT_EQ(this->state_->programCounter(), this->program_counter_ - 1);
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

TEST_F(OpCodesTest, TestExecute19_N0H1C1) {
    uint16_t hl = 0xFFFF;
    uint16_t de = 0x0001;

    this->state_->setHL(hl);
    this->state_->setDE(de);

    ASSERT_EQ(Execute19(this->state_), 8);
    ASSERT_EQ(this->state_->programCounter(), this->program_counter_ + 1);
    ASSERT_EQ(state_->hl(), (uint16_t)(hl + de));

    // Check the state of the CPU flags
    ASSERT_EQ(this->state_->nFlag(), false);
    ASSERT_EQ(this->state_->hFlag(), true);
    ASSERT_EQ(this->state_->cFlag(), true);
}

TEST_F(OpCodesTest, TestExecute29_N0H1C1) {
    uint16_t hl = 0xFFFF;

    this->state_->setHL(hl);

    ASSERT_EQ(Execute29(this->state_), 8);
    ASSERT_EQ(this->state_->programCounter(), this->program_counter_ + 1);
    ASSERT_EQ(state_->hl(), (uint16_t)(hl + hl));

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

TEST_F(OpCodesTest, TestExecute1A) {
    uint16_t de = 0xAAAA;
    uint8_t value = 42;

    this->state_->setDE(de);
    this->state_->SetMemoryAt(de, value);

    ASSERT_EQ(Execute1A(this->state_), 8);
    ASSERT_EQ(this->state_->a(), value);
}

TEST_F(OpCodesTest, TestExecute2A) {
    uint16_t hl = 0xAAAA;
    uint8_t value = 42;

    this->state_->setHL(hl);
    this->state_->SetMemoryAt(hl, value);

    ASSERT_EQ(Execute2A(this->state_), 8);
    ASSERT_EQ(this->state_->a(), value);
    ASSERT_EQ(this->state_->hl(), (hl + 1));
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

TEST_F(OpCodesTest, TestExecute1B) {
    uint16_t de = 0x1987;

    this->state_->setD(0x19);
    this->state_->setE(0x87);

    // Ensure that the function returns 8 cycles
    ASSERT_EQ(Execute1B(this->state_), 8);
    // 8 bit instruction, PC incremented by 1
    ASSERT_EQ(this->state_->programCounter(), this->program_counter_ + 1);
    // BC = BC++
    ASSERT_EQ(this->state_->de(), de - 1);
}

TEST_F(OpCodesTest, TestExecute2B) {
    uint16_t hl = 0x1987;

    this->state_->setH(0x19);
    this->state_->setL(0x87);

    // Ensure that the function returns 8 cycles
    ASSERT_EQ(Execute2B(this->state_), 8);
    // 8 bit instruction, PC incremented by 1
    ASSERT_EQ(this->state_->programCounter(), this->program_counter_ + 1);
    // BC = BC++
    ASSERT_EQ(this->state_->hl(), hl - 1);
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

TEST_F(OpCodesTest, TestExecute1C) {
    uint8_t e = 0x19;
    this->state_->setE(e);

    // Ensure that the function returns 4 cycles
    ASSERT_EQ(Execute1C(this->state_), 4);
    // 8 bit instruction, PC incremented by 1
    ASSERT_EQ(this->state_->programCounter(), this->program_counter_ + 1);
    // C = C++
    ASSERT_EQ(this->state_->e(), e + 1);
    // Z should equal 0 since the result did not result in 0
    ASSERT_EQ(this->state_->zFlag(), 0);
    // N is always set to 0 after this operation
    ASSERT_EQ(this->state_->nFlag(), 0);
    // H Should be zero since this did not result in a carry
    ASSERT_EQ(this->state_->hFlag(), 0);
}

TEST_F(OpCodesTest, TestExecute1C_Z1N0H1) {
    uint8_t e = 0xFF;
    this->state_->setE(e);

    // Ensure that the function returns 4 cycles
    ASSERT_EQ(Execute1C(this->state_), 4);
    // 8 bit instruction, PC incremented by 1
    ASSERT_EQ(this->state_->programCounter(), this->program_counter_ + 1);
    // C = C++
    ASSERT_EQ(this->state_->e(), 0);
    // Z should equal 1 since the result was 0
    ASSERT_EQ(this->state_->zFlag(), 1);
    // N is always set to 0 after this operation
    ASSERT_EQ(this->state_->nFlag(), 0);
    // H Should be 1 since this resulted in a carry
    ASSERT_EQ(this->state_->hFlag(), 1);
}

TEST_F(OpCodesTest, TestExecute2C) {
    uint8_t l = 0x19;
    this->state_->setL(l);

    // Ensure that the function returns 4 cycles
    ASSERT_EQ(Execute2C(this->state_), 4);
    // 8 bit instruction, PC incremented by 1
    ASSERT_EQ(this->state_->programCounter(), this->program_counter_ + 1);
    // C = C++
    ASSERT_EQ(this->state_->l(), l + 1);
    // Z should equal 0 since the result did not result in 0
    ASSERT_EQ(this->state_->zFlag(), 0);
    // N is always set to 0 after this operation
    ASSERT_EQ(this->state_->nFlag(), 0);
    // H Should be zero since this did not result in a carry
    ASSERT_EQ(this->state_->hFlag(), 0);
}

TEST_F(OpCodesTest, TestExecute2C_Z1N0H1) {
    uint8_t l = 0xFF;
    this->state_->setL(l);

    // Ensure that the function returns 4 cycles
    ASSERT_EQ(Execute2C(this->state_), 4);
    // 8 bit instruction, PC incremented by 1
    ASSERT_EQ(this->state_->programCounter(), this->program_counter_ + 1);
    // C = C++
    ASSERT_EQ(this->state_->l(), 0);
    // Z should equal 1 since the result was 0
    ASSERT_EQ(this->state_->zFlag(), 1);
    // N is always set to 0 after this operation
    ASSERT_EQ(this->state_->nFlag(), 0);
    // H Should be 1 since this resulted in a carry
    ASSERT_EQ(this->state_->hFlag(), 1);
}

TEST_F(OpCodesTest, TestExecute0D_Z1N1H0) {
    uint8_t c = 0x01;
    this->state_->setC(c);

    // Ensure that the function returns 4 cycles
    ASSERT_EQ(Execute0D(this->state_), 4);
    // 8 bit instruction, PC incremented by 1
    ASSERT_EQ(this->state_->programCounter(), this->program_counter_ + 1);
    // B = B--
    ASSERT_EQ(this->state_->c(), c - 1);
    // Z should equal 1 since the result of the operation was 0
    ASSERT_EQ(this->state_->zFlag(), 1);
    // N is always set to 1 after this operation
    ASSERT_EQ(this->state_->nFlag(), 1);
    // H Should be zero since this did not result in a carry
    ASSERT_EQ(this->state_->hFlag(), 0);
}

TEST_F(OpCodesTest, TestExecute0D_Z0N1H1) {
    uint8_t c = 0x00;
    this->state_->setC(c);

    // Ensure that the function returns 4 cycles
    ASSERT_EQ(Execute0D(this->state_), 4);
    // 8 bit instruction, PC incremented by 1
    ASSERT_EQ(this->state_->programCounter(), this->program_counter_ + 1);
    // B = B--
    ASSERT_EQ(this->state_->c(), 0xFF);
    // Z should equal 0 since the result was not 0
    ASSERT_EQ(this->state_->zFlag(), 0);
    // N is always set to 0 after this operation
    ASSERT_EQ(this->state_->nFlag(), 1);
    // H Should be 1 since this resulted in a carry
    ASSERT_EQ(this->state_->hFlag(), 1);
}

TEST_F(OpCodesTest, TestExecute1D_Z1N1H0) {
    uint8_t e = 0x01;
    this->state_->setE(e);

    // Ensure that the function returns 4 cycles
    ASSERT_EQ(Execute1D(this->state_), 4);
    // 8 bit instruction, PC incremented by 1
    ASSERT_EQ(this->state_->programCounter(), this->program_counter_ + 1);
    // B = B--
    ASSERT_EQ(this->state_->e(), e - 1);
    // Z should equal 1 since the result of the operation was 0
    ASSERT_EQ(this->state_->zFlag(), 1);
    // N is always set to 1 after this operation
    ASSERT_EQ(this->state_->nFlag(), 1);
    // H Should be zero since this did not result in a carry
    ASSERT_EQ(this->state_->hFlag(), 0);
}

TEST_F(OpCodesTest, TestExecute1D_Z0N1H1) {
    uint8_t e = 0x00;
    this->state_->setE(e);

    // Ensure that the function returns 4 cycles
    ASSERT_EQ(Execute1D(this->state_), 4);
    // 8 bit instruction, PC incremented by 1
    ASSERT_EQ(this->state_->programCounter(), this->program_counter_ + 1);
    // B = B--
    ASSERT_EQ(this->state_->e(), 0xFF);
    // Z should equal 0 since the result was not 0
    ASSERT_EQ(this->state_->zFlag(), 0);
    // N is always set to 0 after this operation
    ASSERT_EQ(this->state_->nFlag(), 1);
    // H Should be 1 since this resulted in a carry
    ASSERT_EQ(this->state_->hFlag(), 1);
}

TEST_F(OpCodesTest, TestExecute2D_Z1N1H0) {
    uint8_t l = 0x01;
    this->state_->setL(l);

    // Ensure that the function returns 4 cycles
    ASSERT_EQ(Execute2D(this->state_), 4);
    // 8 bit instruction, PC incremented by 1
    ASSERT_EQ(this->state_->programCounter(), this->program_counter_ + 1);
    // B = B--
    ASSERT_EQ(this->state_->l(), l - 1);
    // Z should equal 1 since the result of the operation was 0
    ASSERT_EQ(this->state_->zFlag(), 1);
    // N is always set to 1 after this operation
    ASSERT_EQ(this->state_->nFlag(), 1);
    // H Should be zero since this did not result in a carry
    ASSERT_EQ(this->state_->hFlag(), 0);
}

TEST_F(OpCodesTest, TestExecute2D_Z0N1H1) {
    uint8_t l = 0x00;
    this->state_->setL(l);

    // Ensure that the function returns 4 cycles
    ASSERT_EQ(Execute2D(this->state_), 4);
    // 8 bit instruction, PC incremented by 1
    ASSERT_EQ(this->state_->programCounter(), this->program_counter_ + 1);
    // B = B--
    ASSERT_EQ(this->state_->l(), 0xFF);
    // Z should equal 0 since the result was not 0
    ASSERT_EQ(this->state_->zFlag(), 0);
    // N is always set to 0 after this operation
    ASSERT_EQ(this->state_->nFlag(), 1);
    // H Should be 1 since this resulted in a carry
    ASSERT_EQ(this->state_->hFlag(), 1);
}

TEST_F(OpCodesTest, TestExecute0E) {
    uint8_t data = 0x42;
    uint16_t pc = state_->programCounter();
    this->state_->SetMemoryAt(pc+1, data);

    // Ensure that the
    ASSERT_EQ(Execute0E(this->state_), 8);
    ASSERT_EQ(this->state_->programCounter(), this->program_counter_ + 2);
    ASSERT_EQ(this->state_->c(), data);
}

TEST_F(OpCodesTest, TestExecute1E) {
    uint8_t data = 0x42;
    uint16_t pc = state_->programCounter();
    this->state_->SetMemoryAt(pc+1, data);

    // Ensure that the
    ASSERT_EQ(Execute1E(this->state_), 8);
    ASSERT_EQ(this->state_->programCounter(), this->program_counter_ + 2);
    ASSERT_EQ(this->state_->e(), data);
}

TEST_F(OpCodesTest, TestExecute2E) {
    uint8_t data = 0x42;
    uint16_t pc = state_->programCounter();
    this->state_->SetMemoryAt(pc+1, data);

    // Ensure that the
    ASSERT_EQ(Execute2E(this->state_), 8);
    ASSERT_EQ(this->state_->programCounter(), this->program_counter_ + 2);
    ASSERT_EQ(this->state_->l(), data);
}

TEST_F(OpCodesTest, TestExecute0F_Z0N0H0C1) {
    uint8_t a = 0b0000001;
    state_->setA(a);

    ASSERT_EQ(Execute0F(this->state_), 4);
    ASSERT_EQ(this->state_->programCounter(), this->program_counter_ + 1);
    ASSERT_EQ(this->state_->a(), 0b10000000);

    // Check the state of the CPU flags
    ASSERT_EQ(this->state_->zFlag(), false);
    ASSERT_EQ(this->state_->nFlag(), false);
    ASSERT_EQ(this->state_->hFlag(), false);
    ASSERT_EQ(this->state_->cFlag(), true);
}

TEST_F(OpCodesTest, TestExecute0F_Z1N0H0C0) {
    uint8_t a = 0b00000000;
    state_->setA(a);

    ASSERT_EQ(Execute0F(this->state_), 4);
    ASSERT_EQ(this->state_->programCounter(), this->program_counter_ + 1);
    ASSERT_EQ(this->state_->a(), 0b00000000);

    // Check the state of the CPU flags
    ASSERT_EQ(this->state_->zFlag(), true);
    ASSERT_EQ(this->state_->nFlag(), false);
    ASSERT_EQ(this->state_->hFlag(), false);
    ASSERT_EQ(this->state_->cFlag(), false);
}

TEST_F(OpCodesTest, TestExecute1F_Z0N0H0C1) {
    uint8_t a = 0b0000001;
    state_->setA(a);
    state_->setF(C_FLAG);

    ASSERT_EQ(Execute1F(this->state_), 4);
    ASSERT_EQ(this->state_->programCounter(), this->program_counter_ + 1);
    ASSERT_EQ(this->state_->a(), 0b10000000);

    // Check the state of the CPU flags
    ASSERT_EQ(this->state_->zFlag(), false);
    ASSERT_EQ(this->state_->nFlag(), false);
    ASSERT_EQ(this->state_->hFlag(), false);
    ASSERT_EQ(this->state_->cFlag(), true);
}

TEST_F(OpCodesTest, TestExecute1F_Z1N0H0C0) {
    uint8_t a = 0b00000000;
    state_->setA(a);
    state_->setF(0b00000000);

    ASSERT_EQ(Execute1F(this->state_), 4);
    ASSERT_EQ(this->state_->programCounter(), this->program_counter_ + 1);
    ASSERT_EQ(this->state_->a(), 0b00000000);

    // Check the state of the CPU flags
    ASSERT_EQ(this->state_->zFlag(), true);
    ASSERT_EQ(this->state_->nFlag(), false);
    ASSERT_EQ(this->state_->hFlag(), false);
    ASSERT_EQ(this->state_->cFlag(), false);
}

TEST_F(OpCodesTest, TestExecute2F) {
    uint8_t a = 0b01010101;
    state_->setA(a);
    state_->setF(0b10010000);

    ASSERT_EQ(Execute2F(this->state_), 4);
    ASSERT_EQ(this->state_->programCounter(), this->program_counter_ + 1);
    ASSERT_EQ(this->state_->a(), 0b10101010);

    // Check the state of the CPU flags
    ASSERT_EQ(this->state_->zFlag(), true);
    ASSERT_EQ(this->state_->nFlag(), true);
    ASSERT_EQ(this->state_->hFlag(), true);
    ASSERT_EQ(this->state_->cFlag(), true);
}

TEST_F(OpCodesTest, TestExecute20_NoJump) {
    // Set Z to 1. NC == False
    state_->setF(0b10000000);

    ASSERT_EQ(Execute20(this->state_), 8);
    ASSERT_EQ(this->state_->programCounter(), this->program_counter_ + 2);
}

TEST_F(OpCodesTest, TestExecute20_JumpForward) {
    int8_t jump = 42;
    // Set Z to 0. NC == True
    state_->setF(0b00000000);
    state_->SetMemoryAt(state_->programCounter() + 1, jump);

    ASSERT_EQ(Execute20(this->state_), 12);
    ASSERT_EQ(this->state_->programCounter(), this->program_counter_ + jump);
}

TEST_F(OpCodesTest, TestExecute20_JumpBack) {
    int8_t jump = -10;
    // Set Z to 0. NC == True
    state_->setF(0b00000000);
    state_->SetMemoryAt(state_->programCounter() + 1, jump);

    ASSERT_EQ(Execute20(this->state_), 12);
    ASSERT_EQ(this->state_->programCounter(), this->program_counter_ + jump);
}

TEST_F(OpCodesTest, TestExecute30_NoJump) {
    // Set C to 1. NC == False
    state_->setF(0b00010000);

    ASSERT_EQ(Execute30(this->state_), 8);
    ASSERT_EQ(this->state_->programCounter(), this->program_counter_ + 2);
}

TEST_F(OpCodesTest, TestExecute30_JumpForward) {
    int8_t jump = 42;
    // Set Z to 0. NC == True
    state_->setF(0b00000000);
    state_->SetMemoryAt(state_->programCounter() + 1, jump);

    ASSERT_EQ(Execute30(this->state_), 12);
    ASSERT_EQ(this->state_->programCounter(), this->program_counter_ + jump);
}

TEST_F(OpCodesTest, TestExecute30_JumpBack) {
    int8_t jump = -10;
    // Set Z to 0. NC == True
    state_->setF(0b00000000);
    state_->SetMemoryAt(state_->programCounter() + 1, jump);

    ASSERT_EQ(Execute20(this->state_), 12);
    ASSERT_EQ(this->state_->programCounter(), this->program_counter_ + jump);
}

TEST_F(OpCodesTest, TestExecute28_NoJump) {
    // Set Z to 1. Z == False
    state_->setF(0b00000000);

    ASSERT_EQ(Execute28(this->state_), 8);
    ASSERT_EQ(this->state_->programCounter(), this->program_counter_ + 2);
}

TEST_F(OpCodesTest, TestExecute28_JumpForward) {
    int8_t jump = 42;
    // Set Z to 1.
    state_->setF(0b10000000);
    state_->SetMemoryAt(state_->programCounter() + 1, jump);

    ASSERT_EQ(Execute28(this->state_), 12);
    ASSERT_EQ(this->state_->programCounter(), this->program_counter_ + jump);
}

TEST_F(OpCodesTest, TestExecute28_JumpBack) {
    int8_t jump = -10;
    // Set Z to 0. Z == True
    state_->setF(0b10000000);
    state_->SetMemoryAt(state_->programCounter() + 1, jump);

    ASSERT_EQ(Execute28(this->state_), 12);
    ASSERT_EQ(this->state_->programCounter(), this->program_counter_ + jump);
}

TEST_F(OpCodesTest, TestExecute38_NoJump) {
    // Set Z to 1. Z == False
    state_->setF(0b00000000);

    ASSERT_EQ(Execute38(this->state_), 8);
    ASSERT_EQ(this->state_->programCounter(), this->program_counter_ + 2);
}

TEST_F(OpCodesTest, TestExecute38_JumpForward) {
    int8_t jump = 42;
    // Set Z to 1.
    state_->setF(0b00010000);
    state_->SetMemoryAt(state_->programCounter() + 1, jump);

    ASSERT_EQ(Execute38(this->state_), 12);
    ASSERT_EQ(this->state_->programCounter(), this->program_counter_ + jump);
}

TEST_F(OpCodesTest, TestExecute38_JumpBack) {
    int8_t jump = -10;
    // Set Z to 0. Z == True
    state_->setF(0b00010000);
    state_->SetMemoryAt(state_->programCounter() + 1, jump);

    ASSERT_EQ(Execute38(this->state_), 12);
    ASSERT_EQ(this->state_->programCounter(), this->program_counter_ + jump);
}

}  // namespace

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}