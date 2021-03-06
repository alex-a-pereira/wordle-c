#include <stdio.h>

#include "../src/game_state/game_state.h"

int test_game_state_input_one_word_and_submit (void) {
  game_state_init();

  // enter a word, but user made a typo (should be `audio`)
  game_state_on_char_press('a');
  game_state_on_char_press('l');
  game_state_on_char_press('d');
  game_state_on_char_press('i');
  game_state_on_char_press('o');

  // user realizes their mistake!
  game_state_on_backspace();
  game_state_on_backspace();
  game_state_on_backspace();
  game_state_on_backspace();
  game_state_on_backspace();

  game_state_on_char_press('a');
  game_state_on_char_press('u');
  game_state_on_char_press('d');
  game_state_on_char_press('i');
  game_state_on_char_press('o');

  game_state_on_submit();

  print_game_state();
  game_state_destroy();

  return 0;
}

// asserts that submitting more than the max num guesses doesn't do anything
int test_game_state_submit_max_num_words(void) {
  game_state_init();

  for (int i = 0; i < 8; i++) {
    game_state_on_char_press('a');
    game_state_on_char_press('u');
    game_state_on_char_press('d');
    game_state_on_char_press('i');
    game_state_on_char_press('o');
    game_state_on_submit();
  }

  // TODO: assert programatically that length == 6
  print_game_state();
  game_state_destroy();

  return 0;
}

int main(int argc, char ** argv) {
  int status = 0;

  status = test_game_state_input_one_word_and_submit();
  if (status != 0) { return status; }

  status = test_game_state_submit_max_num_words();
  if (status != 0) { return status; }

  return status;
}
