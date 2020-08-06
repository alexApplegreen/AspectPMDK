#include "pstack.h"
#include <stdio.h>
#include <libpmemobj.h>

int passed = 0;

int main(int argc, char const *argv[]) {
    PMEMoid pstack = getInstance(10);

    return 0;
}
