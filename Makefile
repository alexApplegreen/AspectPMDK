pstack:
	gcc src/pstacktest.c src/util/log.c -lpmemobj -o pstacktest -g

aopstack:
	ag++ -std=c++11 src/aopstacktest.c src/util/log.c -lpmemobj -o aopstacktest -g --keep_woven
