pstack:
	gcc src/pstacktest.c -lpmemobj -o pstacktest -g

aopstack:
	ag++ src/aopstacktest.c -lpmemobj -o aopstacktest -g
