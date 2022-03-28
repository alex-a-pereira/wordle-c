#include "word_bank.h"

WORD_VECTOR parse_word_bank_into_vector(void) {
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

WORD select_random_word(void) {
  WORD_VECTOR allWords = parse_word_bank_into_vector();

  int minIdx = 0;
  int maxIdx = word_vector_get_length(allWords);

  int randIdx = (rand() % (maxIdx - minIdx + 1)) + 1;

  return word_vector_at(allWords, randIdx);
}