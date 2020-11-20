#include <libpmemobj++/pool.hpp>
#include <libpmemobj++/persistent_ptr.hpp>
#include <libpmemobj.h>
#include "aopstack_cpp.h"
#include "../util/log.h"
#include <iostream>
#include <stdexcept>

#define POOL "./mempooltestbafzigundzwei"

int tests();

int main(int argc, char const *argv[]) {
    if (tests() == 0) {
        log_info("All tests passed");
    }
    else {
        log_warn("some tests failed");
    }
    return 0;
}

int tests() {
    int passed = 0;
    pmem::obj::pool<Stack> pop;
    try {
        pop = pmem::obj::pool<Stack>::create(POOL, "", PMEMOBJ_MIN_POOL);
    }
    catch (pmem::pool_error e) {
        pop = pmem::obj::pool<Stack>::open(POOL, "");
    }

    pmem::obj::persistent_ptr<Stack> root = pop.root();
    *root = Stack(10);
    Stack* stack = pop.root().get();

    if (!stack->isEmpty()) {
        passed--;
        log_error("Stack is not Empty initially");
    }

    stack->push('A');

    char result = stack->pop();
    if (result != 'A') {
        passed--;
        log_error("pushing / popping does not work");
    }

    pop.close();
    return passed;
}
