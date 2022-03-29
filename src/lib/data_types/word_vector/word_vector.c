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

/**
 * TODO: we current pass a pointer in here and simply add the pointer to the array
 *  but do we actually want to make a copy here?
 *  thinking that the issue would be freeing the vector would make out of scope pointers go NULL
 *    "out of scope" meaning a WORD initialized in main() would be NULL after calling word_vector_free_from_memory()
 *    if the WORD was in the word vector
 */
void word_vector_push(WORD_VECTOR hWordVector, WORD hWord) {
  WordVector* pWordVector = (WordVector*)hWordVector;

  // resize if length >= capacity
  if (pWordVector->length >= pWordVector->capacity) {
    int newCapacity = pWordVector->capacity * 2;
    // create the new items array. pWordVector->items will be re-assigned to this pointer after copying data in
    WORD * newItemsArr = (WORD)malloc(sizeof(WORD) * newCapacity);

    // copy the pointers to the existing items in the array to the newItemsArray
    for (int i = 0; i < pWordVector->length; i++) {
      newItemsArr[i] = pWordVector->items[i];
    }

    pWordVector->capacity = newCapacity;
    // free existing data as items have been moved to newItemsArr
    free(pWordVector->items);
    // re-assign the `items` ptr to temp data
    pWordVector->items = newItemsArr;
  }

  // TODO: need to resize the item array if length => capacity
  int idxOfNewItem = pWordVector->length;
  pWordVector->length = idxOfNewItem + 1;
  pWordVector->items[idxOfNewItem] = hWord;
}

int word_vector_get_length(WORD_VECTOR hWordVector) {
  WordVector* pWordVector = (WordVector*)hWordVector;
  return pWordVector->length;
}

// TODO: safe access? or just allow segfault? lol
WORD word_vector_at(WORD_VECTOR hWordVector, int idx) {
  WordVector* pWordVector = (WordVector*)hWordVector;
  return pWordVector->items[idx];
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
