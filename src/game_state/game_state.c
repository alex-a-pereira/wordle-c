#include "game_state.h"

typedef struct _gameState {
  int maxNumGuesses;
  // the random word that the user should guess
  WORD chosenWordToGuess;
  // what has the user already done?
  int numGuessesTaken;
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
  globalGameState.numGuessesTaken = 0;
  globalGameState.alreadyGuessedWords = word_vector_init_default();
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

//
// UTILS
//

void print_game_state(void) {
  print_word(globalGameState.chosenWordToGuess);
}
