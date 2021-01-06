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
        std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
        auto pop = pmem::obj::pool_by_vptr(this);
        pmem::obj::persistent_ptr<NODE> temp;
        pmem::obj::transaction::run(pop, [&] {
            temp = pmem::obj::make_persistent<NODE>();

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
        });
        std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
        printf("%ld\n", std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin).count());
    }

    char dequeue() {
        std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
        auto pop = pmem::obj::pool_by_vptr(this);
        char elem;
        pmem::obj::transaction::run(pop, [&] {
            if (this->head == NULL) {
                throw new std::runtime_error("Queue is empty");
            }
            elem = this->head->data;
            this->head = this->head->next;

            if (this->head == NULL) {
                this->tail = NULL;
            }
        });

        std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
        printf("%ld\n", std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin).count());
        return elem;
    }

    bool isEmpty() {
        return this->head == NULL;
    }
};

#endif
