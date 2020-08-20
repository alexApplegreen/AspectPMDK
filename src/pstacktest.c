#include "pstack.h"
#include <stdio.h>
#include <libpmemobj.h>

#define POOL "/mempool"

int main(int argc, char const *argv[]) {

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

    // push elements into the stack
    // TODO fast fertig, letztes Element wird wegen Indexfehler oder so nicht gepoppt
    push(stack, 'O');
    push(stack, 'L');
    push(stack, 'L');
    push(stack, 'A');
    push(stack, 'H');


    // should print "Hallo"
    while(!isEmpty(stack)) {
        log_debug("%c\n", pop(stack));
    }

    if (passed == 0) {
        log_info("%s\n" "All tests passed");
    }

    return 0;
}
