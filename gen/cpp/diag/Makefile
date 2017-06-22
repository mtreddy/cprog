DEBUG_ON	= -g3 -D DEBUG
DEBUG_OFF	= -O2
BASE		= -W

LIBFILES = # here test.o kind files added

CC			= g++
CFLAGS		= $(BASE)	$(DEBUG_ON)
LIBS		=
LDFLAGS		=
AR			= ar

PROGS		= qsfp_dt
all: qsfp_dt

qsfp_dt: qsfp_dt.o
	${CC} ${CFLAGS} -o $@ qsfp_dt.o ${LIBS}

clean:
	rm -f *.o ${PROGS}
		

