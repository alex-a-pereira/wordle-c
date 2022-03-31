#include "user_interface.h"

void init_ui(void) {
  initscr();			/* Start curses mode 		  */
}

void destroy_ui(void) {
  endwin();
}

void print_previous_guesses(void) {
  printw("AUDIO\n");
  printw("STERN\n");
}

void print_current_guess(void) {
  printw("RAT__\n");
}

void print_ui(void) {
  erase();
  print_previous_guesses();
  print_current_guess();
  refresh();
}
