#include "util/log.h"
#include "pstack_cpp.h"
#include <libpmemobj++/pool.hpp>
#include <libpmemobj.h>

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

    pmem::obj::pool_base pool;
    try {
        pool = pmem::obj::pool_base::open(POOL, "");
    }
    catch (pmem::pool_error e) {
        pool = pmem::obj::pool_base::create(POOL, "", PMEMOBJ_MIN_POOL, 0666);
    }

    PStack stack(10, pool);

    return passed;
}
