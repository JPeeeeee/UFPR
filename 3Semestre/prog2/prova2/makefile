CC = gcc
CFLAGS =  -Wall -g

main: main.o 
	$(CC)  main.o -o rle 

main.o : main.c     
	$(CC) $(CFLAGS) -c main.c

clean :
	rm -f *.o rle