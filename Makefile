CC=gcc -Wall -pedantic -std=c99 -O3

fbgrad: fbgrad.c
	${CC} $^ -o $@
