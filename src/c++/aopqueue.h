#ifndef AOPQUEUE_H
#define AOPQUEUE_H

#include <stdexcept>
#include "attribute_cpp.ah"
#include <libpmemobj++/make_persistent.hpp>
#include <libpmemobj++/persistent_ptr.hpp>
#include <libpmemobj++/experimental/self_relative_ptr.hpp>
#include <libpmemobj++/transaction.hpp>
#include <libpmemobj++/pool.hpp>
#include <libpmemobj++/utils.hpp>
#include "../util/log.h"

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
        auto temp = new NODE();
        temp->data = element;
        temp->next = NULL;

        if (this->head == NULL) {
            this->head = temp;
            this->tail = temp;
            delete temp;
        }
        else {
            this->tail->next = temp;
            this->tail = temp;
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
