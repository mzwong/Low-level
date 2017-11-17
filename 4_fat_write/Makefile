CC=gcc
CFLAGS=-Wall -g -fPIC
LINK=-L/home/student/4_fat_write/ -Wl,-rpath=/home/student/4_fat_write/

main: main.o
	$(CC) -shared -o libFAT16.so main.o

main.o: main.c main.h
	$(CC) $(CFLAGS) -fPIC -c main.c

test_run:
	$(CC) $(CFLAGS) $(LINK) -o test test.c -lFAT16

clean:
	-rm *.o *.so test
