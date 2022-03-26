#include "word_bank.h"

void print_something(void) {
  WORD myWordBase = word_init_from_c_string("AUDIO");
  print_word(myWordBase);
  word_free_from_memory(&myWordBase);
}