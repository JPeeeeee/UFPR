CC = gcc
CFLAGS =  -Wall -g

vina++: vina++.o libifla.o libmanagefiles.o
	$(CC) vina++.o libifla.o libmanagefiles.o -o vina++ 

vina++.o : vina++.c     
	$(CC) $(CFLAGS) -c vina++.c

libfila.o : libfila.c     
	$(CC) $(CFLAGS) -c libfila.c

libmanagefiles.o : libmanagefiles.c     
	$(CC) $(CFLAGS) -c libmanagefiles.c

clean :
	rm -f *.o vina++