#include "game_state.h"

typedef struct _gameState {
  int maxNumGuesses;
  WORD alreadyGuessedChars;
  // the random word that the user should guess
  WORD chosenWordToGuess;
  WORD_VECTOR alreadyGuessedWords;
  // what is the user currently doing?
  WORD currentGuessWord;
} GameState;

GameState globalGameState;

//
// INIT/memory management
//

void game_state_init(void) {
  globalGameState.maxNumGuesses = 6;
  globalGameState.chosenWordToGuess = select_random_word();
  globalGameState.alreadyGuessedWords = word_vector_init_default();
  globalGameState.alreadyGuessedChars = word_init_default();
  globalGameState.currentGuessWord = word_init_default();
}

void game_state_destroy(void) {

  // free WORDs in state
  word_free_from_memory(&globalGameState.chosenWordToGuess);
  word_free_from_memory(&globalGameState.currentGuessWord);
  // free WORD_VECTORs in state
  word_vector_free_from_memory(&globalGameState.alreadyGuessedWords);
  // set the pointer to NULL to avoid junk value
}

/**
 * INTERNAL HELPERS
 */

/**
 * @brief converts an ascii char to uppercase
 * 
 * @param c any ascii alpha char
 * @return 0 if "invalid" (not alpha) or the uppercase version of the character
 */
char alphaToUpper (char c) {
  char charAsUpper = c;

  if (c > 90) { charAsUpper = c - 32; }
  // if invalid, return 0 so consumers can do "if (!toUpper(myChar) { return; }"
  if (charAsUpper < 65 || charAsUpper > 90) { return 0; }

  return charAsUpper;
}

// clears out the current guess to an empty WORD
void reset_current_guess_word(void) {
  word_free_from_memory(&globalGameState.currentGuessWord);
  globalGameState.currentGuessWord = word_init_default();
}

int get_num_guesses_taken(void) {
  return word_vector_get_length(globalGameState.alreadyGuessedWords);
}

/**
 * USER INPUT HANDLERS
 */

// user presses an alpha char -> append to current guess if able to
void game_state_on_char_press(char c) {
  char guess = alphaToUpper(c);
  if (!guess) { return; } // non alpha char

  int curLen = word_get_len(globalGameState.currentGuessWord);
  // TODO: global instead of magic number
  if (curLen >= 5) { return; }

  if (get_num_guesses_taken() >= globalGameState.maxNumGuesses) {
    return;
  }

  word_append_char(globalGameState.currentGuessWord, guess);
}

// user presses backspace -> pop from current guess if able to
void game_state_on_backspace(void) {
  word_pop_char(globalGameState.currentGuessWord);
}

// user presses "enter" -> add current guess to word bank if able to
void game_state_on_submit(void) {
  int lenOfCurrentWord = word_get_len(globalGameState.currentGuessWord);
  if (lenOfCurrentWord != 5) {
    return;
  }

  // can't guess if we've already exceeded max num guesses
  if (get_num_guesses_taken() >= globalGameState.maxNumGuesses) {
    return;
  }

  // push the guess onto the vector. the function COPIES currentGuessWord,
  // so currentGuessWord can be modified after pushing worrying about
  // modifying the item in the array
  word_vector_push(
    globalGameState.alreadyGuessedWords,
    globalGameState.currentGuessWord
  );

  // it's safe to modify globalGameState.currentGuessWord pointer
  // as described above
  reset_current_guess_word();
}

//
// UTILS
//

void print_game_state(void) {
  printf("Word to guess: ");
  print_word(globalGameState.chosenWordToGuess);

  printf("\nCurrent guess word: ");
  print_word(globalGameState.currentGuessWord);

  printf("\nAlready guessed chars: ");
  print_word(globalGameState.alreadyGuessedChars);

  printf("\nAlready guessed words:\n");
  print_word_vector(globalGameState.alreadyGuessedWords);

  printf("\n");
}
