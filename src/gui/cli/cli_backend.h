#ifndef BRICK_GAME_CLI_H_
#define BRICK_GAME_CLI_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <curses.h>

#include "../../brick_game/brick_game_lib.h"

void enable_ncurses();
void disable_ncurses();
void frontend_general_func(GameInfo_t game_inf);

#ifdef __cplusplus
}
#endif
#endif
