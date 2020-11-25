#include <libpmemobj++/pool.hpp>
#include <libpmemobj++/persistent_ptr.hpp>
#include <libpmemobj.h>
#include "aopstack_cpp.h"
#include "../util/log.h"
#include <iostream>
#include <stdexcept>

#define POOL "./mempooltestbafzigundzwei"

int tests();

int main(void) {
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

    pmem::obj::pool<Stack> pop;
    try {
        pop = pmem::obj::pool<Stack>::open(POOL, "");
    }
    catch (pmem::pool_error e) {
        log_error("Cannot find memory pool");
        return -1;
    }

    Stack* stack = pop.root().get();

    if (stack->isEmpty()) {
        log_error("Stack is Empty");
        return -1;
    }

    char hello[6];
    int i = 0;
    while(!stack->isEmpty()) {
        char elem = stack->pop();
        hello[i] = elem;
        i++;
    }
    hello[5] = '\0';

    if (strcmp(hello, "HALLO") != 0) {
        log_error("Stack enthält falsche Daten");
        passed--;
    }

    pop.close();
    return passed;
}
