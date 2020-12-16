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
        pmem::obj::experimental::self_relative_ptr<NODE> temp;
        pmem::obj::transaction::run(pop, [&] {
            temp = pmem::obj::make_persistent<NODE>();
        });
        temp->data = element;
        temp->next = NULL;

        if (this->head == NULL) {
            this->head = temp.get();
            this->tail = temp.get();
            pmem::obj::delete_persistent<NODE>(temp);
        }
        else {
            // Das funktioniert noch
            this->tail = temp.get();
            // FIXME Hier tritt der Segfault auf. (genauer im set advice für pointer)
            this->tail->next = temp.get();
        }
    }

    char dequeue() {
        if (this->head == NULL) {
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
