CC=gcc
CFLAGS=-Wall -g -pthread

max: main.o barrier.o
	$(CC) $(CFLAGS) main.c barrier.c -o max

main.o: main.c barrier.h
	$(CC) -c main.c

barrier.o: barrier.c barrier.h
	$(CC) -c barrier.c

clean:
	-rm *.o max
