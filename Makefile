CC = gcc
CFLAGS = -Wall -Wextra -std=c99
TARGET = image_processor
SRCS = image_processor.c

all: $(TARGET)

$(TARGET): $(SRCS)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRCS)

clean:
	rm -f $(TARGET) *.o
