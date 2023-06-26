CC = gcc
CFLAGS =  -Wall -g

vina++: vina++.o libfila.o libmanagefiles.o libutils.o
	$(CC) vina++.o libfila.o libmanagefiles.o libutils.o -o vina++ 

vina++.o : vina++.c     
	$(CC) $(CFLAGS) -c vina++.c

libfila.o : libfila.c     
	$(CC) $(CFLAGS) -c libfila.c

libmanagefiles.o : libmanagefiles.c     
	$(CC) $(CFLAGS) -c libmanagefiles.c

libutils.o : libutils.c     
	$(CC) $(CFLAGS) -c libutils.c

clean :
	rm -f *.o vina++

remove : 
	rm -f backup.vpp