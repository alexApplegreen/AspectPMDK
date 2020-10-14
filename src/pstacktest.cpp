#define CATCH_CONFIG_MAIN
#define POOL "/mempool"

#include "pstack.h"
#include <stdio.h>
#include <libpmemobj.h>
#include <string.h>
#include "util/catch.hpp"

PMEMobjpool* pool;
PMEMoid stack;

struct MyListener : Catch::TestEventListenerBase {

    using TestEventListenerBase::TestEventListenerBase;

    void testRunStarting(Catch::TestRunInfo const& testRunInfo) override {
        if (!(pool = pmemobj_open(POOL, ""))) {
            if (!(pool = pmemobj_create(POOL, "", PMEMOBJ_MIN_POOL, 0666))) {
                perror("pmemobj_create");
                exit(-1);
            }
        }
        stack = getInstance(10, pool);
    }

    void testCaseStarting(Catch::TestCaseInfo const& testInfo) override {
        while(!isEmpty(stack)) {
            pop(stack);
        }
    }

    void testRunEnded(Catch::TestRunStats const& testRunStats) override {
        // prep persistent Stack for subsequent test of persistent properties
        push(stack, 'O');
        push(stack, 'L');
        push(stack, 'L');
        push(stack, 'A');
        push(stack, 'H');
    }
};
CATCH_REGISTER_LISTENER(MyListener)

TEST_CASE("Get instance", "[Stack]") {
    REQUIRE(!OID_IS_NULL(stack));
    REQUIRE(isEmpty(stack));
}

TEST_CASE("Can push / pop", "[Stack]") {
    push(stack, 'O');
    REQUIRE(!isEmpty(stack));
    char elem = pop(stack);
    REQUIRE(elem == 'O');
}

TEST_CASE("FIFO works", "[Stack]") {
    push(stack, 'O');
    push(stack, 'L');
    push(stack, 'L');
    push(stack, 'A');
    push(stack, 'H');
    REQUIRE(!isEmpty(stack));

    char hello[6];
    // should print "Hallo"
    for (int i = 0; i < 5; i++) {
        hello[i] = pop(stack);
    }
    hello[5] = '\0';

    REQUIRE(strcmp(hello, "HALLO") == 0);
    REQUIRE(isEmpty(stack));
}
