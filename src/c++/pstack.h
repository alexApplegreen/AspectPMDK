#ifndef PSTACK_CLASS_H
#define PSTACK_CLASS_H

#include <inttypes.h>
#include "../util/log.h"
#include <stdexcept>
#include <libpmemobj++/p.hpp>
#include <libpmemobj++/persistent_ptr.hpp>
#include <libpmemobj++/transaction.hpp>
#include <libpmemobj++/utils.hpp>
#include <libpmemobj++/pool.hpp>
#include <libpmemobj.h>

#define STACK_MAXSIZE 1024

class PStack {

public:

    PStack() : PStack(STACK_MAXSIZE) {}

    PStack(uint64_t size) {
        if (size > STACK_MAXSIZE) {
            throw new std::invalid_argument("Stack size is too large");
        }
        m_maxsize = size;
        m_counter = 0;
    }

    void push(char elem) {
        if (this->m_counter == this->m_maxsize) {
            throw new std::runtime_error("Stack is full");
        }
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

    bool isEmpty() {
        return this->m_counter == 0;
    }

private:
    pmem::obj::p<uint64_t>                              m_counter;
    pmem::obj::p<uint64_t>                              m_maxsize;
    pmem::obj::p<char>                                  m_elements[STACK_MAXSIZE];

};
#endif
