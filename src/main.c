#include <stdio.h>

#include "game_state/game_state.h"

int main(int argc, char ** argv) {
  game_state_init();
  print_game_state();
  game_state_destroy();
  return 0;
}
