CC=gcc
CFLAGS=-Wall --std=c99 
# OBJECTS=

main: ./src/main.c $(OBJECTS)
	$(CC) $(CFLAGS) ./src/main.c $(OBJECTS) -o play_wordle
