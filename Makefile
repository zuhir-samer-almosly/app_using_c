CC      = gcc
CFLAGS  = -Wall -Wextra -pedantic -std=c99
TARGET  = text_app
SRC     = main.c

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC)

clean:
	rm -f $(TARGET)
