CC := clang
CFLAGS := -Wall -Wextra -g -O2
DEPFLAGS := -MMD -MP
OBJ_DIR := obj
INC_DIR := include
SRC_DIR := src

# Находим все исходные файлы с сохранением структуры поддиректорий
SOURCES := $(shell find $(SRC_DIR) -name '*.c')
# Сохраняем структуру поддиректорий в obj
OBJECTS := $(SOURCES:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
DEPFILES := $(OBJECTS:.o=.d)

TARGET := Turn-Terror

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^ -lncurses -lpanel

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(DEPFLAGS) -I$(INC_DIR) -c $< -o $@

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

-include $(DEPFILES)

clean:
	rm -rf $(OBJ_DIR) $(TARGET)
