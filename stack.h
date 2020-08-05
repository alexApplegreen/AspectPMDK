/*!
   \file stack.h
   \brief Regular Stack implementation using an array
   \author Alexander Tepe
*/

#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct stack {
    char*       elements;
    char        top;
    uint64_t    maxsize;
    uint64_t    counter;
};

/*!
   \brief Constructor which returns a pointer to a stack struct
   \param Size of Stack
   \return "Return of the function"
*/
struct stack* getInstance(int size) {
    struct stack* stack = malloc(sizeof(struct stack));
    stack->maxsize = size;
    stack->elements = malloc(size * sizeof(char));
    stack->counter = 0;
    return stack;
}

/// adds element to stack
void push(struct stack* stack, char elem) {
    if (stack->counter >= stack->maxsize) {
        printf("%s\n", "Stack is full!");
    }
    else {
        stack->elements[++stack->counter] = *strdup(&elem);
    }
}

/// gets element from stack according to FIFO principle
char pop(struct stack* stack) {
    if (stack->counter <= 0) {
        printf("%s\n", "Stack is empty");
    }
    else {
        char elem = stack->elements[stack->counter];
        stack->counter--;
        return elem;
    }
    return NULL;
}

/*!
   \brief Checks if given Stack is empty
   \param Pointer to Stack
   \return 0 if stack is empty
*/
int isEmpty(struct stack* stack) {
    return stack->counter == 0;
}
