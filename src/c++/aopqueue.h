#ifndef AOPQUEUE_H
#define AOPQUEUE_H

#include <stdexcept>
#include "attribute_cpp.h"
#include <libpmemobj++/make_persistent.hpp>
#include <libpmemobj++/persistent_ptr.hpp>
#include <libpmemobj++/pool.hpp>
#include <libpmemobj++/utils.hpp>

struct [[AOP_CPP::transactionalCpp]] NODE {
    char data;
    NODE* next;
};

class [[AOP_CPP::transactionalCpp]] LinkedQueue {

private:
    NODE* head;
    NODE* tail;

public:
    LinkedQueue() {
        this->head = NULL;
        this->tail = NULL;
    }

    void enqueue(char element) {
        auto pop = pmem::obj::pool_by_vptr(this);
        pmem::obj::persistent_ptr<NODE> temp;
        pmem::obj::transaction::run(pop, [&] {
            temp = pmem::obj::make_persistent<NODE>();
        });
        temp->data = element;
        temp->next = NULL;

        if (this->isEmpty()) {
            this->head = temp.get();
            this->tail = temp.get();
            temp = NULL;
        }
        else {
            this->tail->next = temp.get();
            this->tail = temp.get();
        }
    }

    char dequeue() {
        if (this->isEmpty()) {
            throw new std::runtime_error("Queue is empty");
        }
        char elem = this->head->data;
        this->head = this->head->next;

        return elem;
    }

    bool isEmpty() {
        return this->head == NULL;
    }
};


#endif
