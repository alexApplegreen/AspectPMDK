#include "aopqueue.h"
#include "../util/log.h"
#include <libpmemobj++/pool.hpp>
#include <libpmemobj++/persistent_ptr.hpp>
#include <libpmemobj.h>

#define POOL "/mnt/pm_n0_int/at/pqueue"

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
    pmem::obj::transaction::run(pop, [&] {
        *root = LinkedQueue();
    });

    LinkedQueue* queue = pop.root().get();

    int passed = 0;

    // test if queue is initially empty
    if (!queue->isEmpty()) {
        passed--;
        log_error("Queue is not empty initially");
    }

    // enqueue one char and check if it can be obtained
    queue->enqueue('B');

    if (queue->dequeue() != 'B') {
        passed--;
        log_error("Enqueueing / dequeueing does not work");
    }

    // check if queue is empty after dequeueing last element
    if (!queue->isEmpty()) {
        passed--;
        log_error("Queue is not empty after dequeueing");
    }

    // enqueue "HALLO" for subsequent tests
    // FIXME erster enqueue is hier irgendwie wirkungslos?
    queue->enqueue('H');
    queue->enqueue('A');
    queue->enqueue('L');
    queue->enqueue('L');
    queue->enqueue('O');

    pop.close();

    return passed;
}
