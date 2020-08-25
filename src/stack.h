/*!
   \file stack.h
   \brief Regular Stack implementation using an array
   \author Alexander Tepe
*/

#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct STACK {
    char*           elements;
    uint64_t        maxsize;
    uint64_t        counter;
};

/*!
   \brief Constructor which returns a pointer to a stack struct
   \param Size of Stack
   \return "Return of the function"
*/
struct STACK* getInstance(int size) {
    struct STACK* stack = malloc(sizeof(struct STACK));
    stack->maxsize = size;
    stack->elements = malloc(size * sizeof(char));
    stack->counter = 0;
    return stack;
}

/// adds element to stack
void push(struct STACK* stack, char elem) {
    if (stack->counter >= stack->maxsize) {
        printf("%s\n", "Stack is full!");
    }
    else {
        stack->elements[stack->counter] = elem;
        stack->elements++;
    }
}

/// gets element from stack according to FIFO principle
char pop(struct STACK* stack) {
    if (stack->counter == 0) {
        printf("%s\n", "Stack is empty");
    }
    else {
        char elem = stack->elements[stack->counter];
        stack->counter--;
        return elem;
    }
    return '0';
}

/*!
   \brief Checks if given Stack is empty
   \param Pointer to Stack
   \return 0 if stack is empty
*/
int isEmpty(struct STACK* stack) {
    return stack->counter == 0;
}
