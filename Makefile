pstack:
	gcc src/pstacktest.c src/util/log.c -lpmemobj -o pstacktest -g

aopstack:
	ag++ -std=c++11 src/aopstacktest.c src/util/log.c -lpmemobj -o aopstacktest -g --keep_woven
	ag++ -std=c++11 src/aopstacktest2.c src/util/log.c -lpmemobj -o aopstacktest2 -g --keep_woven
