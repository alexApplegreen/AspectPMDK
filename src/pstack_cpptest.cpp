#include "util/log.h"
#include "pstack_cpp.h"
#include <libpmemobj++/pool.hpp>
#include <libpmemobj.h>

#define POOL "./mempooltestdroelf"

// TODO kommt mir unschön vor.
struct root {
    PStack stack;
};

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

    PMEMobjpool* pool;
    if (!(pool = pmemobj_open(POOL, ""))) {
        if (!(pool = pmemobj_create(POOL, "", PMEMOBJ_MIN_POOL, 0666))) {
            perror("pmemobj_create");
            exit(-1);
        }
    }

    // TODO Das muss irgendwie schöner gehen
    auto pop = pmem::obj::pool_base(pool);
    PStack stack(10, pop);

    PMEMoid root_oid = pmemobj_root(pool, sizeof(struct root));
    struct root* root = (struct root*)pmemobj_direct(root_oid);

    // TODO ist das hier Quatsch?
    root->stack = stack;

    if (!stack.isEmpty()) {
        passed--;
        log_error("Stack is not empty initially");
    }

    stack.push('O');
    stack.push('L');
    stack.push('L');
    stack.push('A');
    stack.push('H');

    if (stack.isEmpty()) {
        log_error("Cannot push to stack");
        passed--;
    }

    return passed;
}
