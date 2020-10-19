#define POOL "./mempooltestdroelf"

#include "util/log.h"
#include "pstack_cpp.h"
#include <libpmemobj++/pool.hpp>
#include <libpmemobj.h>

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
        pop = pmem::obj::pool<PStack>::create(POOL, "", PMEMOBJ_MIN_POOL);
    }
    catch (pmem::pool_error e) {
        pop = pmem::obj::pool<PStack>::open(POOL, "");
    }

    pmem::obj::persistent_ptr<PStack> stack_ptr = pop.root();
    PStack* stack = stack_ptr.get();
    stack = new PStack(10);

    pop.persist(stack_ptr);

    if (!pop.root().get()->isEmpty()) {
        passed--;
        log_error("Stack is not empty initially");
    }

    pop.root().get()->push('O');
    pop.root().get()->push('L');
    pop.root().get()->push('L');
    pop.root().get()->push('A');
    pop.root().get()->push('H');

    if (pop.root().get()->isEmpty()) {
        log_error("Cannot push to stack");
        passed--;
    }

    pop.close();

    return passed;
}
