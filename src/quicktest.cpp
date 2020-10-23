#include "pstack_cpp.h"
#include "util/log.h"
#include <libpmemobj++/pool.hpp>
#include <libpmemobj.h>
#include <iostream>
#include <stdexcept>

#define POOL "./mempooltestbafzigundeins"

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
    pmem::obj::pool<PStack> pop;
    try {
        pop = pmem::obj::pool<PStack>::create(POOL, "", PMEMOBJ_MIN_POOL);
    }
    catch (pmem::pool_error e) {
        pop = pmem::obj::pool<PStack>::open(POOL, "");
    }

    auto root = pop.root();
    *root = PStack(10);
    PStack* stack = pop.root().get();

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

    std::invalid_argument* e;
    try {
        *root = PStack(2048);
    }
    catch (std::invalid_argument* ex) {
        e = ex;
        if (strcmp(e->what(), "Stacksize exceeds 1 kB") != 0) {
            passed--;
            log_error("invalid argument not thrown");
        }
    }

    *root = PStack();
    stack = pop.root().get();

    std::runtime_error* error;
    try {
        for (int i = 0; i < STACK_MAXSIZE + 1; i++) {
            stack->push('X');
        }
    }
    catch (std::runtime_error e) {
        error = &e;
        if (strcmp(error->what(), "Stack is full") != 0) {
            passed--;
            log_info("runtime error not thrown");
        }
    }

    pop.close();
    return passed;
}
