prog: correct.o corpus.o hash.o main.o
	gcc correct.o corpus.o hash.o main.o -o prog

correct.o: correct.h hash.h correct.c
	gcc -c correct.c
	
corpus.o: corpus.h corpus.c
	gcc -c corpus.c
	
hash.o: hash.h hash.c
	gcc -c hash.c
	
main.o: correct.h hash.h corpus.h main.c
	gcc -c main.c

