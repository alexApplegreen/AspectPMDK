#include "pstack_cpp.h"
#include "util/log.h"

#include <libpmemobj++/pool.hpp>

#define POOL "./mempooltest"

int tests();

int main(int argc, char const *argv[]) {

    if (tests() == 0) {
        log_info("All tests passed");
    }
    else {
        log_warn("Some tests failed");
    }

    return 0;
}

int tests() {

    int passed = 0;

    pmem::obj::pool<PStack> pop;
    try {
        pop = pmem::obj::pool<PStack>::open(POOL, "");
    }
    catch (pmem::pool_error e) {
        log_error("Cannot open pool");
    }

    try {
        PStack* stack = pop.pmem::obj::pool<PStack>::root().get();

        if (stack->isEmpty()) {
            passed--;
            log_error("Stack is Empty");
        }
    }
    catch (pmem::pool_error e) {
        log_error("Cannot get root object");
    }

    return passed;
}
