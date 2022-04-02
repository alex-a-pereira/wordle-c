#include "user_interface.h"

void init_ui(void) {
  initscr();			/* Start curses mode 		  */
  timeout(3000);
  noecho();
  curs_set(0);
}

void destroy_ui(void) {
  endwin();
}

void print_previous_guesses(void) {
  int numWordsToPrint = get_previous_guesses_len();
  int currWordToPrintLen;

  for (int idxOfWordToPrint = 0; idxOfWordToPrint < numWordsToPrint; idxOfWordToPrint++) {
    int currWordToPrintLen = get_len_of_previous_guess(idxOfWordToPrint);
    for (int idxOfCharInWord = 0; idxOfCharInWord < currWordToPrintLen; idxOfCharInWord++) {
      char charAtGuessIdx = get_previous_guess_char(idxOfWordToPrint, idxOfCharInWord);
      printw("%c", charAtGuessIdx);
    }
    printw("\n");
  }
}

void ui_get_input (void) {
  char c = getch();
  if (c) {
    game_state_handle_key_press(c);
  }
}

void print_current_guess(void) {
  for (int i = 0; i < 5; i++) {
    char guessChar = get_current_guess_char(i);
    char charToPrint = guessChar != '\0' ? guessChar : '_';
    printw("%c", charToPrint);
  }
  printw("\n");
}

void print_ui(void) {
  erase();
  print_previous_guesses();
  print_current_guess();
  refresh();
}
