#include "misc.h"
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>

struct stack {
    char* elements;
    char top;
    uint64_t maxsize;
    uint64_t counter;
};

struct stack* getInstance(int size) {
    struct stack* stack = malloc(sizeof(struct stack));
    stack->maxsize = size;
    stack->elements = malloc(size * sizeof(char));
    stack->counter = 0;

    return stack;
}

void push(struct stack* stack, char elem) {
    if (stack->counter >= stack->maxsize) {
        printf("%s\n", "Stack is full!");
    }
    else {
        stack->elements[stack->counter] = elem;
        stack->counter++;
    }
}

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

BOOL isEmpty(struct stack* stack) {
    return stack->counter == 0;
}
