CC=gcc
CFLAGS=-Wall -g

main: main.o
	$(CC) -shared -o libFAT.so main.o

main.o: main.c main.h
	$(CC) $(CFLAGS) -c main.c

test_run:
	$(CC) $(CFLAGS) -o test test.c -lFAT

clean:
	-rm *.o *.so
