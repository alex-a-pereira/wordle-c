#include <stdio.h>

#include "game_state/game_state.h"

int main(int argc, char ** argv) {
  GAME_STATE gameState = game_state_init_default();
  game_state_destroy(&gameState);
  return 0;
}
