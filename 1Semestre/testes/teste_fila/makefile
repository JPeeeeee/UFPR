CC = gcc
CFLAGS =  -Wall -g -std=c90

mundo: libfila.o testa_fila.o 
	$(CC) libfila.o  testa_fila.o -o mundo 

testa_conjunto.o : testa_fila.c 
	$(CC) $(CFLAGS) -c testa_fila.c

libfila.o : libfila.c
	$(CC) $(CFLAGS) -c libfila.c

clean :
	rm -f *.o mundo