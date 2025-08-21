# Makefile for c-stripper

CC ?= clang
CFLAGS = -Wall -O2
TARGET = c-stripper
SRC = c-stripper.c

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC)

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET)

