#ifndef WORD_H
#define WORD_H

#include <stdio.h>
#include <stdlib.h>

#define WORD_LEN 5

typedef char WORD[WORD_LEN];

WORD* word_init_default(void);

void print_word(WORD * word);

#endif
