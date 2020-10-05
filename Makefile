pstack:
	gcc src/pstacktest.c src/util/log.c -lpmemobj -o pstacktest -g

aopstack:
	ag++ -std=c++11 src/aopstacktest.c src/util/log.c -lpmemobj -o aopstacktest -g --keep_woven
	ag++ -std=c++11 src/aopstacktest2.c src/util/log.c -lpmemobj -o aopstacktest2 -g --keep_woven

cppstack:
	g++ src/pstack_cpptest.cpp src/util/log.c -lpmemobj -o cppstacktest -g
	g++ src/pstack_cpptest2.cpp src/util/log.c -lpmemobj -o cppstacktest2 -g
