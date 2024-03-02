CC = gcc
CFLAGS = -Wall -Wextra
LDFLAGS =
TARGET = writer

# Check if CROSS_COMPILE is specified
ifdef CROSS_COMPILE
    CC := $(CROSS_COMPILE)$(CC)
endif

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(TARGET).o
    $(CC) $(LDFLAGS) -o $@ $^

$(TARGET).o: $(TARGET).c
    $(CC) $(CFLAGS) -c -o $@ $<

clean:
    $(RM) $(TARGET) $(TARGET).o
