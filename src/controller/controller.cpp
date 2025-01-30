#include "controller.h"

void controllerFunc(int *key, int ***field, int ***next, int *score,
                    int *high_score, int *level, int *speed, int *pause) {
  switch (*key) {
    case 0x01000012:
      userInput(Left, false);
      *key = 0;
      break;
    case 0x01000014:
      userInput(Right, false);
      *key = 0;
      break;
    case 0x01000013:
      userInput(Up, false);
      *key = 0;
      break;
    case 0x01000015:
      userInput(Down, false);
      *key = 0;
      break;
    case 0x41:
      userInput(Action, false);
      *key = 0;
      break;
    case 0x53:
      userInput(Start, false);
      *key = 0;
      break;
    case 0x50:
      userInput(Pause, false);
      *key = 0;
      break;
    case 0x54:
      userInput(Terminate, false);
      *key = 0;
      break;
    default:
      *key = 0;
      break;
  }
  GameInfo_t game_inf;
  game_inf = updateCurrentState();
  *field = game_inf.field;
  *next = game_inf.next;
  *score = game_inf.score;
  *high_score = game_inf.high_score;
  *level = game_inf.level;
  *speed = game_inf.speed;
  *pause = game_inf.pause;
}
