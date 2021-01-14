#include "aopvector.h"
#include "../util/log.h"
#include <libpmemobj++/pool.hpp>
#include <libpmemobj++/persistent_ptr.hpp>
#include <libpmemobj++/transaction.hpp>
#include <libpmemobj++/make_persistent.hpp>
#include <libpmemobj.h>
#include <cstdlib>

#define POOL "/mnt/pm_n1_ni/at/vector"

int main(int argc, char const *argv[]) {

    pmem::obj::pool<aopvector> pop;
    try {
        pop = pmem::obj::pool<aopvector>::create(POOL, "", PMEMOBJ_MIN_POOL);
    }
    catch (pmem::pool_error e) {
        pop = pmem::obj::pool<aopvector>::open(POOL, "");
    }

    pmem::obj::persistent_ptr<aopvector> root = pop.root();
    pmem::obj::transaction::run(pop, [&] {
        root = pmem::obj::make_persistent<aopvector>();
    });

    aopvector* vector = pop.root().get();
    vector->init();
    srand(0);

    for (int i = 0; i < 100; i++) {
        char rand = 'a' + std::rand() % 26;
        vector->add(rand);
    }
    pop.close();
    return 0;
}
