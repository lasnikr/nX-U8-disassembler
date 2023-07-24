TARGET = disas

OBJDIR = obj
LIBDIR = $(OBJDIR)/lib
SRCDIR = src

CC = gcc
CFLAGS = -g
LDFLAGS = -g -lm

SOURCES := $(shell find $(SRCDIR) -type f -name '*.c')
OBJECTS := $(patsubst $(SRCDIR)/%,$(OBJDIR)/%,$(SOURCES:.c=.o))

all: $(LIBDIR) $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $^ $(LDFLAGS) -o $(TARGET)

$(LIBDIR):
	mkdir -p $(LIBDIR)

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) $(INC) -c -o $@ $<
