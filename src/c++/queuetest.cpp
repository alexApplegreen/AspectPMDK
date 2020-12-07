#include "aopqueue.h"
#include "../util/log.h"
#include <libpmemobj++/pool.hpp>
#include <libpmemobj++/persistent_ptr.hpp>
#include <libpmemobj.h>

#define POOL "mempoolqueue"

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

    pmem::obj::pool<LinkedQueue> pop;
    try {
        pop = pmem::obj::pool<LinkedQueue>::create(POOL, "", PMEMOBJ_MIN_POOL);
    }
    catch (pmem::pool_error e) {
        pop = pmem::obj::pool<LinkedQueue>::open(POOL, "");
    }

    pmem::obj::persistent_ptr<LinkedQueue> root = pop.root();
    *root = LinkedQueue();

    LinkedQueue* queue = pop.root().get();

    int passed = 0;

    if (!queue->isEmpty()) {
        passed--;
        log_warn("Queue is not empty initially");
    }

    queue->enqueue('H');

    if (queue->dequeue() != 'H') {
        passed--;
        log_warn("Enqueueing / dequeueing does not work");
    }

    if (!queue->isEmpty()) {
        passed--;
        log_warn("Queue is not empty after dequeueing");
    }

    queue->enqueue('H');
    queue->enqueue('A');
    queue->enqueue('L');
    queue->enqueue('L');
    queue->enqueue('O');

    pop.close();

    return passed;
}
