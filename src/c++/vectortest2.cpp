#include "aopvector.h"
#include "../util/log.h"
#include <libpmemobj++/pool.hpp>
#include <libpmemobj++/persistent_ptr.hpp>
#include <libpmemobj++/transaction.hpp>
#include <libpmemobj++/make_persistent.hpp>
#include <libpmemobj.h>

#define POOL "/mnt/pm_n1_ni/at/vectortest"

int main(int argc, char const *argv[]) {

    pmem::obj::pool<aopvector> pop;
    try {
        pop = pmem::obj::pool<aopvector>::open(POOL, "");
    }
    catch (pmem::pool_error e) {
        log_error("Cannot open pool");
    }

    aopvector* vector = pop.root().get();

    while(!vector->isEmpty()) {
        vector->get();
    }

    pop.close();
    return 0;
}
