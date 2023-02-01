CC=g++
CFLAGS=-I.

main: main.o
	$(CC) -o main  main.cpp
	