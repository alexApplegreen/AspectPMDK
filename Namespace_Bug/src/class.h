#ifndef TESTCLASS_H
#define TESTCLASS_H

#include "attribute1.ah"
#include <iostream>

class Testclass {

public:

    [[namespace1::attr]]
    static void printAnnotation() {
        std::cout << "Should say namespace1: ";
    }
};

#endif
