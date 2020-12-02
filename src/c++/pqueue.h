#ifndef LINKEDQUEUE_H
#define LINKEDQUEUE_H

#include <stdexcept>
#include "attribute_cpp.ah"

struct NODE {
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
        NODE* temp = new NODE;
        temp->data = element;
        temp->next = NULL;

        if (this->isEmpty()) {
            this->head = temp;
            this->tail = temp;
            temp = NULL;
        }
        else {
            this->tail->next = temp;
            this->tail = temp;
        }
    }

    char dequeue() {
        if (this->isEmpty()) {
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
