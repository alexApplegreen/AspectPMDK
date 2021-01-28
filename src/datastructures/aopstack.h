#ifndef STACK_H
#define STACK_H

#include <inttypes.h>
#include <cstdlib>
#include <stdexcept>
#include "../util/log.h"
#include "../util/attribute.ah"

#define STACK_MAXSIZE 1024

class [[AOP_CPP::transactionalCpp]] Stack {

public:

    Stack() : Stack(STACK_MAXSIZE) {}

    Stack(uint64_t size) {
        if (size > STACK_MAXSIZE) {
            throw new std::invalid_argument("Stacksize exceeds maximum size");
        }
        this->m_maxsize = size;
        this->m_counter = 0;
    }

    void push(char elem) {
        if (this->m_counter == this->m_maxsize) {
            throw std::runtime_error("Stack is full");
        }
        else {
            this->m_elements[this->m_counter] = elem;
            this->m_counter++;
        }
    }

    char pop() {
        if (this->m_counter == 0) {
            throw std::runtime_error("Stack is empty");
        }
        else {
            this->m_counter--;
            char elem = this->m_elements[this->m_counter];
            return elem;
        }
    }

    bool isEmpty() {
        return this->m_counter == 0;
    }

private:

    uint64_t                m_counter;
    uint64_t                m_maxsize;
    char                    m_elements[STACK_MAXSIZE];

};
#endif
