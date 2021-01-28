#define CATCH_CONFIG_EXTERNAL_INTERFACES

#include "../util/catch.hpp"
#include "../datastructures/linkedqueue.h"
#include <stdexcept>

LinkedQueue* queue = new LinkedQueue();

struct MyListener : Catch::TestEventListenerBase {

    using TestEventListenerBase::TestEventListenerBase;

    void testCaseEnded(Catch::TestCaseStats const& testCaseStats) override {
        while(!queue->isEmpty()) {
            queue->dequeue();
        }
    }
};
CATCH_REGISTER_LISTENER(MyListener)

TEST_CASE("Get Instance", "[Queue]") {
    REQUIRE(queue->isEmpty());
}

TEST_CASE("Can enq/deq", "[Queue]") {
    queue->enqueue('A');
    REQUIRE_FALSE(queue->isEmpty());
    char elem = queue->dequeue();
    REQUIRE(elem == 'A');
    REQUIRE(queue->isEmpty());
}

TEST_CASE("deq throws exception", "[Queue]") {
    REQUIRE_THROWS_AS([&]() {
        queue->dequeue();
    }(), std::runtime_error*);
}

TEST_CASE("FIFO works", "[Queue]") {
    queue->enqueue('H');
    queue->enqueue('A');
    queue->enqueue('L');
    queue->enqueue('L');
    queue->enqueue('O');

    char hello[6];
    int i = 0;
    while(!queue->isEmpty()) {
        hello[i] = queue->dequeue();
        i++;
    }
    hello[5] = '\0';
    REQUIRE(strcmp(hello, "HALLO") == 0);
}
