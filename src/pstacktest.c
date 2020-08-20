#include "pstack.h"
#include <stdio.h>
#include <libpmemobj.h>
#include <string.h>

#define POOL "/mempool"

int tests();

int main(int argc, char const *argv[]) {

    if (tests() == 0) {
        log_info("All tests passed");
    }
    else {
        log_error("tests failed");
    }

}

int tests() {

    int passed = 0;
    // create memorypool
    PMEMobjpool* pool;
    if (!(pool = pmemobj_open(POOL, ""))) {
        if (!(pool = pmemobj_create(POOL, "", PMEMOBJ_MIN_POOL, 0600))) {
            perror("pmemobj_create");
            exit(-1);
        }
    }

    PMEMoid stack = getInstance(10, pool);

    if (OID_IS_NULL(stack)) {
        passed--;
        log_error("Stack cannot be created!");
        return passed;
    }

    // push elements into the stack
    push(stack, 'O');
    push(stack, 'L');
    push(stack, 'L');
    push(stack, 'A');
    push(stack, 'H');

    char hello[6];
    // should print "Hallo"
    for (int i = 0; i < 5; i++) {
        hello[i] = pop(stack);
    }
    hello[5] = '\0';

    if (strcmp(hello, "HALLO") != 0) {
        passed--;
        log_error("Pushing and popping does not work correctly");
    }

    if (!isEmpty(stack)) {
        passed--;
        log_error("Stack is not empty after popping all of its contents");
    }

    return passed;
}
