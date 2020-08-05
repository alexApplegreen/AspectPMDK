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

struct stack {
    char*       elements;
    char        top;
    uint64_t    maxsize;
    uint64_t    counter;
};

/// Constructor
struct stack* getInstance(int size) {

    // allocate persistent memory
    if (!(pool = pmemobj_create(POOL, "", PMEMOBJ_POOL_MIN, 0666))) {
        printf("%s\n", "Cannot create memory pool");
        exit(1);
    }

    // initialize Stack
    struct stack* stack = malloc(sizeof(struct stack));
    stack->maxsize = size;
    stack->elements = malloc(size * sizeof(char));
    stack->counter = 0;
    return stack;
}

/// adds element to the stack
void push(struct stack* stack, char elem) {
    if (stack->counter >= stack->maxsize) {
        printf("%s\n", "Stack is full!");
    }
    else {
        TX_BEGIN(pool) {
            TX_ADD_DIRECT(stack->elements);
            TX_ADD_DIRECT(stack->counter);

            stack->elements[++stack->counter] = *strdup(&elem);
        } TX_END

    }
}

/// gets element from stack and deletes it according to FIFO principle
char pop(struct stack* stack) {
    if (stack->counter <= 0) {
        printf("%s\n", "Stack is empty");
    }
    else {
        TX_BEGIN(pool) {
            TX_ADD_DIRECT(stack->elements);
            TX_ADD_DIRECT(stack->counter);
            TX_ADD_DIRECT(elem);
            
            char elem = stack->elements[stack->counter];
            stack->counter--;
            return elem;
        } TX_END

    }
    return NULL;
}

/// checks if given Stack is empty
int isEmpty(struct stack* stack) {
    return stack->counter == 0;
}
