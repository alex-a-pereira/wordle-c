#include "word.h"

struct word {
  int length;
  int capacity;
  char * data;
};

typedef struct word Word;

/**
 * @brief allocates a Word struct full of '*' char
 * @return void pointer to the Word struct, set to '*****'
 */
WORD word_init_default(void) {
  Word* pWord = NULL;

  pWord = (Word *)malloc(sizeof(Word));

  if (pWord != NULL) {
    pWord->length = 5;
    pWord->capacity = 5;

    pWord->data = (char *)malloc(sizeof(char) * pWord->capacity);
    for (int i = 0; i < pWord->capacity; i++) {
      pWord->data[i] = '*';
    }
  }

  return pWord;
}

WORD word_init_copy_from_other_word(WORD hWordSrc) {
  Word* pWordSrc = (Word*)hWordSrc;
  // allocate new
  Word* pWordCopy = NULL;
  pWordCopy = (Word *)malloc(sizeof(Word));

  if (pWordCopy != NULL) {
    pWordCopy->capacity = pWordSrc->capacity;
    pWordCopy->length = pWordSrc->length;

    pWordCopy->data = (char *)malloc(sizeof(char) * pWordCopy->capacity);
    for (int i = 0; i < pWordCopy->capacity; i++) {
      pWordCopy->data[i] = pWordSrc->data[i];
    }
  }

  return pWordCopy;
}

// 
// GETTERS
// 

int word_get_len(WORD hWord) {
  Word* pWord = (Word*)hWord;
  return pWord->length;
};

int word_get_capacity(WORD hWord) {
  Word* pWord = (Word*)hWord;
  return pWord->capacity;
};


// 
// UTILS
// 

/**
 * @brief prints a word from front to back
 * 
 * @param hWord handle to the Word struct
 */
void print_word(WORD hWord) {
  // cast from void pointer to known type
  Word* pWord = (Word*)hWord;

  for (int i = 0; i < pWord->length; i++) {
    printf("%c", pWord->data[i]);
  }
  printf("\n");
}

int word_get_size(WORD hWord);

int word_get_capacity(WORD hWord);