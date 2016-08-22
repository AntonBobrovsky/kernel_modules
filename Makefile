CC = gcc
CFLAGS = -Wall

default: main.o
		$(CC) $(CFLAGS) main.c -o main

clean:
		rm -rf main *.o

run:
		./main
