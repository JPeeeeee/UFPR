CC = gcc
CFLAGS = -std=c99 -Wall

lerXml: lerXml.o
	$(CC) lerXml.o -o lerXml 

lerXml.o : lerXml.c 
	$(CC) $(CFLAGS) -c lerXml.c

clean :
	rm -f *.o lerXml
