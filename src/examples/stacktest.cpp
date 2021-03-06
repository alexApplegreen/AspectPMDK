#define CATCH_CONFIG_EXTERNAL_INTERFACES

#include "../util/catch.hpp"
#include "../datastructures/stack.h"
#include <stdexcept>

Stack stack(10);

struct MyListener : Catch::TestEventListenerBase {

    using TestEventListenerBase::TestEventListenerBase;

    void testCaseEnded(Catch::TestCaseStats const& testCaseStats) override {
        while(!stack.isEmpty()) {
            stack.pop();
        }
    }
};
CATCH_REGISTER_LISTENER(MyListener)

TEST_CASE("Get Instance", "[Stack]") {
    REQUIRE(stack.isEmpty());
}

TEST_CASE("Can push / pop", "[Stack]") {
    stack.push('O');
    REQUIRE_FALSE(stack.isEmpty());
    char elem = stack.pop();
    REQUIRE(elem == 'O');
    REQUIRE(stack.isEmpty());
}

TEST_CASE("push throws exception", "[Stack]") {
    REQUIRE_THROWS_WITH([&]() {
        for (int i = 0; i < 11; i++) {
            stack.push('A');
        }
    }(), "Stack is full");
}

TEST_CASE("pop throws exception", "[Stack]") {
    REQUIRE_THROWS_WITH(stack.pop(), "Stack is empty");
}

TEST_CASE("LIFO works", "[Stack]") {
    stack.push('O');
    stack.push('L');
    stack.push('L');
    stack.push('A');
    stack.push('H');

    char hello[6];
    int i = 0;
    while(!stack.isEmpty()) {
        hello[i] = stack.pop();
        i++;
    }
    hello[5] = '\0';
    REQUIRE(strcmp(hello, "HALLO") == 0);
}
