CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -O3
TARGET = tic_tac_toe
SOURCES = main.c game.c ai.c
HEADERS = game.h ai.h

all: $(TARGET)

$(TARGET): $(SOURCES) $(HEADERS)
	$(CC) $(CFLAGS) $(SOURCES) -o $(TARGET)

clean:
	rm -f $(TARGET)

.PHONY: all clean