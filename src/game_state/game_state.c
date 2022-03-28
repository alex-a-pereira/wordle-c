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



GAME_STATE game_state_init_default(void) {
  GameState* pGameState = NULL;
  pGameState = (GameState*)malloc(sizeof(GameState));

  pGameState->maxNumGuesses = 6;
  pGameState->chosenWordToGuess = select_random_word();
  pGameState->numGuessesTaken = 0;
  pGameState->alreadyGuessedWords = word_vector_init_default();
  pGameState->currentGuessWord = word_init_default();

  return pGameState;
}

void game_state_destroy(GAME_STATE* ptrToHGameState) {
  GameState* pGameState = (GameState*)*ptrToHGameState;
  // free WORDs in state
  word_free_from_memory(&pGameState->chosenWordToGuess);
  word_free_from_memory(&pGameState->currentGuessWord);
  // free WORD_VECTORs in state
  word_vector_free_from_memory(&pGameState->alreadyGuessedWords);
  // free stack memory
  free(pGameState);
  // set the pointer to NULL to avoid junk value
  *ptrToHGameState = NULL;
}
