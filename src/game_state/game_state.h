#ifndef GAME_STATE_H
#define GAME_STATE_H

#include <stdlib.h>
#include "../lib/data_types/word/word.h"
#include "../lib/data_types/word_vector/word_vector.h"
#include "../lib/word_bank/word_bank.h"

typedef void* GAME_STATE;

// TODO: move to a `globals` module as it's needed for validating words
// when pulling them out of t
// const int WORD_LENGTH = 5;

// init/memory management
void game_state_init(void);
void game_state_destroy(void);

/**
 * USER INPUT HANDLERS
 */

// user presses an alpha char -> append to current guess if able to
void game_state_on_char_press(char guess);
// user presses backspace -> pop from current guess if able to
void game_state_on_backspace(void);
// user presses "enter" -> add current guess to word bank if able to
void game_state_on_submit(void);

/**
 * UTILS
 */

void print_game_state(void);

#endif
