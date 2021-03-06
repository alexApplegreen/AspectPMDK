#include <libpmemobj++/pool.hpp>
#include <libpmemobj++/persistent_ptr.hpp>
#include <libpmemobj++/make_persistent.hpp>
#include <libpmemobj++/transaction.hpp>
#include <libpmemobj.h>
#include "../datastructures/aopstack.h"
#include "../util/log.h"
#include <iostream>
#include <stdexcept>
#include <cstdlib>

#define POOL "stacktest"

void tests();

int main(int argc, char const *argv[]) {
    tests();
}

void tests() {
    pmem::obj::pool<Stack> pop;
    try {
        pop = pmem::obj::pool<Stack>::create(POOL, "", PMEMOBJ_MIN_POOL);
    }
    catch (pmem::pool_error e) {
        pop = pmem::obj::pool<Stack>::open(POOL, "");
    }

    pmem::obj::persistent_ptr<Stack> root = pop.root();
    *root = Stack();
    Stack* stack = pop.root().get();

    srand(0);

    for (int i = 0; i < 100; i++) {
        char rand = 'a' + std::rand() % 26;
        stack->push(rand);
    }

    pop.close();
}
