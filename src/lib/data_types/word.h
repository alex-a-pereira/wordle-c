#ifndef WORD_H
#define WORD_H

#include <stdio.h>
#include <stdlib.h>

typedef struct _word {
  int length;
  int capacity;
  char * data;
} Word;

typedef void* WORD;

// allocation/memory management
WORD word_init_default(void);
WORD word_init_copy_from_other_word(WORD hWordSrc);
WORD word_init_from_c_string(char * cString);

void word_free_from_memory(WORD * ptrToHWord);

// getters
int word_get_len(WORD hWord);
int word_get_capacity(WORD hWord);

// utils
void print_word(WORD hWord);

#endif
