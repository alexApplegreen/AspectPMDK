-include local.mk

stack:
	g++ src/util/tests-main.o src/c++/pstacktest.cpp src/util/log.c -lpmemobj -g -o stacktest
	g++ src/util/tests-main.o src/c++/pstacktest2.cpp src/util/log.c -lpmemobj -g -o stacktest2

queue:
	g++ src/util/tests-main.o src/c++/queuetest.cpp src/util/log.c -g -o queuetest
	g++ src/util/tests-main.o src/c++/queuetest2.cpp src/util/log.c -g -o queuetest2

aopstack:
	ag++ -std=c++11 --c_compiler g++-9 src/examples/aopstackExample.cpp src/util/log.c -lpmemobj -o aopstackexample -g --keep_woven --data_joinpoints --builtin_operators
	ag++ -std=c++11 --c_compiler g++-9 src/examples/aopstackExample2.cpp src/util/log.c -lpmemobj -o aopstackexample2 -g --keep_woven --data_joinpoints --builtin_operators

aopqueue:
	ag++ -std=c++11 --c_compiler g++-9 src/examples/aopqueueExample.cpp src/util/log.c -lpmemobj -o aopqueueexample -g --data_joinpoints --builtin_operators
	ag++ -std=c++11 --c_compiler g++-9 src/examples/aopqueueExample2.cpp src/util/log.c -lpmemobj -o aopqueueexample2 -g --data_joinpoints --builtin_operators

vector:
	ag++ -std=c++11 --c_compiler g++-9 src/examples/vectortest.cpp src/util/log.c -lpmemobj -o vectortest -g --data_joinpoints --builtin_operators
	ag++ -std=c++11 --c_compiler g++-9 src/examples/vectortest2.cpp src/util/log.c -lpmemobj -o vectortest2 -g --data_joinpoints --builtin_operators
