#include "word.h"

/**
 * @brief allocates a WORD full of '*' char
 * @return pointer to the WORD set to '*****'
 */
WORD* word_init_default(void) {
  WORD* pWord = NULL;

  pWord = (WORD *)malloc(sizeof(WORD));

  if (pWord != NULL) {
    for (int i = 0; i < 5; i++) {
      *pWord[i] = '*';
    }
  }

  return pWord;
}
