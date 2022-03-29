#include <stdio.h>
#include "lib/data_types/word_vector/word_vector.h"

int main(int argc, char ** argv) {
  FILE* fp = fopen("./src/lib/word_bank/wordbank.txt", "r");

  // add a few default words to the vector
  // WORD myWord = word_extract_from_file(fp);
  // WORD myWord1 = word_extract_from_file(fp);
  WORD myWord = word_init_from_c_string("ALEX");

  for (int i = 1; i < 10; i++) {
    word_append_char(myWord, '!');
  }

  WORD myWord1 = word_init_from_c_string("hjksdfhjksdfhjksdfhkjsdfhkj");

  print_word(myWord);
  print_word(myWord1);

  word_free_from_memory(&myWord);
  word_free_from_memory(&myWord1);

  return 0;
}
