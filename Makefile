TARGET ?= main
OBJS = dangeon.o sup_func.o fight.c $(TARGET).o
CC = clang
CFLAGS = -Wall -g -O2

# Определяем ОС (Windows или Linux/MacOS)
ifeq ($(OS),Windows_NT)
	# Настройки для Windows (MinGW-w64)
	CFLAGS += --target=x86_64-w64-pc-windows-gnu
	LDFLAGS = -lpdcurses  # В MinGW-w64 используется pdcurses вместо ncurses
	INC = -I/usr/x86_64-w64-mingw32/include
	LIB = -L/usr/x86_64-w64-mingw32/lib
	TARGET := $(TARGET).exe
else
    # Настройки для Linux/MacOS
	LDFLAGS = -lncurses
endif

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(INC) $(LIB) -o $@ $^ $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) $(INC) -c $< -o $@

clean:
	rm -f *.o $(TARGET)

