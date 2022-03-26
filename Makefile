CC=gcc
CFLAGS=-Wall --std=c99 
OBJECTS=./build/word.o ./build/word_vector.o

main: ./src/main.c $(OBJECTS)
	$(CC) $(CFLAGS) ./src/main.c $(OBJECTS) -o play_wordle

./build/word_vector.o: ./src/lib/data_types/word_vector/word_vector.c
	$(CC) $(CFLAGS) -c -o $@ $<

./build/word.o: ./src/lib/data_types/word/word.c
	$(CC) $(CFLAGS) -c -o $@ $<

# leave dir in tact
clean:
	rm -f play_wordle build/*.o
