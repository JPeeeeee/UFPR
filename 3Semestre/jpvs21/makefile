CC = gcc
CFLAGS =  -Wall -g -std=c99

beale: beale.o libfila.o libcodifica.o libdecodifica.o libarquivochaves.o
	$(CC)  beale.o libfila.o libcodifica.o libdecodifica.o libarquivochaves.o -o beale 

beale.o : beale.c     
	$(CC) $(CFLAGS) -c beale.c

libfila.o : libfila.c
	$(CC) $(CFLAGS) -c libfila.c

libcodifica.o : libcodifica.c
	$(CC) $(CFLAGS) -c libcodifica.c

libdecodifica.o : libdecodifica.c
	$(CC) $(CFLAGS) -c libdecodifica.c
	
libarquivochaves.o : libarquivochaves.c
	$(CC) $(CFLAGS) -c libarquivochaves.c

clean :
	rm -f *.o beale

purge : 
	rm -f beale