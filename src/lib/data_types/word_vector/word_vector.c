#include "word_vector.h"

/**
 * TODO:
 * We probably don't need to expose capacity to consumers.
 * Since it's an implementation-specific detail, we can default to ANY capacity
 *  rather than just 1
 */

//
// ALLOCATION / MEMORY MANAGEMENT
//

typedef struct _wordVector {
  int length;
  int capacity;
  // pointer to the WORD at the start of the array
  WORD * items;
} WordVector;

/**
 * @brief allocates a WordVector with 0 items and (an arbitrarily set) capactiy
 * @return void pointer to the WordVector struct
 */
WORD_VECTOR word_vector_init_default(void) {
  WordVector* pWordVector = NULL;

  pWordVector = (WordVector*)malloc(sizeof(WordVector));

  if (pWordVector != NULL) {
    pWordVector->length = 0;
    // start with simply being able to have 1 item in the vector
    // we will dynamically resize later if needed.
    pWordVector->capacity = 1; // see TODO at top of file
    pWordVector->items = (WORD)malloc(sizeof(WORD) * pWordVector->capacity);
  }

  return pWordVector;
}

void word_vector_free_from_memory(WORD_VECTOR * ptrToHWordVector) {
  // derefence the pointer to the handle to get the WORD (void ptr)
  // then cast the WORD (void ptr) to it's true type - a Word struct
  WordVector* pWordVector = (WordVector*)*ptrToHWordVector;

  // free each word in the vector from memory
  for (int i = 0; i < pWordVector->length; i++) {
    WORD wordToFree = pWordVector->items[i];
    // pass in the ADDRESS of the pointer to the word
    word_free_from_memory(&wordToFree);
  }
  
  // free the array of pointers from memory
  free(pWordVector->items);
  // free the struct from memory
  free(pWordVector);
  // set the value of the address passed as an argument to NULL
  *ptrToHWordVector = NULL;
}

//
// ARRAY METHODS
//

void word_vector_push(WORD_VECTOR hWordVector, WORD hWord) {
  WordVector* pWordVector = (WordVector*)hWordVector;
  // TODO: need to resize the item array if length => capacity
  int idxOfNewItem = pWordVector->length;
  pWordVector->length = idxOfNewItem + 1;
  pWordVector->items[idxOfNewItem] = hWord;
}


//
// UTILS
//

void print_word_vector(WORD_VECTOR hWordVector) {
  WordVector* pWordVector = (WordVector*)hWordVector;

  printf("++++ WORD VECTOR ++++\n");
  for (int i = 0; i < pWordVector->length; i++) {
    WORD wordToPrint = pWordVector->items[i];
    print_word(wordToPrint);
  }
}
