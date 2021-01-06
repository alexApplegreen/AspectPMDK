#include "aopqueue.h"
#include "../util/log.h"
#include <libpmemobj++/pool.hpp>
#include <libpmemobj++/persistent_ptr.hpp>
#include <libpmemobj.h>

#define POOL "/mnt/pm_n1_ni/at/queue"

void tests();

int main(void) {

    tests();
    return 0;
}

void tests() {

    pmem::obj::pool<LinkedQueue> pop;
    try {
        pop = pmem::obj::pool<LinkedQueue>::open(POOL, "");
    }
    catch (pmem::pool_error e) {
        log_error("Cannot open pool");
    }

    LinkedQueue* queue = pop.root().get();

    while(!queue->isEmpty()) {
        queue->dequeue();
    }

    pop.close();
}
