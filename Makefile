CFLAGS = -Wall -Wpedantic -Wextra -Werror -Wl,-z,now
CFLAGS_RELEASE = ${CFLAGS} -O2 -s -D_FORTIFY_SOURCE=2
CFLAGS_DEBUG = ${CFLAGS} -O0 -g -fsanitize=undefined
CFLAGS_STATIC = ${CFLAGS_RELEASE} -static-pie
LIBS = -lcrypt
CC = gcc

all: rdo.c
	${CC} ${CFLAGS_RELEASE} rdo.c -o rdo ${LIBS}

static: rdo.c
	${CC} ${CFLAGS_STATIC} rdo.c -o rdo ${LIBS}

debug: rdo.c
	${CC} ${CFLAGS_DEBUG} rdo.c -o rdo ${LIBS}

install: rdo
	cp rdo /usr/local/bin
	chown root:root /usr/local/bin/rdo
	chmod 755 /usr/local/bin/rdo
	chmod u+s /usr/local/bin/rdo

uninstall:
	rm /usr/local/bin/rdo

clean:
	rm rdo
