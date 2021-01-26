#ifndef PSTACK_CLASS_H
#define PSTACK_CLASS_H

#include <inttypes.h>
#include "../util/log.h"
#include <stdexcept>
#include <libpmemobj++/p.hpp>
#include <libpmemobj++/persistent_ptr.hpp>
#include <libpmemobj++/transaction.hpp>
#include <libpmemobj++/make_persistent.hpp>
#include <libpmemobj++/utils.hpp>
#include <libpmemobj++/pool.hpp>
#include <libpmemobj.h>
#include <chrono>

#define STACK_MAXSIZE 1024

class PStack {

public:

    PStack(uint64_t size) {
        m_maxsize = size;

        log_debug("Stacksize is: %d", this->m_maxsize);
    }

    void push(char elem) {
        log_debug("Stacksize is: %d", this->m_maxsize);

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
        auto start = std::chrono::system_clock::now();
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
            auto end = std::chrono::system_clock::now();
            printf("%ld,", std::chrono::duration_cast<std::chrono::nanoseconds>(end - start));
            return elem;
        }
    }

    bool isEmpty() {
        return this->m_counter == 0;
    }

private:
    pmem::obj::p<uint64_t>                              m_counter = 0;
    pmem::obj::p<uint64_t>                              m_maxsize;
    pmem::obj::p<char>                                  m_elements[STACK_MAXSIZE];

};
#endif
