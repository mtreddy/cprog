DEBUG_ON	= -g3 -D DEBUG
DEBUG_OFF	= -O2
BASE		= -W

LIBFILES = # here test.o kind files added

CC			= g++
CFLAGS		= $(BASE)	$(DEBUG_ON)
LIBS		=
LDFLAGS		=
AR			= ar

PROGS		= btree
all: btree

btree: btree.cpp
	${CC} ${CFLAGS} -o $@ btree.cpp ${LIBS}

clean:
	rm -f *.o ${PROGS}
		

