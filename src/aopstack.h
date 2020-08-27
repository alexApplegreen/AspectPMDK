/*!
   \file pstack.h

   \brief implementation of Stack using arrays, Stack runnable on persistent
          memory by using PMDK transactions. In this version of the stack,
          transactional behavior is ensured by advices which trigger
          the PMDK transactional API

   \author Alexander Tepe
*/

#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libpmemobj.h>
#include "attribute.ah"

static PMEMobjpool* m_pool;

// Forward Declarations
PMEMoid getInstance(uint64_t size, PMEMobjpool* pool);
[[AOP::transactional]] void push(PMEMoid stack, char elem);
[[AOP::transactional]] char pop(PMEMoid stack);
int isEmpty(PMEMoid stack);

// global TOIDs
TOID_DECLARE(struct pstack, 1);
TOID(struct pstack) pstack;

TOID_DECLARE(char, 2);
TOID(char) pelem;

/// The internal stack which is used for FIFO storing of Data
struct pstack {
    uint64_t                maxsize;
    int                     counter;
    char                    elements[];
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
    intptr_t size = (intptr_t)args;
    PMEMoid stack_oid = pmemobj_oid(ptr);
    TOID_ASSIGN(pstack, stack_oid);

    D_RW(pstack)->maxsize = size;
    D_RW(pstack)->counter = 0;
    D_RW(pstack)->elements[size];

    pmemobj_persist(pool, D_RW(pstack), sizeof(D_RW(pstack)));

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
PMEMoid getInstance(uint64_t size, PMEMobjpool* pool) {

    m_pool = pool;
    // initialize Stack
    PMEMoid pstack_oid;
    pmemobj_alloc(m_pool, &pstack_oid, sizeof(struct pstack), 1, init, (void*)size);

    return pstack_oid;
}

/*!
   \brief Pushes an element into the stack according to FIFO principle

   \param pstack_oid: PMEMoid stack wrapper
          elem: char to push into stack
*/
// TODO make function behave transactional by using advices
[[AOP::transactional]]
void push(PMEMoid pstack_oid, char elem) {

    TOID_ASSIGN(pstack, pstack_oid);
    if (D_RO(pstack)->counter >= D_RO(pstack)->maxsize) {
        printf("%s\n", "Stack is full");
    }
    else {
        D_RW(pstack)->elements[D_RW(pstack)->counter] = elem;
        D_RW(pstack)->counter++;
    }
}

/*!
   \brief Retrieves and deletes next element from Stack
   \param PMEMoid Stack wrapper
   \return the next char stored in the Stack
*/
// TODO Transactional behavior through advice
[[AOP::transactional]]
char pop(PMEMoid pstack_oid) {

    TOID_ASSIGN(pstack, pstack_oid);

    if (isEmpty(pstack_oid)) {
        printf("%s\n", "Stack is empty");
    }
    else {
        D_RW(pstack)->counter--;
        return D_RW(pstack)->elements[D_RW(pstack)->counter];
    }
    return '0';
}

/// Check if Stack is empty
int isEmpty(PMEMoid pstack_oid) {
    return D_RO(pstack)->counter == 0;
}
