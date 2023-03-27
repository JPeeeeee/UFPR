CC = gcc
CFLAGS = -lm -o

main.o : main.c 
	$(CC) main.c $(CFLAGS) main $(pkg-config allegro-5 allegro_main-5 allegro_font-5 --libs --cflags)

clean :
	rm -f *.o main
