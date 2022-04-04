#include "game_state.h"

typedef struct _gameState {
  // the word bank
  WORD_BANK allValidWords;
  int maxNumGuesses;
  WORD alreadyGuessedChars;
  // the random word that the user should guess
  WORD chosenWordToGuess;
  WORD_VECTOR alreadyGuessedWords;
  // what is the user currently doing?
  WORD currentGuessWord;
  // LOG BOX MESSAGE
  WORD logBoxMessage;
  time_t logBoxMessageStartTime;
  int logBoxMessageTimeoutSeconds;
  // game status!
  int isGameOver;
  int isVictory;
} GameState;

GameState globalGameState;

//
// INIT/memory management
//

void game_state_init(void) {
  // parse all words into game_state
  // TODO: need to do memory cleanup on this guy!
  globalGameState.allValidWords = parse_word_bank_into_vector();
  // 
  globalGameState.maxNumGuesses = 6;
  globalGameState.chosenWordToGuess = select_random_word(globalGameState.allValidWords);
  globalGameState.alreadyGuessedWords = word_vector_init_default();
  globalGameState.alreadyGuessedChars = word_init_default();
  globalGameState.currentGuessWord = word_init_default();
  // log box
  globalGameState.logBoxMessage = "";
  globalGameState.logBoxMessageStartTime = time(NULL);
  globalGameState.logBoxMessageTimeoutSeconds = 0;
  // game status
  globalGameState.isGameOver = 0;
  globalGameState.isVictory = 0;
}

void game_state_destroy(void) {
  // reset int
  globalGameState.maxNumGuesses = 0;
  // free WORDs in state
  word_free_from_memory(&globalGameState.chosenWordToGuess);
  word_free_from_memory(&globalGameState.currentGuessWord);
  word_free_from_memory(&globalGameState.alreadyGuessedChars);
  // free WORD_VECTORs in state
  word_vector_free_from_memory(&globalGameState.alreadyGuessedWords);
  // set the pointer to NULL to avoid junk value
}

/**
 * LOG BOX
 * TODO: this entire section is insanely succeptible to memory leaks
 */

// Add a c string to the log box
void set_log_box_message(char * logMessage, int timeoutSeconds) {
  globalGameState.logBoxMessage = logMessage;
  globalGameState.logBoxMessageStartTime = time(NULL);
  globalGameState.logBoxMessageTimeoutSeconds = timeoutSeconds;
}

char* get_log_box_message(void) {
  time_t now = time(NULL);
  long secondsSinceLogStart = now - globalGameState.logBoxMessageStartTime;

  if (secondsSinceLogStart > globalGameState.logBoxMessageTimeoutSeconds) {
    return "";
  }

  return globalGameState.logBoxMessage;
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

int get_is_current_guess_valid_word(void) {
  return word_bank_includes_word(globalGameState.allValidWords, globalGameState.currentGuessWord);
}

// NOTE: the implementation doesn't account for "if already guessed, dont add it"
// so there will be duplicates in alreadyGuessedChars, e.g. if user submits `audio` and
// then `raids`, already guessed chars will be `audioraids`. This is OK performance wise
// as the max len is tiny, (maxNumGuesses * word length, i.e. 6 * 5 = 30)
void add_submitted_chars_to_already_guessed_charts() {
  int curLen = word_get_len(globalGameState.currentGuessWord);
  for (int i = 0; i < curLen; i++) {
    char charAtIdx = word_at_idx(globalGameState.currentGuessWord, i);
    word_append_char(
      globalGameState.alreadyGuessedChars, charAtIdx
    );
  }
}

void set_is_game_over(void) {
  int numGuessesTaken = word_vector_get_length(globalGameState.alreadyGuessedWords);

  // WINNER CASE (one of the previous guesses was correct)
  for (int i = 0; i < numGuessesTaken; i++) {
    int wasGuessCorrect = word_eq_other_word(
      word_vector_at(globalGameState.alreadyGuessedWords, i),
      globalGameState.chosenWordToGuess
    );

    if (wasGuessCorrect) {
      globalGameState.isGameOver = 1;
      globalGameState.isVictory = 1;
      return;
    }
  }

  // LOSER CASE (max num guesses has been reached)
  if (numGuessesTaken >= globalGameState.maxNumGuesses) {
    globalGameState.isGameOver = 1;
    globalGameState.isVictory = 0;
    return;
  }
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

  int isValidWord = get_is_current_guess_valid_word();
  if (!isValidWord) {
    set_log_box_message("Current guess is not in word bank!", 2);
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

  add_submitted_chars_to_already_guessed_charts();

  // it's safe to modify globalGameState.currentGuessWord pointer
  // as described above
  reset_current_guess_word();

  set_log_box_message("YOU HAVE SUBMITTED", 3);

  set_is_game_over();
}

void game_state_handle_key_press(char inputChar) {
  if (inputChar == '\n' || inputChar == '\r') {
    game_state_on_submit();
  }

  // TODO: handle backspace chars better? backspace comes through as 127 even tho it should be 8
  // maybe because of my shell? (tmux -> zsh on OSX). Investigate this
  if (inputChar == 8 || inputChar == 127) {
    game_state_on_backspace();
  }

  // handles all validation and no-ops if out of range
  game_state_on_char_press(inputChar);
}

//
// GETTERS
//

char get_current_guess_char(int idx) {
  int curLen = word_get_len(globalGameState.currentGuessWord);
  if (idx > curLen - 1) { return '\0'; }
  return word_at_idx(globalGameState.currentGuessWord, idx);
}

int get_max_num_guesses(void) {
  return globalGameState.maxNumGuesses;
}

char get_previous_guess_char(int previousGuessIdx, int idxOfCharInWord) {
  int lenOfPreviousGuesses = word_vector_get_length(globalGameState.alreadyGuessedWords);
  if (previousGuessIdx > lenOfPreviousGuesses - 1) { return '\0'; }

  WORD previousGuessAtIdx = word_vector_at(globalGameState.alreadyGuessedWords, previousGuessIdx);
  int lenOfPreviousGuessWord = word_get_len(previousGuessAtIdx);
  if (idxOfCharInWord > lenOfPreviousGuessWord - 1) { return '\0'; }

  return word_at_idx(previousGuessAtIdx, idxOfCharInWord);
}

int get_previous_guesses_len(void) {
  return word_vector_get_length(globalGameState.alreadyGuessedWords);
}

// TODO: should we really no-op here if out of range?
int get_len_of_previous_guess(int previousGuessIdx) {
  int lenOfPreviousGuesses = word_vector_get_length(globalGameState.alreadyGuessedWords);
  if (previousGuessIdx > lenOfPreviousGuesses - 1) { return 0; }

  WORD previousGuessAtIdx = word_vector_at(globalGameState.alreadyGuessedWords, previousGuessIdx);
  return word_get_len(previousGuessAtIdx);
}

int get_is_game_over(void) {
  return globalGameState.isGameOver;
}

int get_is_game_victory(void) {
  return globalGameState.isVictory;
}

CHAR_GUESS_STATUS get_char_guess_status(char c) {
  // since we optomistically iterate forward, this is used as a "default"
  // if no condition to return early is true.
  // initialized to CHAR_NOT_IN_WORD so if no conditions in loop are met, we return correct val.
  // It might get re-assigned later to CHAR_IN_WORD_WRONG_IDX
  CHAR_GUESS_STATUS status = CHAR_NOT_IN_WORD;

  // TODO: bool
  int hasAlreadyGuessed = word_includes(globalGameState.alreadyGuessedChars, c);
  if (!hasAlreadyGuessed) {
    return NOT_YET_GUESSED;
  }

  /**
   *  iterate over every word (returns early if a perfect match is found).
   *   We optomistically iterate through every guessed char to see if there's
   *     a BETTER match in subsequent guesses, e.g.
   *   - actual word: "AUDIO"
   *   - guess1: "BREAK" -> resolves to CHAR_IN_WORD_WRONG_IDX
   *   - guess2: "ALTER" -> resolves to CHAR_IN_WORD_CORRECT_IDX
   */
  int numGuesses = get_previous_guesses_len();
  for (int idxOfGuessWord = 0; idxOfGuessWord < numGuesses; idxOfGuessWord++) {
    // iterate over every char in each word
    int currWordToPrintLen = get_len_of_previous_guess(idxOfGuessWord);
    for (int idxOfCharInWord = 0; idxOfCharInWord < currWordToPrintLen; idxOfCharInWord++) {
      // we can skip logic below if we haven't guessed it yet
      char prevGuessChar = get_previous_guess_char(idxOfGuessWord, idxOfCharInWord);
      if (prevGuessChar != c) {
        continue;
      }

      int charInPreviousGuessAtCorrectIdx = previous_guess_char_was_at_correct_idx(idxOfGuessWord, idxOfCharInWord);

      // can return early if best possible case is true
      if (charInPreviousGuessAtCorrectIdx) {
        return CHAR_IN_WORD_CORRECT_IDX;
      }

      // CAN'T return early if this status is 
      int charInPreviousGuessWasInWord = previous_guess_char_was_in_word(idxOfGuessWord, idxOfCharInWord);
      if (charInPreviousGuessWasInWord) {
        status = CHAR_IN_WORD_WRONG_IDX;
      }
    }
  }

  return status;
}

/**
 * GAME LOGIC
 */

int previous_guess_char_was_at_correct_idx(int previousGuessIdx, int idxOfCharInWord) {
  char charAtPreviousGuess = get_previous_guess_char(previousGuessIdx, idxOfCharInWord);
  char chosenWordToGuessAtIdx = word_at_idx(globalGameState.chosenWordToGuess, idxOfCharInWord);
  return charAtPreviousGuess == chosenWordToGuessAtIdx;
}

int previous_guess_char_was_in_word(int previousGuessIdx, int idxOfCharInWord) {
  char charAtPreviousGuess = get_previous_guess_char(previousGuessIdx, idxOfCharInWord);
  return word_includes(globalGameState.chosenWordToGuess, charAtPreviousGuess);
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
