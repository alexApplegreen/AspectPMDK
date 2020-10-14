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
        // TODO get stack from pool
        // stack = getInstance(10, pool);
    }
};
CATCH_REGISTER_LISTENER(MyListener)

TEST_CASE("is present", "[Stack]") {
    REQUIRE_FALSE(OID_IS_NULL(stack));
    REQUIRE_FALSE(isEmpty(stack));
}

TEST_CASE("contains right stuff", "[Stack]") {
    char hello[6];
    while(!isEmpty(stack)) {
        int i = 0;
        hello[i] = pop(stack);
    }
    hello[5] = '\0';
    REQUIRE(strcmp(hello, "HALLO") == 0);
}
