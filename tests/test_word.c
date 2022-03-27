#include <stdio.h>
#include "../src/lib/data_types/word_vector/word_vector.h"

int main(int argc, char ** argv) {
  WORD initialWord = word_init_from_c_string("AUDIO");
  print_word(initialWord);
  // copy into a new WORD
  WORD wordCopy = word_init_copy_from_other_word(initialWord);
  // free the initial one (ensure no overlaps)
  word_free_from_memory(&initialWord);
  // 
  print_word(wordCopy);
  // TODO: add assertion once word_compare() is a function
  // cleanup
  word_free_from_memory(&wordCopy);
}
