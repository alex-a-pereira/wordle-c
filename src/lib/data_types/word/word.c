#include "word.h"

typedef struct _word {
  int length;
  int capacity;
  char * data;
} Word;

//
// ALLOCATION / MEMORY MANAGEMENT
//

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

WORD word_init_from_c_string(char * cString) {
  // first, get the necessary data from the c str argument
  // for a WORD with 5 chars in it, we have 5 items
  int lenCStr = 0;
  while (cString[lenCStr] != '\0') {
    lenCStr++;
  }

  // now, allocate the new one
  Word* pWord = NULL;
  pWord = (Word *)malloc(sizeof(Word));

  if (pWord != NULL) {
    pWord->length = lenCStr;
    pWord->capacity = 5;

    pWord->data = (char *)malloc(sizeof(char) * pWord->capacity);
    for (int i = 0; i < pWord->capacity; i++) {
      pWord->data[i] = cString[i];
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

// destructor
void word_free_from_memory(WORD * ptrToHWord) {
  // derefence the pointer to the handle to get the WORD (void ptr)
  // then cast the WORD (void ptr) to it's true type - a Word struct
  Word* pWord = (Word*)*ptrToHWord;
  // de-allocate the char array
  free(pWord->data);
  // de-allocate the struct
  free(pWord);
  // now we must set value of the the handle to NULL (so existing PTR doesn't point to free'd address)
  *ptrToHWord = NULL;
};

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

  printf("=== WORD ===\n");
  printf("len: %i\n", pWord->length);
  printf("capacity: %i\n", pWord->capacity);

  for (int i = 0; i < pWord->length; i++) {
    printf("%c", pWord->data[i]);
  }
  printf("\n");
  printf("============\n");
}

int word_get_size(WORD hWord);

int word_get_capacity(WORD hWord);