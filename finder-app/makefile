
# Check if CROSS_COMPILE is specified
ifdef CROSS_COMPILE
    CC := $(CROSS_COMPILE)$(CC)
endif

.PHONY: all clean

all: writer.c
	$(CC) writer.c -o writer

clean:
	rm -rf *.o writer

