DEBUG_ON	= -g3 -D DEBUG
DEBUG_OFF	= -O2
BASE		= -W

LIBFILES = # here test.o kind files added

CC			= g++
CFLAGS		= $(BASE)	$(DEBUG_ON)
LIBS		=
LDFLAGS		=
AR			= ar

PROGS		= spath1
all: spath1

spath1: spath1.cpp
	${CC} ${CFLAGS} -o $@ spath1.cpp ${LIBS}

clean:
	rm -f *.o ${PROGS}
		

