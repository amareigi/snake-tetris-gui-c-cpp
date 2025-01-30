#ifndef BRICKGAME_CONTROLLER_H
#define BRICKGAME_CONTROLLER_H

#include "../brick_game/brick_game_lib.h"

#ifdef __cplusplus
extern "C" {
#endif

void controllerFunc(int* key, int*** field, int*** next, int* score,
                    int* high_score, int* level, int* speed, int* pause);

#ifdef __cplusplus
}
#endif

#endif
