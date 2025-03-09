# Compiler
CC = gcc

# Directories
SRC_DIR = server
CLIENT_DIR = client
BUILD_DIR = build

# Source files
SERVER_SRC = $(SRC_DIR)/main.c
CLIENT_SRC = $(CLIENT_DIR)/main.c

# Output binaries
SERVER_BIN = $(BUILD_DIR)/server
CLIENT_BIN = $(BUILD_DIR)/client

# Compiler flags
CFLAGS = -Wall -Wextra -Werror

# Targets
all: $(SERVER_BIN) $(CLIENT_BIN)

$(BUILD_DIR):
    mkdir -p $(BUILD_DIR)

$(SERVER_BIN): $(SERVER_SRC) | $(BUILD_DIR)
    $(CC) $(CFLAGS) -o $@ $<

$(CLIENT_BIN): $(CLIENT_SRC) | $(BUILD_DIR)
    $(CC) $(CFLAGS) -o $@ $<

clean:
    rm -rf $(BUILD_DIR)

.PHONY: all clean