CC = gcc
CFLAGS =  -Wall -g -std=c90

mundo: libconjunto.o testa_conjunto.o 
	$(CC) libconjunto.o  testa_conjunto.o -o mundo 

testa_conjunto.o : testa_conjunto.c 
	$(CC) $(CFLAGS) -c testa_conjunto.c

libconjunto.o : libconjunto.c
	$(CC) $(CFLAGS) -c libconjunto.c

clean :
	rm -f *.o mundo
