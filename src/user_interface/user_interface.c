#include "user_interface.h"

#define BACKGROUND_COLOR 0
#define GREEN_COLOR_PAIR_ATTR 2
#define YELLOW_COLOR_PAIR_ATTR 3

void init_ui(void) {
  initscr();			/* Start curses mode 		  */
  timeout(3000);
  noecho();
  curs_set(0);
  start_color();
  init_pair(1, COLOR_WHITE, BACKGROUND_COLOR);
  // 
  init_pair(GREEN_COLOR_PAIR_ATTR, COLOR_GREEN, BACKGROUND_COLOR);
  init_pair(YELLOW_COLOR_PAIR_ATTR, COLOR_YELLOW, BACKGROUND_COLOR);
}

void destroy_ui(void) {
  endwin();
}

void print_green_char(char c) {
  attron(COLOR_PAIR(GREEN_COLOR_PAIR_ATTR));
  printw("%c", c);
  attroff(COLOR_PAIR(GREEN_COLOR_PAIR_ATTR));
}

void print_yellow_char(char c) {
  attron(COLOR_PAIR(YELLOW_COLOR_PAIR_ATTR));
  printw("%c", c);
  attroff(COLOR_PAIR(YELLOW_COLOR_PAIR_ATTR));
}

void print_previous_guesses(void) {
  int numWordsToPrint = get_previous_guesses_len();
  int currWordToPrintLen;

  for (int idxOfWordToPrint = 0; idxOfWordToPrint < numWordsToPrint; idxOfWordToPrint++) {
    int currWordToPrintLen = get_len_of_previous_guess(idxOfWordToPrint);
    for (int idxOfCharInWord = 0; idxOfCharInWord < currWordToPrintLen; idxOfCharInWord++) {
      char charAtGuessIdx = get_previous_guess_char(idxOfWordToPrint, idxOfCharInWord);
      if (charAtGuessIdx == 'A') {
        print_green_char('A');
      } else if (charAtGuessIdx == 'S') {
        print_yellow_char('S');
      } else {
        printw("%c", charAtGuessIdx);
      }
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
