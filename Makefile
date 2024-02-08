# Makefile for compiling maze program

# Compiler
CC = gcc

# Compiler flags
CFLAGS = -Wall -Werror -Wextra -pedantic -std=c99

# Directories
INCDIR = inc
SRCDIR = src
COREDIR = $(SRCDIR)/core
GRAPHICSDIR = $(SRCDIR)/graphics

# Source files
SRCS = $(wildcard $(SRCDIR)/*.c) \
       $(wildcard $(COREDIR)/*.c) \
       $(wildcard $(GRAPHICSDIR)/*.c)

# Header files
INCS = $(wildcard $(INCDIR)/*.h)

# Object files
OBJS = $(SRCS:.c=.o)

# Libraries
LIBS = -lSDL2 -lm

# Executable name
EXEC = PixelEscape

# Targets
all: $(EXEC)

$(EXEC): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)

# Compile source files
%.o: %.c $(INCS)
	$(CC) $(CFLAGS) -c $< -o $@

# Clean target
clean:
	rm -f $(OBJS) $(EXEC)
