#ifndef LINKEDPQUEUE_H
#define LINKEDPQUEUE_H

#include <stdexcept>
#include "attribute_cpp.ah"
#include <libpmemobj++/transaction.hpp>
#include <libpmemobj++/make_persistent.hpp>
#include <libpmemobj++/utils.hpp>
#include <libpmemobj++/pool.hpp>

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

        if (this->head == NULL) {
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
        if (this->head == NULL) {
            throw new std::runtime_error("Queue is empty");
        }
        char elem = this->head->data;
        this->head = this->head->next;

        if (this->head == NULL) {
            this->tail = NULL;
        }

        return elem;
    }

    bool isEmpty() {
        return this->head == NULL;
    }
};

#endif
