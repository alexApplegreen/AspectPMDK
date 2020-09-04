#include <libpmemobj.h>
#include "aopstack.h"
#include "util/log.h"

int main(int argc, char const *argv[]) {

    int passed = 0;

    PMEMobjpool* pool;
    if (!(pool = pmemobj_open("/mempool", ""))) {
        log_error("Cannot open pool");
        return -1;
    }
    PMEMoid stack = pmemobj_root(pool, sizeof(struct pstack));

    if (OID_IS_NULL(stack)) {
        log_error("Stack cannot be found");
        return -1;
    }

    while(!isEmpty(stack)) {
        printf("%c\n", pop(stack));
    }
    return 0;
}
