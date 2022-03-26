#include <stdio.h>
#include "lib/data_types/word.h"

int main(int argc, char ** argv) {
  WORD myWord = word_init_default();
  print_word(myWord);
}
