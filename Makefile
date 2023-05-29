CFLAGS = -Wall -Wpedantic -Wextra -Wl,-z,now
CFLAGS_RELEASE = ${CFLAGS} -O2 -s -D_FORTIFY_SOURCE=2
CFLAGS_DEBUG = ${CFLAGS} -O0 -g -fsanitize=undefined
CFLAGS_STATIC = ${CFLAGS_RELEASE} -static-pie
LIBS = -lcrypt
CC = gcc
PREFIX ?= /usr/local

all: rdo.c rdo.h
	${CC} ${CFLAGS_RELEASE} rdo.c -o rdo ${LIBS}

static: rdo.c rdo.h
	${CC} ${CFLAGS_STATIC} rdo.c -o rdo ${LIBS}

debug: rdo.c rdo.h
	${CC} ${CFLAGS_DEBUG} rdo.c -o rdo ${LIBS}

noconfig: rdo.noconfig.c
	${CC} ${CFLAGS_RELEASE} rdo.noconfig.c -o rdo

install: rdo
	mkdir -p ${DESTDIR}${PREFIX}/bin
	cp rdo ${DESTDIR}${PREFIX}/bin
	chown root:root ${DESTDIR}${PREFIX}/bin/rdo
	chmod 4755 ${DESTDIR}${PREFIX}/bin/rdo

uninstall:
	rm ${DESTDIR}${PREFIX}/bin/rdo

clean:
	rm rdo
