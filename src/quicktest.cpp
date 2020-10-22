#include "pstack_cpp.h"
#include "util/log.h"
#include <libpmemobj++/pool.hpp>
#include <libpmemobj.h>
#include <iostream>

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
    pmem::obj::persistent_ptr<PStack> stack_p = new PStack(10);

    // reicht das, um Stack zu erzeugen und als Root zu speichern?
    root = stack_p;

    PStack* stack = pop.root().get();

    if (!stack->isEmpty()) {
        passed--;
        log_error("Stack is not Empty initially");
    }

    // Exception: Stack is full?
    stack->push('A');

    char result = stack->pop();
    if (result != 'A') {
        passed--;
        log_error("pushing / popping does not work");
    }
    pop.close();
    return passed;
}
