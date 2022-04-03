#ifndef WORD_BANK_H
#define WORD_BANK_H

#include <time.h>

#include "../data_types/word/word.h"
#include "../data_types/word_vector/word_vector.h"

typedef void* WORD_BANK;

WORD_BANK parse_word_bank_into_vector(void);
// TODO: boolean
int word_bank_get_length(WORD_BANK hWordBank);
int word_bank_includes_word(WORD_BANK hWordBank, WORD hWord);

WORD select_random_word(WORD_BANK hWordBank);

#endif
