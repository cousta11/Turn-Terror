SRC = src/main.c src/dungeon.c src/rand_to.c src/screen.c src/fight.c src/control.c
OBJ = $(SRC:.c=.o)
CC = clang
CFLAGS = -Wall -Wextra -g -O2
EXEC = Turn-Terror

.PHONY: all clean

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^ -lncurses

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(EXEC)
