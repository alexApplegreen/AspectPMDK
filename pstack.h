/*!
   \file pstack.h

   \brief implementation of Stack using arrays, Stack runnable on persistent
          memory by using PMDK transactions

   \author Alexander Tepe
*/

#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libpmemobj.h>

// global TOIDs
TOID_DECLARE(struct pstack, 1);
TOID(struct pstack) pstack;

TOID_DECLARE(char, 2);
TOID(char) pelem;

static PMEMobjpool* pool;

struct pstack {
    uint64_t                maxsize;
    uint64_t                counter;
    char*                   elements;
};

/*!
   \brief internal constructor used for initialization of the Stack. This
          function is called by pmemobj_alloc() when requesting an instance
          of pstack. The Code inside of this function is executed like a transaction.

   \param pool pointer to the PMEMobjpool
          ptr void pointer to the stack
          args void pointer to the size of the stack


   \return 0 on successful completion
*/
int init(PMEMobjpool* pool, void* ptr, void* args) {
    int size = (int)args;
    PMEMoid stack_oid = pmemobj_oid(ptr);
    TOID_ASSIGN(pstack, stack_oid);

    D_RW(pstack)->maxsize = size;
    D_RW(pstack)->counter = 0;

    PMEMoid pelem_oid;
    TOID_ASSIGN(pelem, pelem_oid);
    pmemobj_alloc(pool, &pelem_oid, size * sizeof(char), 2, 0, 0);

    D_RW(pstack)->elements = D_RO(pelem);

    return 0;
}

/*!
   \brief Constructor for persistent stack
          Allocates Pool of persistent memory and initializes the Stack
          by using the pmemobj_alloc() function we ensure that the stack is
          in a consistent state when returned

   \param size of the Stack

   \return a PMEMoid Wrapper around a Stack Object
*/
PMEMoid getInstance(int size, PMEMobjpool* pool) {

    // initialize Stack
    PMEMoid pstack_oid;
    pmemobj_alloc(pool, &pstack_oid, sizeof(struct pstack), 1, init, (void*)size);

    return pstack_oid;
}

/*!
   \brief Pushes an element into the stack according to FIFO principle
   \param pstack_oid: PMEMoid stack wrapper
*/
void push(PMEMoid pstack_oid, char elem) {
    TOID_ASSIGN(pstack, pstack_oid);

    if (D_RO(pstack)->counter >= D_RO(pstack)->maxsize) {
        printf("%s\n", "Stack is full!");
    }
    else {
        TX_BEGIN(pool) {
            TX_ADD_DIRECT(&D_RW(pstack)->elements[D_RO(pstack)->counter + 1]);
            TX_ADD_DIRECT(&D_RW(pstack)->counter);

            D_RW(pstack)->elements[D_RW(pstack)->counter++] = elem;
        } TX_END
    }
}

/*!
   \brief Retrieves and deletes next element from Stack
   \param PMEMoid Stack wrapper
   \return the next char stored in the Stack
*/
char pop(PMEMoid pstack_oid) {
    TOID_ASSIGN(pstack, pstack_oid);

    if (D_RO(pstack)->counter == 0) {
        printf("%s\n", "Stack is empty!");
    }
    else {
        char elem;
        TX_BEGIN(pool) {
            TX_ADD_DIRECT(&D_RW(pstack)->elements[D_RO(pstack)->counter]);
            TX_ADD_DIRECT(&D_RW(pstack)->counter);

            elem = D_RW(pstack)->elements[D_RO(pstack)->counter];
            D_RW(pstack)->counter--;
        } TX_END

        return elem;
    }
    return NULL;
}

/// Check if Stack is empty
int isEmpty(PMEMoid pstack_oid) {
    return D_RO(pstack)->counter == 0;
}
