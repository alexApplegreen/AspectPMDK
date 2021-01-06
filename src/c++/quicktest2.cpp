#include <libpmemobj++/pool.hpp>
#include <libpmemobj++/persistent_ptr.hpp>
#include <libpmemobj.h>
#include "aopstack_cpp.h"
#include "../util/log.h"
#include <iostream>
#include <stdexcept>

#define POOL "/mnt/pm_n1_ni/at/stack"

void tests();

int main(void) {
    tests();
}

void tests() {

    pmem::obj::pool<Stack> pop;
    try {
        pop = pmem::obj::pool<Stack>::open(POOL, "");
    }
    catch (pmem::pool_error e) {
        log_error("Cannot find memory pool");
    }

    Stack* stack = pop.root().get();

    while(!stack->isEmpty()) {
        stack->pop();
    }

    pop.close();
}
