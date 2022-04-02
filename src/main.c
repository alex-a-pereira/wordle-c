#include <stdio.h>

#include "user_interface/user_interface.h"
#include "game_state/game_state.h"

#include <unistd.h>

int main(int argc, char ** argv) {
  game_state_init();
  init_ui();

  int i = 0;

  while (1) {
    ui_get_input();
    print_ui();
  }

  // TODO: sigint handler
  game_state_destroy();
  destroy_ui();
  return 0;
}
