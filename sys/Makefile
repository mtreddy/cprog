## Makefie


CC = gcc
CFLAGS = -g3

all: system_fn timeofday timer_hndlr tty
bin = system_fn timeofday timer_hndlr tty
input: system_fn.c timeofday.c timer_hndlr.c tty.c

$(all): 
	$(CC) ${CFLAGS}  -c $< -o $@

clean:
	rm ${bin}

