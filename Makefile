CC = gcc
OBJS = sand.o

%.o: %.c
	$(CC) -c -o $@ $<

sim: $(OBJS)
	$(CC) -o $@ $^ -lncurses

clean:
	rm -f sim *.o
