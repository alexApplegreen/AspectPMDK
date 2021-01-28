CXXFLAGS= -g
ACCFLAGS= -std=c++11 --c_compiler g++-9 --data_joinpoints --builtin_operators
LOG = src/util/log.c
CATCH_O = src/util/tests-main.o



stack: stacktest
.PHONY: stack

queue: queuetest
.PHONY: queue

aopstack: aopstackexample aopstackexample2
.PHONY: aopstack

aopqueue: aopqueueexample aopqueueexample2
.PHONY: aopqueue

aopvector: aopvectorexample aopvectorexample2
.PHONY: aopvector

aspectc: aspectcexample
.PHONY: aspectc

clean:
	rm -rf stacktest
	rm -rf queuetest
	rm -rf aopstackexample*
	rm -rf aopqueueexample*
	rm -rf aopvectorexample*
	rm -rf aspectcexample



stacktest: src/examples/stacktest.cpp src/datastructures/stack.h
	g++ $(CXXFLAGS) $(LOG) $(CATCH_O) src/examples/stacktest.cpp -o $@

queuetest: src/examples/queuetest.cpp src/datastructures/linkedqueue.h
	g++ $(CXXFLAGS) $(LOG) $(CATCH_O) src/examples/queuetest.cpp -o $@

aspectcexample: aspectc++_example/HelloWorld.cpp aspectc++_example/hello.h
	ag++ $(CXXFLAGS) $(ACCFLAGS) aspectc++_example/HelloWorld.cpp -o $@



aopstackexample: src/examples/aopstackExample.cpp src/datastructures/aopstack.h
	ag++ $(CXXFLAGS) $(ACCFLAGS) $(LOG) src/examples/aopstackExample.cpp -lpmemobj -o $@

aopstackexample2: src/examples/aopstackExample2.cpp src/datastructures/aopstack.h
	ag++ $(CXXFLAGS) $(ACCFLAGS) $(LOG) src/examples/aopstackExample2.cpp -lpmemobj -o $@



aopqueueexample: src/examples/aopqueueExample.cpp src/datastructures/aopqueue.h
	ag++ $(CXXFLAGS) $(ACCFLAGS) $(LOG) src/examples/aopqueueExample.cpp -lpmemobj -o $@

aopqueueexample2: src/examples/aopqueueExample2.cpp src/datastructures/aopqueue.h
	ag++ $(CXXFLAGS) $(ACCFLAGS) $(LOG) src/examples/aopqueueExample2.cpp -lpmemobj -o $@



aopvectorexample: src/examples/aopvectorExample.cpp src/datastructures/aopvector.h
	ag++ $(CXXFLAGS) $(ACCFLAGS) $(LOG) src/examples/aopvectorExample.cpp -lpmemobj -o $@

aopvectorexample2: src/examples/aopvectorExample2.cpp src/datastructures/aopvector.h
	ag++ $(CXXFLAGS) $(ACCFLAGS) $(LOG) src/examples/aopvectorExample2.cpp -lpmemobj -o $@
