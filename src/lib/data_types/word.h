#ifndef WORD_H
#define WORD_H

#include <stdio.h>
#include <stdlib.h>

typedef void* WORD;

// initialization
WORD word_init_default(void);
WORD word_init_copy_from_other_word(WORD hWordSrc);

// getters
int word_get_len(WORD hWord);
int word_get_capacity(WORD hWord);

// utils
void print_word(WORD hWord);

#endif
