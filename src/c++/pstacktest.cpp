#define CATCH_CONFIG_EXTERNAL_INTERFACES
#define POOL "./pstacktest"
#define POOL_TEST "./pstacktestinternal"

#include "../util/log.h"
#include "pstack.h"
#include <libpmemobj++/pool.hpp>
#include <libpmemobj.h>
#include <stdexcept>
#include "../util/catch.hpp"

pmem::obj::pool<PStack> pop;
PStack* stack;

struct MyListener : Catch::TestEventListenerBase {

    using TestEventListenerBase::TestEventListenerBase;

    void testRunStarting(Catch::TestRunInfo const& testRunInfo) override {
        try {
            pop = pmem::obj::pool<PStack>::create(POOL, "", PMEMOBJ_MIN_POOL);
        }
        catch (pmem::pool_error e) {
            pop = pmem::obj::pool<PStack>::open(POOL, "");
        }

        auto root = pop.root();
        *root = PStack(10);
        stack = pop.root().get();
    }

    void testCaseStarting(Catch::TestCaseInfo const& testInfo) override {
        while(!stack->isEmpty()) {
            stack->pop();
        }
    }

    void testRunEnded(Catch::TestRunStats const& testRunStats) override {
        // prep persistent Stack for subsequent test of persistent properties
        stack->push('O');
        stack->push('L');
        stack->push('L');
        stack->push('A');
        stack->push('H');

        pop.close();
    }
};
CATCH_REGISTER_LISTENER(MyListener)

TEST_CASE("is empty initially", "[Stack]") {
    REQUIRE(stack->isEmpty());
}

// funktioniert
TEST_CASE("Can push / pop", "[Stack]") {
    stack->push('A');
    REQUIRE_FALSE(stack->isEmpty());

    char elem = stack->pop();
    REQUIRE(elem == 'A');
}

TEST_CASE("FIFO Works", "[Stack]") {
    stack->push('O');
    stack->push('L');
    stack->push('L');
    stack->push('A');
    stack->push('H');

    char hallo[6];
    int i = 0;
    while(!stack->isEmpty()) {
        hallo[i] = stack->pop();
        i++;
    }
    hallo[5] = '\0';

    REQUIRE(strcmp(hallo, "HALLO") == 0);
}

TEST_CASE("Constructor Tests", "[Stack]") {

    auto root = pop.root();
    SECTION("Constructor throws Exception") {
        REQUIRE_THROWS_AS([&]() {
            *root = PStack(STACK_MAXSIZE + 1);
        }(), std::invalid_argument*);

        *root = PStack(10);
        stack = pop.root().get();
    }

    SECTION("Constructor delegation works") {
        auto root = pop.root();
        *root = PStack(1024);
        stack = pop.root().get();

        REQUIRE_THROWS_AS([&]() {
            for (int i = 0; i < STACK_MAXSIZE + 1; i++) {
                stack->push('X');
            }
        }(), std::runtime_error);


        *root = PStack(10);
        stack = pop.root().get();
    }
}
