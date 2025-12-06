
# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -O2 `sdl2-config --cflags`
LDFLAGS = `sdl2-config --libs` -lSDL2_image -pthread

# Source files
SRC = main.c src/dirscan.c src/imageload.c src/bg_thread.c src/utils.c

# Output binary
OUT = iv

# Default target
all: $(OUT)

# Build binary
$(OUT): $(SRC)
	$(CC) $(CFLAGS) -o $(OUT) $(SRC) $(LDFLAGS)

# Clean object files and binary
clean:
	rm -f $(OUT)
