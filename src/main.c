#include <stdio.h>
#include "lib/data_types/word.h"

int main(int argc, char ** argv) {
  WORD* myWord = word_init_default();

  for (int i = 0; i < 5; i++) {
    printf("%s", myWord[i]);
  }
  printf("\n");
}