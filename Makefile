# Определение платформы
ifeq ($(OS),Windows_NT)
    PLATFORM = windows
else
    PLATFORM = linux
endif

# Общие настройки
CFLAGS := -Wall -Wextra -g -O2
DEPFLAGS := -MMD -MP
OBJ_DIR := obj
SRC_DIR := src
SOURCES := $(shell find $(SRC_DIR) -name '*.c')
OBJECTS := $(SOURCES:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
DEPFILES := $(OBJECTS:.o=.d)

# Платформо-зависимые настройки
ifeq ($(PLATFORM),windows)
    # Windows (MinGW) настройки
    CC := x86_64-w64-mingw32-gcc
    TARGET := Turn-Terror.exe
    
    MINGW_PREFIX := /usr/x86_64-w64-mingw32
    MINGW_INC := $(MINGW_PREFIX)/include
    MINGW_NCURSES_INC := $(MINGW_PREFIX)/include/ncursesw
    MINGW_LIB := $(MINGW_PREFIX)/lib
    
    INC_DIRS := $(shell find include -type d)
    CPPFLAGS := $(addprefix -I,$(INC_DIRS)) -I$(MINGW_INC) -I$(MINGW_NCURSES_INC) -DNCURSES_STATIC
    LDFLAGS := -L$(MINGW_LIB) -static
    LIBS := -lmenuw -lpanelw -lncursesw
    
else
    # Linux настройки
    CC := clang
    TARGET := Turn-Terror
    
    INC_DIRS := $(shell find include -type d)
    CPPFLAGS := $(addprefix -I,$(INC_DIRS))
    LDFLAGS := 
    LIBS := -lncurses -lpanel -lmenu
    
endif

# Дополнительные цели для ручного выбора платформы
.PHONY: windows linux clean distclean help

# Основная цель
all: $(TARGET)

# Цели для конкретных платформ
windows:
	@$(MAKE) PLATFORM=windows

linux:
	@$(MAKE) PLATFORM=linux

# Сборка целевого файла
$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^ $(LIBS)

# Компиляция объектных файлов
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(CPPFLAGS) $(DEPFLAGS) -c $< -o $@

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

# Очистка
clean:
	rm -rf $(OBJ_DIR) $(TARGET) $(TARGET).exe

distclean: clean
	rm -f $(TARGET)

# Отладочная информация
debug-info:
	@echo "Platform: $(PLATFORM)"
	@echo "Compiler: $(CC)"
	@echo "Target: $(TARGET)"
	@echo "CFLAGS: $(CFLAGS)"
	@echo "CPPFLAGS: $(CPPFLAGS)"
	@echo "LDFLAGS: $(LDFLAGS)"
	@echo "LIBS: $(LIBS)"

# Справка
help:
	@echo "Available targets:"
	@echo "  all       - Build for current platform ($(PLATFORM))"
	@echo "  windows   - Build for Windows (MinGW)"
	@echo "  linux     - Build for Linux"
	@echo "  clean     - Remove object files"
	@echo "  distclean - Remove object files and target"
	@echo "  debug-info - Show build configuration"
	@echo "  help      - Show this help"

-include $(DEPFILES)
