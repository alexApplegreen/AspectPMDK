#define CATCH_CONFIG_MAIN
#define POOL "/mempooldroelf"

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
            log_error("Cannot find mempool");
            exit(-1);
        }
        stack = pmemobj_root(pool, pmemobj_root_size(pool));
        if (OID_IS_NULL(stack)) {
            perror("pmemobj_root");
            exit(-1);
        }
    }

    void testRunEnded(Catch::TestRunStats const& testRunStats) override {
        log_info("closing pool");
        pmemobj_close(pool);
    }
};
CATCH_REGISTER_LISTENER(MyListener)

TEST_CASE("is present", "[Stack]") {
    REQUIRE_FALSE(OID_IS_NULL(stack));
    REQUIRE_FALSE(isEmpty(stack));
}

TEST_CASE("contains right stuff", "[Stack]") {
    // TODO Segfault hier
    REQUIRE_FALSE(isEmpty(stack));
    char hello[6];
    for (int i = 0; i < 5; i++) {
        hello[i] = pop(stack);
    }
    hello[5] = '\0';

    REQUIRE(strcmp(hello, "HALLO") == 0);
    REQUIRE(isEmpty(stack));
}
