# Compiler and flags
CC = clang
CFLAGS = -Wall -Wextra -std=c11 -g
LDFLAGS =

# Directories
SRC_DIR = src
ITEM_FNS_DIR = $(SRC_DIR)/item-fns
BUILD_DIR = build
BIN_DIR = bin

# Target executable
TARGET = $(BIN_DIR)/inventory-manager

# Source files
SRCS = $(SRC_DIR)/main.c \
       $(ITEM_FNS_DIR)/item_fns.c \
       $(ITEM_FNS_DIR)/read_line.c

# Object files
OBJS = $(SRCS:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o)

# Default target
all: $(TARGET)

# Create directories
$(BUILD_DIR) $(BIN_DIR) $(BUILD_DIR)/item-fns:
	mkdir -p $@

# Link object files to create executable
$(TARGET): $(OBJS) | $(BIN_DIR)
	$(CC) $(OBJS) $(LDFLAGS) -o $@
	@echo "Build complete: $(TARGET)"

# Compile source files to object files
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c | $(BUILD_DIR) $(BUILD_DIR)/item-fns
	$(CC) $(CFLAGS) -c $< -o $@

# Run the program
run: $(TARGET)
	./$(TARGET)

# Clean build artifacts
clean:
	rm -rf $(BUILD_DIR) $(BIN_DIR) a.out

# Remove executable only
cleanbin:
	rm -f $(TARGET)

# Debug build
debug: CFLAGS += -DDEBUG -O0
debug: clean $(TARGET)

# Release build
release: CFLAGS += -O2 -DNDEBUG
release: clean $(TARGET)

# Print variables (for debugging Makefile)
print-%:
	@echo $* = $($*)

.PHONY: all run clean cleanbin debug release print-%
