#ifndef CPP_SNAKE_LIB_H_
#define CPP_SNAKE_LIB_H_

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

#include "../brick_game_lib.h"

namespace s21 {
typedef struct {
  UserAction_t act;
  bool is_new;
} Action_t;

typedef enum {
  START = 0,
  SPAWN,
  MOVING,
  SHIFTING,
  GAMEOVER,
  PAUSE,
  EXIT_STATE,
  WIN_STATE
} State;

class Apple {
  int x_;
  int y_;

 public:
  Apple();
  void set_xy(int x, int y);
  int get_x();
  int get_y() { return y_; }
};

typedef struct {
  int x, y;
  bool exist;
} Location;

typedef enum { UP, DOWN, LEFT, RIGHT } Direction;

class Snake {
  Location loc_[200];
  Direction dir_;
  int size_;
  bool change_dir_status_;

 public:
  Snake();
  void Init();
  void Growth();
  int get_x(int cell);
  int get_y(int cell);
  bool exist(int cell);
  void anableChangeDir();
  void DirUp();
  void DirDown();
  void DirLeft();
  void DirRight();
  void RebuildSnake();
  void Move();
  Direction get_dir();
  int get_size();
};

class GameTimer {
  unsigned long long timer_;
  bool activated_;

 public:
  GameTimer();
  void set();
  bool IsActivated();
  bool ItsTime(long long unsigned int lvl_speed);

 private:
  unsigned long long CurrentTimeMillis();
};

class Game {
 public:
  GameInfo_t game_i;
  bool field_allocated;
  Action_t input;
  State state;
  Snake snake;
  Apple apple;
  GameTimer timer;
  Game();
  void setState(State newState);
  void FirstInitGameIn();

  void RestartGameIn();

  int LoadMaxScore();

  void SaveMaxScore();

  void AllocField();

  void DeallocField();

  bool IsNewInput();

  void set_input(UserAction_t new_input);

  bool CollideBorder();
  bool CollideSelf();
  bool CollideApple();
  void UpdateField();
  bool SnakePoint(int x, int y);
  void PutApple();

  void SnakeToField();

  void AppleToField();

  void ZeroToField();
  bool CheckTime();
  void CheckHighScore();
  void CheckLvl();

  GameInfo_t Result();
};
}  // namespace s21
void FiniteStateMachine(s21::Game& game);
s21::Game& get_game_ref();
#endif
