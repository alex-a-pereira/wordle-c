#include "user_interface.h"

#define BACKGROUND_COLOR 0
#define GREEN_COLOR_PAIR_ATTR 2
#define YELLOW_COLOR_PAIR_ATTR 3

void init_ui(void) {
  initscr();			/* Start curses mode 		  */
  timeout(1);
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

  for (int idxOfWordToPrint = 0; idxOfWordToPrint < numWordsToPrint; idxOfWordToPrint++) {
    int currWordToPrintLen = get_len_of_previous_guess(idxOfWordToPrint);
    for (int idxOfCharInWord = 0; idxOfCharInWord < currWordToPrintLen; idxOfCharInWord++) {
      char charAtGuessIdx = get_previous_guess_char(idxOfWordToPrint, idxOfCharInWord);

      // TODO: replace int with boolean!

      // print green if the char was TOTALLY correct? (i.e. was in word at the correct index)
      int charInPreviousGuessAtCorrectIdx = previous_guess_char_was_at_correct_idx(idxOfWordToPrint, idxOfCharInWord);
      if (charInPreviousGuessAtCorrectIdx) {
        print_green_char(charAtGuessIdx);
        continue;
      }

      // print yellow if the char was PARTIALLY correct? (i.e. was in word but not at the correct index)
      int charInPreviousGuessWasInWord = previous_guess_char_was_in_word(idxOfWordToPrint, idxOfCharInWord);
      if (charInPreviousGuessWasInWord) {
        print_yellow_char(charAtGuessIdx);
        continue;
      }

      // otherwise just print the char
      printw("%c", charAtGuessIdx);
    }
    // print a newline after the entire word has been printed
    printw("\n");
  }
  // no need to print a newline after ALL words have been printed!
}

void print_logbox_message(void) {
  printw("\n");
  printw("-------------------------------------\n");

  char* logBoxMessage;

  if (get_is_game_over()) {
    if (get_is_game_victory()) {
      logBoxMessage = "VICTORY!";
    } else {
      logBoxMessage = "FAILURE!";
    }
  } else {
    logBoxMessage = get_log_box_message();
  }

  printw("%s", logBoxMessage);
  printw("\n-------------------------------------\n");
}

void ui_get_input (void) {
  char c = getch();

  if (c != ERR) {
    game_state_handle_key_press(c);
  }
}

void print_current_guess(void) {
  if (get_is_game_over()) {
    return;
  }

  // if game isn't over, display current guess (or `_` chars if not yet complete)
  for (int i = 0; i < 5; i++) {
    char guessChar = get_current_guess_char(i);
    char charToPrint = guessChar != '\0' ? guessChar : '_';
    printw("%c", charToPrint);
  }
}

void print_ui(void) {
  erase();
  print_previous_guesses();
  print_current_guess();
  print_logbox_message();
  refresh();
}
