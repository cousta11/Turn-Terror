CC := clang
CFLAGS := -Wall -Wextra -g -O2
DEPFLAGS := -MMD -MP
OBJ_DIR := obj
INC_DIR := include
SRC_DIR := src

SOURCES := $(shell find $(SRC_DIR) -name '*.c')
OBJECTS := $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SOURCES))
DEPFILES := $(OBJECTS:.o=.d)

TARGET := Turn-Terror

.PHONY: all cgi clean

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^ -lncurses -lpanel -lmenu

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(DEPFLAGS) -I$(INC_DIR) -c $< -o $@

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

-include $(DEPFILES)

clean:
	rm -rf $(OBJ_DIR) $(TARGET)
