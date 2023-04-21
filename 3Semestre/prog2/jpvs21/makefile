CC = gcc
CFLAGS =  -Wall -g

beale: beale.o libfila.o libcodifica.o libdecodifica.o
	$(CC)  beale.o libfila.o libcodifica.o libdecodifica.o -o beale 

beale.o : beale.c     
	$(CC) $(CFLAGS) -c beale.c

libfila.o : libfila.c
	$(CC) $(CFLAGS) -c libfila.c

libcodifica.o : libcodifica.c
	$(CC) $(CFLAGS) -c libcodifica.c

libdecodifica.o : libdecodifica.c
	$(CC) $(CFLAGS) -c libdecodifica.c

clean :
	rm -f *.o beale