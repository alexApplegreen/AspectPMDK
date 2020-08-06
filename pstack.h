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
#define TYPE "pstack"
#define TYPE_NUM 1

// global TOID
TOID_DECLARE(struct pstack, 1);
TOID(struct pstack) pstack_oid;

struct pstack {
    char*                   elements;
    char                    top;
    uint64_t                maxsize;
    uint64_t                counter;

    // Stack stores reference to it's own memory pool
    PMEMobjpool*            pool;
};

/// Constructor
struct pstack* getInstance(int size) {

    // initialize Stack
    struct pstack* stack = malloc(sizeof(struct pstack));

    D_RW(pstack_oid)->maxsize = size;
    D_RW(pstack_oid)->elements = malloc(size * sizeof(char));
    D_RW(pstack_oid)->counter = 0;

    // allocate persistent memory
    if (!(stack->pool = pmemobj_create(POOL_PATH, "", size * sizeof(char), 0666))) {
        perror("pmemobj_create");
        exit(1);
    }

    return stack;
}

/// adds element to the stack
void push(struct pstack* stack, char elem) {
    if (stack->counter >= stack->maxsize) {
        printf("%s\n", "Stack is full!");
    }
    else {
        TX_BEGIN(D_RW(pstack_oid)->pool) {
            TX_ADD_DIRECT(D_RW(pstack_oid)->elements);
            TX_ADD_DIRECT(&D_RW(pstack_oid)->counter);

            stack->elements[++stack->counter] = elem;
        } TX_END

    }
}

/// gets element from stack and deletes it according to FIFO principle
char pop(struct pstack* stack) {
    if (stack->counter <= 0) {
        printf("%s\n", "Stack is empty");
    }
    else {
        TX_BEGIN(stack->pool) {
            TX_ADD_DIRECT(D_RW(pstack_oid)->elements);
            TX_ADD_DIRECT(&D_RW(pstack_oid)->counter);

            char elem = stack->elements[stack->counter];

            stack->counter--;
            return elem;
        } TX_END

    }
    return NULL;
}

/// checks if given Stack is empty
int isEmpty(struct pstack* stack) {
    return stack->counter == 0;
}

/*!
   \brief Since structs do not define own destructors, it is in the Responsibility
          of the application developer to free persistent memory after the stack
          is out of scope.

   \param Pointer to the pstack
*/
void free_pool(struct pstack* stack) {
    pmemobj_close(stack->pool);
}
