CC=gcc
CFLAGS= -Wall

all:
	g++ -lpthread -lrt -g -o  account.o account.c
clean:
	rm *.o

server:
	g++ -g -o server.o server.c
client:
	g++ -g -o client.o client.c
