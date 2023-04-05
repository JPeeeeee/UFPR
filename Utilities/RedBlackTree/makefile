CC = gcc
CFLAGS =  -Wall -g

main: main.o libRedblack.o
	$(CC)  main.o libRedblack.o -o main 

main.o : main.c     
	$(CC) $(CFLAGS) -c main.c

libRedblack.o : libRedblack.c
	$(CC) $(CFLAGS) -c libRedblack.c

clean :
	rm -f *.o main