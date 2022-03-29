# COMMON FLAGS
CC=gcc
CFLAGS=-Wall --std=c99 
# RUN FLAGS
OBJECTS=./build/word.o ./build/word_vector.o ./build/word_bank.o
# DEBUG FLAGS
CFLAGS_DEBUG=$(CFLAGS) -g
DEBUG_OBJECTS=./build_debug/word.o ./build_debug/word_vector.o ./build_debug/word_bank.o

# RUN
all: main
main: ./src/main.c $(OBJECTS)
	$(CC) $(CFLAGS) ./src/main.c $(OBJECTS) -o play_wordle

./build/word_vector.o: ./src/lib/data_types/word_vector/word_vector.c
	$(CC) $(CFLAGS) -g -c -o $@ $<

./build/word.o: ./src/lib/data_types/word/word.c
	$(CC) $(CFLAGS) -g -c -o $@ $<

./build/word_bank.o: ./src/lib/word_bank/word_bank.c
	$(CC) $(CFLAGS) -g -c -o $@ $<

# DEBUG
debug: ./src/main.c $(OBJECTS)
	$(CC) $(CFLAGS_DEBUG) ./src/main.c $(OBJECTS) -o play_wordle__debug

./build_debug/word_vector.o: ./src/lib/data_types/word_vector/word_vector.c
	$(CC) $(CFLAGS_DEBUG) -c -o $@ $<

./build_debug/word.o: ./src/lib/data_types/word/word.c
	$(CC) $(CFLAGS_DEBUG) -g -c -o $@ $<

./build_debug/word_bank.o: ./src/lib/word_bank/word_bank.c
	$(CC) $(CFLAGS_DEBUG) -g -c -o $@ $<

# TESTS
test_word: ./tests/test_word.c $(OBJECTS)
	$(CC) $(CFLAGS) ./tests/test_word.c $(OBJECTS) -o _test_word

# leave dir in tact
clean:
	rm -f play_wordle build/*.o
	rm -rf play_wordle__debug play_wordle__debug.dSYM/ build_debug/*.o 
