CC=gcc
CFLAGS= -Wall -g
all:
	g++ -g -o main.o main.cpp

zip:
	Lab1.zip

clean:
	rm -f *.o

Lab1.zip: *.c *.h Makefile
	zip $@ $^

pipe:
	g++ -g -o pipe.o pipe.c
	./pipe.o
