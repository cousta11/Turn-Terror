SRC = src/main.c src/dangeon.c src/sup_func.c
OBJ = $(SRC:.c=.o)
CC = clang
CFLAGS = -Wall -Wextra -g -O2
EXEC = game


.PHONY: all clean

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^ -lncurses

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(EXEC)
