CC = gcc

all: hanoi

OBJS=towers_of_honoi.o

hanoi: $(OBJS) 
	$(CC) -o $@ $(OBJS)

$(OBJS) : towers_of_honoi.c
	$(CC) -c $< -o $@

clean:
	rm -f *.o hanoi
