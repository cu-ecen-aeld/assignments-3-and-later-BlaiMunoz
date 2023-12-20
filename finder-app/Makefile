CC = gcc
CFLAGS = -Wall -Wextra -O2
TARGET = writer
SRC = writer.c
OBJ = $(SRC:.c=.o)

ifeq ($(CROSS_COMPILE),aarch64-none-linux-gnu-)
	CC = aarch64-none-linux-gnu-gcc
endif

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(TARGET) $(OBJ)

.PHONY: all clean
