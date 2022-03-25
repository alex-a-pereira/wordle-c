CC=gcc
CFLAGS=-Wall --std=c99 
OBJECTS=./build/word.o

main: ./src/main.c $(OBJECTS)
	$(CC) $(CFLAGS) ./src/main.c $(OBJECTS) -o play_wordle

./build/word.o: ./src/lib/data_types/word.c
	$(CC) $(CFLAGS) -c -o $@ $<
