#include <stdio.h>

#include "game_state/game_state.h"

int main(int argc, char ** argv) {
  game_state_init();

  game_state_on_char_press('a');
  game_state_on_char_press('l');
  game_state_on_char_press('e');
  game_state_on_char_press('x');
  game_state_on_char_press(' ');
  game_state_on_char_press('i');

  game_state_on_submit();

  print_game_state();
  game_state_destroy();
  return 0;
}
