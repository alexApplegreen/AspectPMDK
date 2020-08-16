#include "pstack.h"
#include <stdio.h>
#include <libpmemobj.h>

int main(int argc, char const *argv[]) {

    PMEMobjpool* pool;
    if (!(pool = pmemobj_create(/* TODO */))) {
        if (!(pool = pmemobj_create(/* TODO */))) {
            perror("pmemobj_create");
            exit(-1);
        }
    }

    PMEMoid stack = getInstance(10, pool);
    if (OID_IS_NULL(stack)) {
        printf("%s\n", "Error");
    }
    return 0;
}
