CC=gcc
CFLAGS=-ansi -Wall

all: mqTest

mqTest: mqTest.o mQueue.o
	$(CC) -Wall -o mqTest mqTest.o mQueue.o

mQueue.o: mQueue.c mQueue.h
	$(CC) $(CFLAGS) -x c -c -o mQueue.o mQueue.c

mqTest.o: mqTest.c
	$(CC) $(CFLAGS) -x c -c -o mqTest.o mqTest.c

clean:
	rm -f *.o
