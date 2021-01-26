#include <libpmemobj++/pool.hpp>
#include <libpmemobj++/persistent_ptr.hpp>
#include <libpmemobj++/make_persistent.hpp>
#include <libpmemobj++/transaction.hpp>
#include <libpmemobj.h>
#include "pstack_cpp.h"
#include "../util/log.h"
#include <iostream>
#include <stdexcept>
#include <cstdlib>

#define POOL "aopstacktest"

void tests();

int main(int argc, char const *argv[]) {
    tests();
}

void tests() {
    pmem::obj::pool<PStack> pop;
    try {
        pop = pmem::obj::pool<PStack>::create(POOL, "", PMEMOBJ_MIN_POOL);
    }
    catch (pmem::pool_error e) {
        pop = pmem::obj::pool<PStack>::open(POOL, "");
    }

    pmem::obj::persistent_ptr<PStack> root = pop.root();
    pmem::obj::transaction::run(pop, [&] {
        root = pmem::obj::make_persistent<PStack>(10);
    });
    PStack* stack = pop.root().get();

    srand(0);

    for (int i = 0; i < 100; i++) {
        char rand = 'a' + std::rand() % 26;
        stack->push(rand);
        // stack->pop();
    }

    pop.close();
}
