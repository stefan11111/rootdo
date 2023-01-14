CFLAGS = -Wall -Wextra -Werror -Wl,-z,now
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
	cp rdo ${DESTDIR}/usr/bin/rdo
	chown root:root ${DESTDIR}/usr/bin/rdo
	chmod 755 ${DESTDIR}/usr/bin/rdo
	chmod u+s ${DESTDIR}/usr/bin/rdo

uninstall:
	rm /usr/bin/rdo
	rm /etc/rdo.conf

clean:
	rm rdo
