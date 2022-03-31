#ifndef WORD_H
#define WORD_H

#include <stdio.h>
#include <stdlib.h>

// Word struct is only used by implementation so it's defined at top of word.c
// It's added in comments here for convenience of those working on word implementation files
// typedef struct _word {
//   int length;
//   int capacity;
//   char * data;
// } Word;

// all consumers interact with a void ptr to set up strong boundaries between modules
typedef void* WORD;

// allocation/memory management
WORD word_init_default(void);
WORD word_init_copy_from_other_word(WORD hWordSrc);
WORD word_init_from_c_string(char * cString);

void word_free_from_memory(WORD * ptrToHWord);

// string methods
void word_append_char(WORD hWord, char charToAppend);
void word_pop_char(WORD hWord);
// TODO: boolean
int word_includes(WORD hWord, char c);
char word_at_idx(WORD hWord, int idx);

// getters
int word_get_len(WORD hWord);
// TODO: we probably don't need to expose this as it's implementation specific?
int word_get_capacity(WORD hWord);

// utils
void print_word(WORD hWord);

#endif
