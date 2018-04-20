CC=gcc -Wall -pedantic -std=c99 -O3

fbgrad: fbgrad.c fblib.h
	${CC} $< -o $@
