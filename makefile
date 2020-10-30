CC=gcc
CFLAGS=-Wall

main.exe: main.o ecran.o conversion.o
	$(CC) -o main.exe main.o ecran.o conversion.o

main.o: main.c
	$(CC) -c main.c

ecran.o: ecran.c
	$(CC) -c ecran.c

conversion.o: conversion.c
	$(CC) -c conversion.c 

ctrl.exe: ctrl2.o
	$(CC) -o ctrl2.exe ctrl2.o

ctrl.o: ctrl2.c
	$(CC) -c ctrl2.c

clean:
	rm -rf *.o
