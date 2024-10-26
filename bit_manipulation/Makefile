# Compiler and flags
CC = gcc
CFLAGS = -Wall

# Directories
SRC_DIR = ../common
OBJ_DIR = obj

# Source files
SOURCES = source.c $(SRC_DIR)/common.c
HEADERS = $(SRC_DIR)/common.h

# Output executable
OUTPUT = source

# Default target
all: $(OUTPUT)

# Rule to build the executable
$(OUTPUT): $(SOURCES) $(HEADERS)
	$(CC) $(CFLAGS) -o $(OUTPUT) $(SOURCES)

# Clean up generated files
clean:
	rm -f $(OUTPUT) *.o
