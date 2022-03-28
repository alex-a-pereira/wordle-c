#ifndef WORD_VECTOR_H
#define WORD_VECTOR_H

#include "../word/word.h"

typedef void * WORD_VECTOR;

WORD_VECTOR word_vector_init_default(void);

void word_vector_free_from_memory(WORD_VECTOR * ptrToHWordVector);

// ARRAY METHODS
void word_vector_push(WORD_VECTOR hWordVector, WORD hWord);
int word_vector_get_length(WORD_VECTOR hWordVector);
WORD word_vector_at(WORD_VECTOR hWordVector, int idx);

// UTILS
void print_word_vector(WORD_VECTOR hWordVector);

#endif
