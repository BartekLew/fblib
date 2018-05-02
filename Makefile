CC=gcc -Wall -pedantic -std=c99 -O3 -g
FLAGS=
OUTDIR=/usr/bin/

ifeq (${DEBUG}, 1)
	FLAGS=-g -DDEBUG
endif

all: info lib/fblib.a bin/fbgrad bin/fbrec bin/fbd util/fb2ppm

lib/%.a: o/%.o
	@ar rcs $@ $<
	@echo "\tLIB\t$^\t-> $@"

o/%.o: %.c %.h
	@${CC} ${FLAGS} ${OPTS} -c $< -o $@
	@echo "\tOBJ\t$^\t-> $@"

bin/%: %.c lib/fblib.a
	@${CC} ${FLAGS} ${OPTS} $^ -o $@
	@echo "\tEXE\t$^\t-> $@"

util/%: %.c
	@${CC} ${FLAGS} ${OPTS} $^ -o $@
	@echo "\tEXE\t$^\t-> $@"

info:
	@echo "CC	= ${CC}"
	@echo "FLAGS	= ${FLAGS}"
	@echo "OUTDIR	= ${OUTDIR}"
	@echo
	@mkdir -p o/ bin/ lib/ util/

install:
	cp bin/* ${OUTDIR}
	cp util/* ${OUTDIR}

clean:
	@rm o/* bin/* lib/* || true
	@echo "clean"

rebuild: clean all

.PHONY: all clean rebuild install
