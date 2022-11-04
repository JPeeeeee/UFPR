CC = gcc
CFLAGS =  -Wall -g -std=c90

mundo: liblef.o testa_lef.o 
	$(CC) liblef.o  testa_lef.o -o mundo 

testa_lef.o : testa_lef.c 
	$(CC) $(CFLAGS) -c testa_lef.c

liblef.o : liblef.c
	$(CC) $(CFLAGS) -c liblef.c

clean :
	rm -f *.o mundo
