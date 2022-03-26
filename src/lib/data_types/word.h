#ifndef WORD_H
#define WORD_H

#include <stdio.h>
#include <stdlib.h>

typedef void* WORD;

WORD word_init_default(void);

// getters
int word_get_len(WORD hWord);
int word_get_capacity(WORD hWord);

// utils
void print_word(WORD hWord);

#endif
