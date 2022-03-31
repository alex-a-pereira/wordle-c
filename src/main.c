#include <stdio.h>

#include "user_interface/user_interface.h"
#include "game_state/game_state.h"

#include <unistd.h>

int main(int argc, char ** argv) {
  init_ui();

  while (1) {
    print_ui();
  }

  destroy_ui();
  return 0;
}
