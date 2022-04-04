#include "word_bank.h"

WORD_BANK parse_word_bank_into_vector(void) {
  WORD_VECTOR allWordsVector = word_vector_init_default();

  char charFromFile;

  WORD tmpWord = NULL;

  FILE* fp = fopen("./src/lib/word_bank/wordbank.txt", "r");

  charFromFile = fgetc(fp);

  // iterate through the whole file
  while (charFromFile != EOF) {
    // each line
    tmpWord = word_init_default();

    // TODO: cleanup nested loop logic
    // need to also compare for EOF here in case no newline at end of file
    while (charFromFile != '\n' && charFromFile != EOF) {
      word_append_char(tmpWord, charFromFile);
      charFromFile = fgetc(fp);
    }

    word_vector_push(allWordsVector, tmpWord);

    // not necessary, but it's better to make sure it's
    tmpWord = NULL;
    // last char we pulled was a `\n`, so must increment again
    charFromFile = fgetc(fp);
  }

  fclose(fp);

  return allWordsVector;
}

int word_bank_get_length(WORD_BANK hWordBank) {
  WORD_VECTOR allWords = (WORD_VECTOR)hWordBank;
  return word_vector_get_length(allWords);
}

// TODO: (maybe) can implement caching here for duplicate guesses??
// probably not worth it, data set is small
int word_bank_includes_word(WORD_BANK hWordBank, WORD hWord) {
  WORD_VECTOR allWords = (WORD_VECTOR)hWordBank;
  int numWordsInBank = word_bank_get_length(hWordBank);
  for (int i = 0; i < numWordsInBank; i++) {
    int isValid = word_eq_other_word(hWord, word_vector_at(allWords, i));
    if (isValid) {
      return 1;
    }
  }

  return 0;
}

WORD select_random_word(WORD_BANK hWordBank) {
  WORD_VECTOR allWords = (WORD_VECTOR)hWordBank;

  WORD selectedWord = NULL;
  WORD selectedWordCopy = NULL;

  // get random selection
  int minIdx = 0;
  int maxIdx = word_vector_get_length(allWords);

  time_t t;
  srand((unsigned) time(&t));

  int randIdx = (rand() % (maxIdx - minIdx + 1)) + 1;
  selectedWord = word_vector_at(allWords, randIdx);
  // copy into a new pointer so we can free the vector safely
  selectedWordCopy = word_init_copy_from_other_word(selectedWord);
  // TODO: since WORD_BANK now needs to live for the entire runtime
  // we need to figure out a better way to clean up memory
  // word_vector_free_from_memory(&allWords);

  return selectedWordCopy;
}