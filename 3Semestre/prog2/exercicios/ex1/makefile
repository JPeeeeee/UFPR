CC = gcc
CFLAGS =  -Wall -g

main: main.o 
	$(CC)  main.o -o main 

main.o : main.c     
	$(CC) $(CFLAGS) -c main.c

clean :
	rm -f *.o main