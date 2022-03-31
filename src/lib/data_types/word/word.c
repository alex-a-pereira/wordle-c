#include "word.h"

typedef struct _word {
  int length;
  int capacity;
  char * data;
} Word;

//
// ALLOCATION / MEMORY MANAGEMENT
//

WORD word_init_default(void) {
  Word* pWord = NULL;

  pWord = (Word *)malloc(sizeof(Word));

  if (pWord != NULL) {
    pWord->length = 0;
    pWord->capacity = 8;

    pWord->data = (char *)malloc(sizeof(char) * pWord->capacity);
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
    pWord->capacity = lenCStr;

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

//
// STRING METHODS
//

void word_append_char(WORD hWord, char charToAppend) {
  Word* pWord = (Word*)hWord;

  // resize to double capacity
  if (pWord->length >= pWord-> capacity) {
    int newCapacity = pWord->capacity * 2;
    printf("Word capacity reached - current = %i, new  = %i\n", pWord->capacity, newCapacity);

    char * newDataArr = (char *)malloc(sizeof(char) * newCapacity);

    for (int i = 0; i < pWord->length; i++) {
      newDataArr[i] = pWord->data[i];
    }

    pWord->capacity = newCapacity;
    free(pWord->data);
    pWord->data = newDataArr;
  }

  int idxOfNewItem = pWord->length;
  pWord->length++;
  pWord->data[idxOfNewItem] = charToAppend;
} 

void word_pop_char(WORD hWord) {
  Word* pWord = (Word*)hWord;
  // if length is already 0, this is a no-op
  if (pWord->length == 0) { return; }
  // don't need to actually modify memory
  pWord->length = pWord->length - 1; 
}

int word_includes(WORD hWord, char c) {
  Word* pWord = (Word*)hWord;
  for (int i = 0; i < pWord->length; i++) {
    if (pWord->data[i] == c) { return 1; }
  }
  return 0;
}

// TODO: safe access? or just allow segfault? lol
char word_at_idx(WORD hWord, int idx) {
  Word* pWord = (Word*)hWord;
  return pWord->data[idx];
}

// destructor
void word_free_from_memory(WORD * ptrToHWord) {
  // derefence the pointer to the handle to get the WORD (void ptr)
  // then cast the WORD (void ptr) to it's true type - a Word struct
  Word* pWord = (Word*)*ptrToHWord;
  // TODO, is this a memory leak?? i dont think so, since we specify the num items when we malloc()
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
  for (int i = 0; i < pWord->length; i++) {
    printf("%c", pWord->data[i]);
  }
}

int word_get_size(WORD hWord);

int word_get_capacity(WORD hWord);