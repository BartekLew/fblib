CC=gcc -Wall -pedantic -std=c99 -O3 -g
FLAGS=

ifeq (${DEBUG}, 1)
	FLAGS=-g -DDEBUG
endif

all: info lib/fblib.a bin/fbgrad bin/fbrec bin/fbd

lib/%.a: o/%.o
	@ar rcs $@ $<
	@echo "\tLIB\t$^\t-> $@"

o/%.o: %.c %.h
	@${CC} ${FLAGS} ${OPTS} -c $< -o $@
	@echo "\tOBJ\t$^\t-> $@"

bin/%: %.c lib/fblib.a
	@${CC} ${FLAGS} ${OPTS} $^ -o $@
	@echo "\tEXE\t$^\t-> $@"

info:
	@echo "CC	= ${CC}"
	@echo "FLAGS	= ${FLAGS}"
	@echo
	@mkdir -p o/ bin/ lib/

clean:
	@rm o/* bin/* lib/* || true
	@echo "clean"

rebuild: clean all

.PHONY: all clean rebuild
