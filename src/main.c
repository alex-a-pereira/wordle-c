#include <stdio.h>
#include "lib/data_types/word.h"

int main(int argc, char ** argv) {
  // WORD myWordBase = word_init_default();
  WORD myWordBase = word_init_from_c_string("AUDIO");
  print_word(myWordBase);

  WORD myWord = word_init_copy_from_other_word(myWordBase);
  // free the base
  word_free_from_memory(&myWordBase);
  // print the copy
  print_word(myWord);
  // free the copy
  word_free_from_memory(&myWord);
}
