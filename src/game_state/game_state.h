#ifndef GAME_STATE_H
#define GAME_STATE_H

#include <stdlib.h>
#include "../lib/data_types/word/word.h"
#include "../lib/data_types/word_vector/word_vector.h"
#include "../lib/word_bank/word_bank.h"

typedef void* GAME_STATE;

// init/memory management
void game_state_init(void);
void game_state_destroy(void);

/**
 * UTILS
 */

void print_game_state(void);

#endif
