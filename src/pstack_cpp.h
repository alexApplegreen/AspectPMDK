#ifndef PSTACK_CLASS_H
#define PSTACK_CLASS_H

#include <inttypes.h>
#include "util/log.h"
#include <stdexcept>
#include <libpmemobj++/p.hpp>
#include <libpmemobj++/persistent_ptr.hpp>
#include <libpmemobj++/transaction.hpp>
#include <libpmemobj++/make_persistent.hpp>
#include <libpmemobj++/pool.hpp>

class PStack {

public:
    PStack(uint64_t size, pmem::obj::pool_base pop) {
        this->m_pop = pop;
        this->m_maxsize = size;
        this->m_elements[size];
        this->m_counter = 0;
    }

    ~PStack() {
        // TODO
    }

    void push(char elem) {
        if (this->m_counter == m_maxsize) {
            throw std::runtime_error("Stack is full");
        }
        else {
            pmem::obj::transaction::run(this->m_pop, [&] {
                pmem::obj::make_persistent<uint64_t>(this->m_counter);
                pmem::obj::make_persistent<uint64_t>(this->m_elements[this->m_counter + 1]);

                this->m_elements[this->m_counter] = elem;
                this->m_counter = this->m_counter + 1;
            });
        }
    }

    char pop() {
        if (this->m_counter == 0) {
            throw std::runtime_error("Stack is empty");
        }
        else {
            char elem;
            pmem::obj::transaction::run(this->m_pop, [&] {
                pmem::obj::make_persistent<uint64_t>(this->m_counter);
                pmem::obj::make_persistent<uint64_t>(this->m_elements[this->m_counter - 1]);

                this->m_counter = this->m_counter - 1;
                elem = this->m_elements[this->m_counter];
            });
            return elem;
        }
    }

    int isEmpty() {
        return this->m_counter == 0;
    }

private:
    pmem::obj::pool_base                                m_pop;
    pmem::obj::p<uint64_t>                              m_counter;
    pmem::obj::p<uint64_t>                              m_maxsize;
    pmem::obj::p<char>                                  m_elements[];

};
#endif
