#ifndef AOPVECTOR_H
#define AOPVECTOR_H

#include <vector>
#include "attribute_cpp.ah"
#include <libpmemobj++/transaction.hpp>
#include <libpmemobj++/experimental/self_relative_ptr.hpp>
#include <libpmemobj++/make_persistent.hpp>
#include <libpmemobj++/utils.hpp>
#include <libpmemobj++/allocator.hpp>

class [[AOP_CPP::transactionalCpp]] aopvector {

private:
    std::vector<char, pmem::obj::allocator<char>>* m_vector;

public:

    void init() {
        auto pop = pmem::obj::pool_by_vptr(this);
        pmem::obj::transaction::run(pop, [&] {
            auto ptr = pmem::obj::make_persistent<std::vector<char, pmem::obj::allocator<char>>>();
            this->m_vector = ptr.get();
        });
    }

    void add(char elem) {
        this->m_vector->push_back(elem);
    }

    char get() {
        char elem = this->m_vector->back();
        m_vector->pop_back();
        return elem;
    }

    bool isEmpty() {
        return this->m_vector->empty();
    }
};

#endif
