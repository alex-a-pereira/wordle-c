#ifndef GAME_STATE_H
#define GAME_STATE_H

#include <stdlib.h>
#include <time.h>

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
 * LOG BOX
 */

void set_log_box_message(char * logMessage, int timeoutSeconds);
char* get_log_box_message(void);

/**
 * USER INPUT HANDLERS
 */

// user presses an alpha char -> append to current guess if able to
void game_state_on_char_press(char guess);
// user presses backspace -> pop from current guess if able to
void game_state_on_backspace(void);
// user presses "enter" -> add current guess to word bank if able to
void game_state_on_submit(void);

void game_state_handle_key_press(char inputChar);

typedef enum _CHAR_GUESS_STATUS {
  NOT_YET_GUESSED,
  CHAR_NOT_IN_WORD,
  CHAR_IN_WORD_WRONG_IDX,
  CHAR_IN_WORD_CORRECT_IDX
} CHAR_GUESS_STATUS;

/**
 * GETTERS
 */

// TODO: think of a smoother way to return info to the UI

char get_current_guess_char(int idx);
int get_max_num_guesses(void);
// getter used to print chars of previous guesses
int get_previous_guesses_len(void);
int get_len_of_previous_guess(int previousGuessIdx);
char get_previous_guess_char(int previousGuessIdx, int idxOfCharInWord);
// getters used to determine game status
// TODO: boolean
int get_is_game_over(void);
int get_is_game_victory(void);
CHAR_GUESS_STATUS get_char_guess_status(char c);

/**
 * GAME LOGIC
 */

// TODO: boolean
int previous_guess_char_was_at_correct_idx(int previousGuessIdx, int idxOfCharInWord);
int previous_guess_char_was_in_word(int previousGuessIdx, int idxOfCharInWord);

/**
 * UTILS
 */

void print_game_state(void);

#endif
