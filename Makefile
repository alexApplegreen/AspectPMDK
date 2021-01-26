-include local.mk

stack:
	g++ src/util/tests-main.o src/c++/pstacktest.cpp src/util/log.c -lpmemobj -g -o stacktest
	g++ src/util/tests-main.o src/c++/pstacktest2.cpp src/util/log.c -lpmemobj -g -o stacktest2

aopstack:
	ag++ -std=c++11 --c_compiler g++-9 src/c++/aopstacktest.cpp src/util/log.c -lpmemobj -o aopstacktest -g --keep_woven --data_joinpoints --builtin_operators
	ag++ -std=c++11 --c_compiler g++-9 src/c++/aopstacktest2.cpp src/util/log.c -lpmemobj -o aopstacktest2 -g --keep_woven --data_joinpoints --builtin_operators

aopqueue:
	ag++ -std=c++11 --c_compiler g++-9 src/c++/queuetest.cpp src/util/log.c -lpmemobj -o queuetest -g --data_joinpoints --builtin_operators
	ag++ -std=c++11 --c_compiler g++-9 src/c++/queuetest2.cpp src/util/log.c -lpmemobj -o queuetest2 -g --data_joinpoints --builtin_operators

vector:
	ag++ -std=c++11 --c_compiler g++-9 src/c++/vectortest.cpp src/util/log.c -lpmemobj -o vectortest -g --data_joinpoints --builtin_operators
	ag++ -std=c++11 --c_compiler g++-9 src/c++/vectortest2.cpp src/util/log.c -lpmemobj -o vectortest2 -g --data_joinpoints --builtin_operators
