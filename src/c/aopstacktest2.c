#include <libpmemobj.h>
#include "aopstack.h"
#include "../util/log.h"

#define POOL "/mnt/pm_n1_ni/at/aopstack"
#define LAYOUT "STACK"

int main(int argc, char const *argv[]) {

    int passed = 0;

    PMEMobjpool* pool;
    if (!(pool = pmemobj_open(POOL, LAYOUT))) {
        log_error("Cannot open pool");
        return -1;
    }

    // ZU diesem Zeitpunkt muss Stack schon im Speicher existieren, also kein zweiter Parameter
    PMEMoid stack = pmemobj_root(pool, pmemobj_root_size(pool));



    if (OID_IS_NULL(stack)) {
        perror("pmemobj_root");
        return -1;
    }

    if (isEmpty(stack)) {
        passed--;
        log_error("Stack is empty");
        return 0;
    }

    // sollte HALLO printen
    // Hier geht es kaputt
    while(!isEmpty(stack)) {
        printf("%c\n", pop(stack));
    }
    pmemobj_close(pool);
    return 0;
}
