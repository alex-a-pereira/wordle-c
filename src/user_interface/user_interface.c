#include "user_interface.h"

#define BACKGROUND_COLOR 0
#define GREEN_COLOR_PAIR_ATTR 2
#define YELLOW_COLOR_PAIR_ATTR 3
#define RED_COLOR_PAIR 4

void init_ui(void) {
  initscr();			/* Start curses mode 		  */
  timeout(1);
  noecho();
  curs_set(0);
  start_color();
  // normal is black background, white letters
  init_pair(1, COLOR_WHITE, 0);
  // "corect guesses" are green background, black letters
  init_pair(GREEN_COLOR_PAIR_ATTR, COLOR_BLACK, COLOR_GREEN);
  // "partially correct guesses" are yellow background, black letters
  init_pair(YELLOW_COLOR_PAIR_ATTR, COLOR_BLACK, COLOR_YELLOW);
  // "already guessed chars that are not in word" are red out
  init_pair(RED_COLOR_PAIR, COLOR_BLACK, COLOR_RED);
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

void print_red_char(char c) {
  attron(COLOR_PAIR(RED_COLOR_PAIR));
  printw("%c", c);
  attroff(COLOR_PAIR(RED_COLOR_PAIR));
}

void print_char_at_correct_color(char c) {
  CHAR_GUESS_STATUS statusOfChar = get_char_guess_status(c);

  switch (statusOfChar) {
    case CHAR_IN_WORD_CORRECT_IDX:
      print_green_char(c);
      break;
    case CHAR_IN_WORD_WRONG_IDX:
      print_yellow_char(c);
      break;
    case CHAR_NOT_IN_WORD:
      print_red_char(c);
      break;
    // NOT YET GUESSED
    default:
      printw("%c", c);
      break;
  }
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

void print_future_guess_lines(void) {
  int numGuessesAlreadyTaken = get_previous_guesses_len();
  int totalNumGuesses = get_max_num_guesses();
  // the `- 1` is because we need to subtract a line the current guess as well
  int numFutureGuessesToPrint = totalNumGuesses - numGuessesAlreadyTaken - 1;
  for (int r = 0; r < numFutureGuessesToPrint; r++) {
    // TODO: constant for word length
    printw("*****\n");
  }
}

void print_char_bank(void) {
  printw("\n");

  char* charsToPrint = "QWERTYUIOPASDFGHJKLZXCVBNM"; // qwerty :)
  for (int i = 0; i < 26; i++) {
    char c = charsToPrint[i];
    print_char_at_correct_color(c);
    // space between each letter
    printw(" ");
    // newline for new keyboard row, shift over using spaces so it looks like a real keyboard
    if (c == 'P') {
      printw("\n ");
    } else if (c == 'L') {
      printw("\n  ");
    } else if (c == 'M') {
      printw("\n");
    }
  }
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
  printw(" <-\n");
}

void print_ui(void) {
  erase();
  print_previous_guesses();
  print_current_guess();
  print_future_guess_lines();
  print_char_bank();
  print_logbox_message();
  refresh();
}
