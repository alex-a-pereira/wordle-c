#ifndef WORD_H
#define WORD_H

#include <stdio.h>
#include <stdlib.h>

typedef void* WORD;

WORD word_init_default(void);

void print_word(WORD hWord);

#endif
