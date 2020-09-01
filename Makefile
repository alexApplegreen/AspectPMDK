pstack:
	gcc src/pstacktest.c src/util/log.c -lpmemobj -o pstacktest -g

aopstack:
	ag++ src/aopstacktest.c src/util/log.c -lpmemobj -o aopstacktest -g --keep_woven
