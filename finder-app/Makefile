# The name of the output executable
EXECUTABLE = writer

# The compiler to use
ifdef CROSS_COMPILE
	CC = $(CROSS_COMPILE)gcc
else
	CC = gcc
endif

# Compiler flags
CFLAGS = -Wall -Wextra

# The source files
SRC = writer.c

# Object files to build
OBJ = $(SRC:.c=.o)

# Default target: build the executable
.PHONY: all
all: $(EXECUTABLE)

# Rule to build the executable
$(EXECUTABLE): $(OBJ)
	$(CC) $(CFLAGS) $^ -o $@

# Rule to build object files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean target: remove the executable and object files
.PHONY: clean
clean:
	$(RM) $(EXECUTABLE) $(OBJ)
