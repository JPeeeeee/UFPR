CC = gcc
CFLAGS =  -Wall -g

main: main.o libfila.o
	$(CC)  main.o libfila.o -o main 

main.o : main.c     
	$(CC) $(CFLAGS) -c main.c

libfila.o : libfila.c
	$(CC) $(CFLAGS) -c libfila.c

clean :
	rm -f *.o main