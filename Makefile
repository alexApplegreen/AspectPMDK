stack:
	g++ src/stacktest.cpp src/util/catch.hpp src/util/log.h -o stacktest -g

pstack:
	g++ src/pstacktest.cpp src/util/log.c src/util/catch.hpp -lpmemobj -o pstacktest -g
	g++ src/pstacktest2.cpp src/util/log.c src/util/catch.hpp -lpmemobj -o pstacktest2 -g

aopstack:
	ag++ -std=c++11 src/aopstacktest.c src/util/log.c -lpmemobj -o aopstacktest -g --keep_woven
	ag++ -std=c++11 src/aopstacktest2.c src/util/log.c -lpmemobj -o aopstacktest2 -g --keep_woven

cppstack:
	g++ src/util/tests-main.o src/pstack_cpptest.cpp src/util/log.c -lpmemobj -g -o cppstacktest
	g++ src/util/tests-main.o src/pstack_cpptest2.cpp src/util/log.c -lpmemobj -g -o cppstacktest2

aoptest:
	ag++ -std=c++11 src/quicktest.cpp src/util/log.c -lpmemobj -o aoptest -g
