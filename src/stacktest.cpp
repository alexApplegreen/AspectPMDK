#include "stack.h"
#include <stdio.h>
#include "util/log.h"

int passed = 0;

int main(int argc, char const *argv[]) {

    // init stack
    Stack stack(10);

    // push too many elements
    char elem = 'A';
    bool exception = false;
    try {
        for (int i = 0; i < 11; i++) {
            stack.push(elem);
        }
    }
    catch (std::runtime_error) {
        exception = true;
    }

    if (!exception) {
        passed--;
        log_error("Exception not thrown");
    }
    exception = false;

    if (passed == 0) {
        log_info("All tests passed");
    }

    try {
        for (int i = 0; i < 11; i++) {
            stack.pop();
        }
    }
    catch (std::runtime_error) {
        exception = true;
    }

    if (!exception) {
        passed--;
        log_error("Exception not thrown");
    }

    

    return 0;
}
