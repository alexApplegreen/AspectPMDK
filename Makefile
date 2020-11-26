stack:
	g++ src/c++/stacktest.cpp src/util/tests-main.o src/util/catch.hpp src/util/log.h -o stacktest -g

pstack:
	g++ src/c/pstacktest.cpp src/util/log.c src/util/catch.hpp -lpmemobj -o pstacktest -g
	g++ src/c/pstacktest2.cpp src/util/log.c src/util/catch.hpp -lpmemobj -o pstacktest2 -g

aopstack:
	ag++ -std=c++11 src/c/aopstacktest.c src/util/log.c -lpmemobj -o aopstacktest -g --keep_woven
	ag++ -std=c++11 src/c/aopstacktest2.c src/util/log.c -lpmemobj -o aopstacktest2 -g --keep_woven

cppstack:
	g++ src/util/tests-main.o src/c++/pstack_cpptest.cpp src/util/log.c -lpmemobj -g -o cppstacktest
	g++ src/util/tests-main.o src/c++/pstack_cpptest2.cpp src/util/log.c -lpmemobj -g -o cppstacktest2

aoptest:
	ag++ -std=c++11 src/c++/quicktest.cpp src/util/log.c -lpmemobj -o aoptest -g --keep_woven --data_joinpoints --builtin_operators
	ag++ -std=c++11 src/c++/quicktest2.cpp src/util/log.c -lpmemobj -o aoptest2 -g --keep_woven --data_joinpoints --builtin_operators
