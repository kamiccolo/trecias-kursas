CC=gcc
CFLAGS=-ansi -Wall

all: mqTest server client

mqTest: mqTest.o mQueue.o
	$(CC) -Wall -o mqTest mqTest.o mQueue.o

server: server.o mQueue.o common.o
	$(CC) -Wall -o server server.o mQueue.o common.o

server.o: server.c server.h defaults.h
	$(CC) $(CFLAGS) -x c -c -o server.o server.c

client: client.o mQueue.o common.o
	$(CC) -Wall -o client client.o mQueue.o common.o

client.o: client.c client.h defaults.h
	$(CC) $(CFLAGS) -x c -c -o client.o client.c

mQueue.o: mQueue.c mQueue.h
	$(CC) $(CFLAGS) -x c -c -o mQueue.o mQueue.c

mqTest.o: mqTest.c
	$(CC) $(CFLAGS) -x c -c -o mqTest.o mqTest.c

common.o: common.c defaults.h
	$(CC) $(CFLAGS) -x c -c -o common.o common.c

clean:
	rm -f *.o
