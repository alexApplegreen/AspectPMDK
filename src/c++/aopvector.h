#ifndef AOPVECTOR_H
#define AOPVECTOR_H

#include <vector>
#include "attribute_cpp.ah"
#include <libpmemobj++/transaction.hpp>
#include <libpmemobj++/experimental/self_relative_ptr.hpp>
#include <libpmemobj++/make_persistent.hpp>
#include <libpmemobj++/utils.hpp>

class [[AOP_CPP::transactionalCpp]] aopvector {

private:
    std::vector<char>* m_vector;

public:

    void init() {
        auto pop = pmem::obj::pool_by_vptr(this);
        pmem::obj::transaction::run(pop, [&] {
            auto ptr = pmem::obj::make_persistent<std::vector<char>>();
            this->m_vector = ptr.get();
        });
    }

    std::vector<char>* getVector() {
        return this->m_vector;
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
