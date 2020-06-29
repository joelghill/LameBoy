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

    // If the constructor and destructor are not enough for setting up
    // and cleaning up each test, you can define the following methods:

    void SetUp() override {
        // Code here will be called immediately after the constructor (right
        // before each test).
        this->memory_ = new uint8_t[65536];
        this->state_ = new SM83State(this->memory_);
    }

    void TearDown() override {
        delete this->state_;
        delete this->memory_;
    }

  // Objects declared here can be used by all tests in the test suite for Foo.
};

TEST_F(OpCodesTest, TestExecute00) {
    uint16_t program_counter = 0x100;
    this->state_->setProgramCounter(program_counter);

    // Ensure that the
    ASSERT_EQ(Execute00(this->state_), 4);
    ASSERT_EQ(this->state_->programCounter(), program_counter + 1);
}

}  // namespace

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}