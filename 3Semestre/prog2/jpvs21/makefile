CC = gcc
CFLAGS =  -Wall -g

main: main.o libfila.o libarvore.o libcodifica.o libdecodifica.o
	$(CC)  main.o libfila.o libarvore.o libcodifica.o libdecodifica.o -o main 

main.o : main.c     
	$(CC) $(CFLAGS) -c main.c

libfila.o : libfila.c
	$(CC) $(CFLAGS) -c libfila.c

libarvore.o : libarvore.c
	$(CC) $(CFLAGS) -c libarvore.c

libcodifica.o : libcodifica.c
	$(CC) $(CFLAGS) -c libcodifica.c

libdecodifica.o : libdecodifica.c
	$(CC) $(CFLAGS) -c libdecodifica.c

clean :
	rm -f *.o main