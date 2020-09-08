#ifndef STACK_H
#define STACK_H

#include <inttypes.h>
#include <cstdlib>
#include <stdexcept>
#include "util/log.h"
#include <assert.h>

class Stack {

public:

    Stack(uint64_t size) {
        this->m_maxsize = size;
        this->m_elements[size];
        this->m_counter = 0;
    }

    void push(char elem) {
        if (this->m_counter == m_maxsize) {
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
    char                    m_elements[];

};
#endif
