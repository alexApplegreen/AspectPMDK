#ifndef LINKEDPQUEUE_H
#define LINKEDPQUEUE_H

#include <stdexcept>
#include "attribute_cpp.ah"
#include <libpmemobj++/transaction.hpp>
#include <libpmemobj++/make_persistent.hpp>
#include <libpmemobj++/persistent_ptr.hpp>
#include <libpmemobj++/utils.hpp>
#include <libpmemobj++/pool.hpp>
#include "../util/log.h"
#include <chrono>

struct NODE {
    pmem::obj::p<char> data;
    pmem::obj::persistent_ptr<NODE> next;
};

class LinkedQueue {

private:
    pmem::obj::persistent_ptr<NODE> head;
    pmem::obj::persistent_ptr<NODE> tail;

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
            temp->next = NULL;
            temp->data = element;

            if (this->head == NULL) {
                this->head = temp;
                this->tail = temp;
            }
            else {
                this->tail->next = temp;
                this->tail = temp;
            }
        });
    }

    char dequeue() {
        auto pop = pmem::obj::pool_by_vptr(this);
        char elem;
        pmem::obj::transaction::run(pop, [&] {
            if (this->head == NULL) {
                throw new std::runtime_error("Queue is empty");
            }
            auto tmp = this->head;

            elem = this->head->data;
            this->head = this->head->next;

            pmem::obj::delete_persistent<NODE>temp;

            if (this->head == NULL) {
                this->tail = NULL;
            }
        });

        return elem;
    }

    bool isEmpty() {
        return this->head == NULL;
    }
};

#endif
