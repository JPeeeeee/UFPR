CC = gcc
CFLAGS =  -Wall -g -std=c90

mundo: libfila.o libconjunto.o liblef.o testa_conjunto.o testa_lef.o testa_fila.o
	$(CC) libfila.o libconjunto.o liblef.o testa_conjunto.o testa_lef.o testa_fila.o -o mundo 

testa_conjunto.o : testa_conjunto.c 
	$(CC) $(CFLAGS) -c testa_conjunto.c

testa_lef.o : testa_lef.c 
	$(CC) $(CFLAGS) -c testa_lef.c

testa_fila.o : testa_fila.c
	$(CC) $(CFLAGS) -c testa_fila.c

liblef.o : liblef.c
	$(CC) $(CFLAGS) -c liblef.c

libfila.o : libfila.c
	$(CC) $(CFLAGS) -c libfila.c

libconjunto.o : libconjunto.c
	$(CC) $(CFLAGS) -c libconjunto.c

clean :
	rm -f *.o mundo
