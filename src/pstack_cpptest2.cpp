#define CATCH_CONFIG_MAIN
#define POOL "./mempooltestdroelf"

#include "pstack_cpp.h"
#include "util/log.h"
#include "util/catch.hpp"
#include <libpmemobj++/pool.hpp>

pmem::obj::pool<PStack> pop;

struct MyListener : Catch::TestEventListenerBase {

    using TestEventListenerBase::TestEventListenerBase;

    void testRunStarting(Catch::TestRunInfo const& testRunInfo) override {
        try {
            pop = pmem::obj::pool<PStack>::open(POOL, "");
        }
        catch (pmem::pool_error e) {
            log_error("cannot open pool");
        }
    }

    void testRunEnded(Catch::TestRunStats const& testRunStats) override {
        while(!pop.root().get()->isEmpty()) {
            pop.root().get()->pop();
        }
        pop.persist(pop.root());
        pop.close();
    }
};
CATCH_REGISTER_LISTENER(MyListener)

TEST_CASE("contains Data", "[Stack]") {
    REQUIRE_FALSE(pop.root().get()->isEmpty());
}

TEST_CASE("contains correct data", "[Stack]") {
    char hallo[6];
    while(!pop.root().get()->isEmpty()) {
        int i = 0;
        hallo[i] = pop.root().get()->pop();
        i++;
    }
    hallo[5] = '\0';

    REQUIRE(strcmp(hallo, "HALLO") == 0);
}
