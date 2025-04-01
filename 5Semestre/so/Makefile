CC = gcc
CFLAGS =  -Wall -g

testafila: testafila.o queue.o
	$(CC) testafila.o queue.o -o testafila

queue.o : queue.c
	$(CC) $(CFLAGS) -c queue.c

testafila.o: testafila.c
	$(CC) $(CFLAGS) -c testafila.c

clean :
	rm -f *.o queue

run: 
	./queue
