CC=gcc
CFLAGS= -Wall -g

all:
	g++ -g -o shared_mem.o shared_mem.c
	g++ -g -o mem_reader.o mem_reader.c

comp_fil: 
	g++ -g -o filozofy.o filozofy.c

fil: comp_fil
	./filozofy.o

clean:
	rm *.o
