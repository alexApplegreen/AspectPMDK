#include "stack.h"
#include <stdio.h>

int passed = 0;

int main(int argc, char const *argv[]) {

    // init stack
    struct stack* stack = getInstance(10);
    if (stack == NULL) {
        printf("%s\n", "Stack is NULL!");
        passed--;
    }

    // push too many elements
    char elem = 'A';
    for (int i = 0; i < 11; i++) {
        push(stack, elem);
    }
    if (stack->counter > 10) {
        printf("%s\n", "Can push too many elements!");
        passed--;
    }

    // pop too many elements
    for (int i = 0; i < 11; i++) {
        pop(stack);
    }
    if (stack->counter < 0) {
        printf("%s\n", "Stack counter is negative!");
        passed--;
    }

    // push elements regularly
    push(stack, 'A');
    if (stack->counter != 1) {
        printf("%s\n", "Cannot push to Stack");
        passed--;
    }
    else {
        char elem = pop(stack);
        if (elem != 'A') {
            printf("%s\n", "Cannot pull Data from Stack!");
            passed--;
        }
    }

    if (passed == 0) {
        printf("%s\n", "ALL PASSED");
    }

    return 0;
}
