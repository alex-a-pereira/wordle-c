#include <stdio.h>
#include "lib/data_types/word_vector/word_vector.h"

int main(int argc, char ** argv) {
  WORD_VECTOR myWordVector = word_vector_init_default();

  WORD myWord = word_init_default();

  word_vector_push(myWordVector, myWord);

  print_word_vector(myWordVector);

  word_vector_free_from_memory(&myWordVector);

  return 0;
}
