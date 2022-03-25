#include "word.h"

/**
 * @brief allocates a WORD full of '*' char
 * @return pointer to the WORD set to '*****'
 */
WORD* word_init_default(void) {
  WORD* pWord = NULL;

  pWord = (WORD *)malloc(sizeof(WORD));

  if (pWord != NULL) {
    for (int i = 0; i < WORD_LEN; i++) {
      *pWord[i] = '*';
    }
  }

  return pWord;
}

void print_word(WORD *word) {
  for (int i = 0; i < WORD_LEN; i++) {
    printf("%s", word[i]);
  }
  printf("\n");
}
