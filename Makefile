CC        := cc
CFLAGS    := -std=c11 -Wall -Wextra -Wpedantic -g -Iinclude
LDFLAGS   := -lm

TARGET    := main
SRC_DIR   := src
BUILD_DIR := build
BIN_DIR   := bin

SRCS      := $(wildcard $(SRC_DIR)/*.c)
OBJS      := $(patsubst $(SRC_DIR)/%.c,$(BUILD_DIR)/%.o,$(SRCS))
BIN       := $(BIN_DIR)/$(TARGET)

.PHONY: all run clean

all: $(BIN)

$(BIN): $(OBJS) | $(BIN_DIR)
	$(CC) $^ -o $@ $(LDFLAGS)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR) $(BIN_DIR):
	mkdir -p $@

run: $(BIN)
	./$(BIN) $(ARGS)

clean:
	rm -rf $(BUILD_DIR) $(BIN_DIR)
