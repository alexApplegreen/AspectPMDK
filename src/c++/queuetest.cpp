#include "aopqueue.h"
#include "../util/log.h"
#include <libpmemobj++/pool.hpp>
#include <libpmemobj++/persistent_ptr.hpp>
#include <libpmemobj.h>
#include <cstdlib>

#define POOL "/mnt/pm_n1_ni/at/queue"

void tests();

int main(void) {

    tests();

    return 0;
}

void tests() {

    pmem::obj::pool<LinkedQueue> pop;
    try {
        pop = pmem::obj::pool<LinkedQueue>::create(POOL, "", 8388608);
    }
    catch (pmem::pool_error e) {
        log_error(e.what());
        pop = pmem::obj::pool<LinkedQueue>::open(POOL, "");
    }

    pmem::obj::persistent_ptr<LinkedQueue> root = pop.root();
    pmem::obj::transaction::run(pop, [&] {
        root = pmem::obj::make_persistent<LinkedQueue>();
    });

    LinkedQueue* queue = pop.root().get();

    srand(0);

    for (int i = 0; i < 100000; i++) {
        char rand = 'a' + std::rand() % 26;
        queue->enqueue(rand);
        queue->dequeue();
    }
    pop.close();

}
