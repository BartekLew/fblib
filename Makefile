CC=gcc -Wall -pedantic -std=c99

fbgrad: fbgrad.c
	${CC} $^ -o $@
