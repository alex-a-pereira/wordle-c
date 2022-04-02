#ifndef USER_INTERFACE_H
#define USER_INTERFACE_H

#include <ncurses.h>
#include "../game_state/game_state.h"

void init_ui(void);
void destroy_ui(void);

void print_ui(void);

void ui_get_input(void);

#endif
