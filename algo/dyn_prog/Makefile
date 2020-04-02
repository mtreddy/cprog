DEBUG_ON	= -g3 -D DEBUG
DEBUG_OFF	= -O2
BASE		= -W

LIBFILES = # here test.o kind files added

CC			= g++
CFLAGS		= $(BASE)	$(DEBUG_ON) -g3
LIBS		=
LDFLAGS		=
AR			= ar

PROGS		= spath1 cut_rod knapscak
all: spath1 cut_rod

spath1: spath1.cpp
	${CC} ${CFLAGS} -o $@ spath1.cpp ${LIBS}

cut_rod: cut_rod.c
	${CC} ${CFLAGS} -o $@ cut_rod.c ${LIBS}

Cut_rod: knapscak.c
	${CC} ${CFLAGS} -o $@ knapscak.c ${LIBS}


clean:
	rm -f *.o ${PROGS}
		

