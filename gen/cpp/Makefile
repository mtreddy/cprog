DEBUG_ON	= -g3 -D DEBUG
DEBUG_OFF	= -O2
BASE		= -W

LIBFILES = # here test.o kind files added

CC			= g++
CFLAGS		= $(BASE)	$(DEBUG_ON)
LIBS		=
LDFLAGS		=
AR			= ar

PROGS		= list
all: list

list: list.o
	${CC} ${CFLAGS} -o $@ list.o ${LIBS}

clean:
	rm -f *.o ${PROGS}
		

