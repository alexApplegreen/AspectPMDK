/*!
   \file pstack.h

   \brief implementation of Stack using arrays, Stack runnable on persistent
          memory by using PMDK transactions

   \author Alexander Tepe
*/

#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libpmemobj.h>

#define POOL_PATH "/mempool"

static PMEMobjpool* pool;

struct pstack {
    PMEMoid                 elements;
    uint64_t                maxsize;
    uint64_t                counter;
};

int init(PMEMobjpool* pool, void* ptr, void* args) {
    int size = (int)args;
    struct pstack* stack = (struct pstack*)ptr;
    struct pobj_action act[2];

    stack->maxsize = size;
    stack->counter = 0;
    stack->elements = pmemobj_reserve(pool, act + 0, size, 0);

    return 0;
}

// global TOID
TOID_DECLARE(struct pstack, 1);
TOID(struct pstack) pstack_oid;

/// Constructor
PMEMoid getInstance(int size) {

    // allocate persistent memory
    if (!(pool = pmemobj_create(POOL_PATH, " ", size * sizeof(char), 0666))) {
        perror("pmemobj_create");
        exit(1);
    }

    // initialize Stack
    pmemobj_alloc(pool, pstack_oid, sizeof(struct pstack), 1, init, (void*)size);

    PMEMoid pstack;
    TOID_ASSIGN(pstack_oid, pstack);
    return pstack;
}
