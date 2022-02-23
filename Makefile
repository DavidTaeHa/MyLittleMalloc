TARGET1 = memgrind
TARGET2 = mymalloc
CC = gcc
CFLAGS = -g -Wall

all: $(TARGET1)

$(TARGET2): $(TARGET2).c
	$(CC) $(CFLAGS) -o mm $(TARGET2).c

memgrind: $(TARGET2).c $(TARGET1).c
	$(CC) $(CFLAGS) -c $(TARGET2).c
	$(CC) $(CFLAGS) -o $(TARGET1)$(TARGET1).c $(TARGET2).o
clean:
	rm -f $(TARGET2).o $(TARGET1)
