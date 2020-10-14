#define CATCH_CONFIG_MAIN

#include "util/catch.hpp"
#include "stack.h"

Stack stack(10);

TEST_CASE("Get Instance", "[Stack]") {
    REQUIRE(stack.isEmpty());
}

TEST_CASE("Can push", "[Stack]") {
    stack.push('O');
    REQUIRE(!stack.isEmpty());
}

TEST_CASE("Can pop", "[Stack]") {
    char elem = stack.pop();
    REQUIRE(elem == 'O');
}

TEST_CASE("Is empty again", "[Stack]") {
    REQUIRE(stack.isEmpty());
}
