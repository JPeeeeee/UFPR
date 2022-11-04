CC = gcc
CFLAGS =  -Wall -g -std=c90

mundo: mundo.o libfila.o libconjunto.o liblef.o
	$(CC)  mundo.o libfila.o libconjunto.o liblef.o -o mundo 

liblef.o : liblef.c
	$(CC) $(CFLAGS) -c liblef.c

mundo.o : mundo.c     
	$(CC) $(CFLAGS) -c mundo.c

libfila.o : libfila.c
	$(CC) $(CFLAGS) -c libfila.c

libconjunto.o : libconjunto.c
	$(CC) $(CFLAGS) -c libconjunto.c

clean :
	rm -f *.o mundo
