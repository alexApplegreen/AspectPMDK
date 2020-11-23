#ifndef TESTCLASS_H
#define TESTCLASS_H

#include "attribute1.ah"
#include <iostream>

class Testclass {

public:

    // Hier soll nur pointcut1 in aspect1.ah angewebt werden.
    [[namespace1::attr]]
    static void printAnnotation() {

        // Ausgabe soll also lauten: "Should say namespace1: namespace1"
        std::cout << "Should say namespace1: ";
    }
};

#endif
