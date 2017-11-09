CC=gcc
CFLAGS=-Wall -g -fPIC
LINK=-L/home/student/3_4_fat/ -Wl,-rpath=/home/student/3_4_fat/

main: main.o
	$(CC) -shared -o libFAT.so main.o

main.o: main.c main.h
	$(CC) $(CFLAGS) -fPIC -c main.c

test_run:
	$(CC) $(CFLAGS) $(LINK) -o test test.c -lFAT

clean:
	-rm *.o *.so
