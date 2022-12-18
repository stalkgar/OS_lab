TARGET = main
OBJECTS = main.o GrepHead.o

CC = gcc

.PHONY: clean

$(TARGET): $(OBJECTS) ./GrepHead.h
	$(CC) $(OBJECTS) -o $@

main.o: main.c
	$(CC) -c main.c
	
GrepHead.o: GrepHead.c
	$(CC) -c GrepHead.c

clean:
	rm -f $(OBJECTS)
	rm -f $(TARGET)