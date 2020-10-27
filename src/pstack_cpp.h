#ifndef PSTACK_CLASS_H
#define PSTACK_CLASS_H

#define STACK_MAXSIZE 1024

#include <inttypes.h>
#include "util/log.h"
#include <stdexcept>
#include <libpmemobj++/p.hpp>
#include <libpmemobj++/persistent_ptr.hpp>
#include <libpmemobj++/transaction.hpp>
#include <libpmemobj++/make_persistent.hpp>
#include <libpmemobj++/utils.hpp>
#include <libpmemobj++/pool.hpp>
#include <libpmemobj.h>

class PStack {

public:
    PStack() : PStack(STACK_MAXSIZE) {}

    PStack(uint64_t size) {
        if (size > STACK_MAXSIZE) {
            throw new std::invalid_argument("Stacksize exceeds maximum size");
        }
        this->m_maxsize = size;
        this->m_counter = 0;
    }

    void push(char elem) {
        if (this->m_counter == m_maxsize) {
            throw std::runtime_error("Stack is full");
        }
        else {
            try {
                auto pop = pmem::obj::pool_by_vptr(this);
                pmem::obj::transaction::run(pop, [&] {
                    this->m_elements[this->m_counter] = elem;
                    this->m_counter = this->m_counter + 1;
                });
            }
            catch (pmem::pool_error e) {
                log_error(e.what());
            }
        }
    }

    char pop() {
        if (this->m_counter == 0) {
            throw std::runtime_error("Stack is empty");
        }
        else {
            char elem;
            try {
                auto pop = pmem::obj::pool_by_vptr(this);
                pmem::obj::transaction::run(pop, [&] {
                    this->m_counter = this->m_counter - 1;
                    elem = this->m_elements[this->m_counter];
                });
            }
            catch (pmem::pool_error e) {
                log_error(e.what());
            }
            return elem;
        }
    }

    int isEmpty() {
        return this->m_counter == 0;
    }

private:
    pmem::obj::p<uint64_t>                              m_counter;
    pmem::obj::p<uint64_t>                              m_maxsize;
    pmem::obj::p<char>                                  m_elements[STACK_MAXSIZE];

};
#endif
