#define POOL "./mempooltestdroelf"

#include "pstack_cpp.h"
#include "util/log.h"
#include "util/catch.hpp"
#include <libpmemobj++/pool.hpp>

pmem::obj::pool<PStack> pop;
PStack* stack;

struct MyListener : Catch::TestEventListenerBase {

    using TestEventListenerBase::TestEventListenerBase;

    void testRunStarting(Catch::TestRunInfo const& testRunInfo) override {
        try {
            pop = pmem::obj::pool<PStack>::open(POOL, "");
        }
        catch (pmem::pool_error e) {
            log_error("cannot open pool");
        }

        stack = pop.root().get();
    }

    void testRunEnded(Catch::TestRunStats const& testRunStats) override {
        while(!stack->isEmpty()) {
            stack->pop();
        }
        pop.close();
    }
};
CATCH_REGISTER_LISTENER(MyListener)

TEST_CASE("contains Data", "[Stack]") {
    REQUIRE_FALSE(stack->isEmpty());
}

TEST_CASE("contains correct data", "[Stack]") {
    char hallo[6];
    int i = 0;
    while(!stack->isEmpty()) {
        hallo[i] = stack->pop();
        i++;
    }
    hallo[5] = '\0';

    REQUIRE(strcmp(hallo, "HALLO") == 0);
}
