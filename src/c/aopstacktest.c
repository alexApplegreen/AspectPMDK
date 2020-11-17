#include "aopstack.h"
#include <stdio.h>
#include <libpmemobj.h>
#include <string.h>
#include "../util/log.h"

#define POOL "/mempool2"
#define LAYOUT "STACK"

int tests();

int main(int argc, char const *argv[]) {

    if (tests() == 0) {
        log_info("All tests passed");
    }
    else {
        log_info("Some tests have failed");
    }
}

int tests() {

    int passed = 0;
    // create memorypool
    PMEMobjpool* pool;
    if (!(pool = pmemobj_open(POOL, LAYOUT))) {
        if (!(pool = pmemobj_create(POOL, LAYOUT, PMEMOBJ_MIN_POOL, 0666))) {
            perror("pmemobj_create");
            exit(-1);
        }
    }

    // Instanz erzeugen, Konstruktor ruft pmemobj_root() auf
    PMEMoid stack = getInstance(10, pool);

    if (OID_IS_NULL(stack)) {
        passed--;
        log_error("Stack cannot be created, exiting");
        return passed;
    }

    // push elements into the stack
    push(stack, 'O');
    push(stack, 'L');
    push(stack, 'L');
    push(stack, 'A');
    push(stack, 'H');

    if (isEmpty(stack)) {
        passed--;
        log_error("Stack is Empty after pushing inside");
    }

    return passed;
}
