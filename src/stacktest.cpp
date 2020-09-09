#include "stack.h"
#include <stdio.h>
#include "util/log.h"
#include <gtest/gtest.h>


// The fixture for testing class Foo.
class StackTest : public ::testing::Test {

protected:

    void SetUp() override {
     // Code here will be called immediately after the constructor (right
     // before each test).
    }

    void TearDown() override {
     // Code here will be called immediately after each test (right
     // before the destructor).
    }

    // Class members declared here can be used by all tests in the test suite
    // for Foo.
    Stack stack(10);
};

    // Tests that Foo does Xyz.
    TEST_F(StackTest, DoesThings) {
        stack.push('A');
        EXPECT_EQ(stack.pop(), 'A');
    }


int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
