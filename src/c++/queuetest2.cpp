#include "aopqueue.h"
#include "../util/log.h"
#include <libpmemobj++/pool.hpp>
#include <libpmemobj++/persistent_ptr.hpp>
#include <libpmemobj.h>

#define POOL "/mnt/pm_n0_int/at/queue"

int tests();

int main(void) {

    switch (tests()) {
        case 0 : log_info("All tests passed"); break;
        case 1 : log_info("Tests interrupted"); break;
        default : log_warn("Some tests failed"); break;
    }

    return 0;
}

int tests() {

    int passed = 0;

    pmem::obj::pool<LinkedQueue> pop;
    try {
        pop = pmem::obj::pool<LinkedQueue>::open(POOL, "");
    }
    catch (pmem::pool_error e) {
        log_error("Cannot open pool");
        return 1;
    }

    LinkedQueue* queue = pop.root().get();

    if (queue->isEmpty()) {
        log_error("queue is empty");
        return -1;
    }

    while(!queue->isEmpty()) {
        log_debug("Message from queue: %c", queue->dequeue());
    }

    pop.close();
    return passed;
}
