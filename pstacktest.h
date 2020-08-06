#include "pstack.h"
#include <stdio.h>

int passed = 0;

int main(int argc, char const *argv[]) {
    struct pstack* pstack = getInstance(10);

    if (pstack == NULL) {
        printf("%s\n", "Stack is Null!");
        passed--;
    }
    else {
        // Elemente in den Stack packen
        for (int i = 0; i < 11; i++) {
            push(pstack, 'A');
        }
        if (pstack->counter == 11) {
            printf("%s\n", "Can push too many elements!");
            passed--;
        }

        // clear too many elements
        for (int i = 0; i < 11; i++) {
            pop(pstack);
        }
        if (pstack->counter != 0) {
            printf("%s\n", "Can clear too many elements");
            passed--;
        }

        // push two and check for them
        push(pstack, 'B');
        push(pstack, 'A');

        if (pop(pstack) != 'A') {
            passed--
        }
        if (pop(pstack) != 'B') {
            passed--;
        }
        printf("%s\n", "FIFO does not work!");
    }

    if (passed == 0) {
        printf("%s\n", "ALL PASSED");
    }

    return 0;
}
