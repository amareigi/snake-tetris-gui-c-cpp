#include "snake_lib.h"

namespace s21 {
static void StartState(Game &game);
static void SpawnState(Game &game);
static void MovingState(Game &game);
static void PauseState(Game &game);
static void ShiftingState(Game &game);
static void WinState(Game &game);
static void GameoverState(Game &game);
static void ExitState(Game &game);

Snake::Snake() { Init(); }

void Snake::Init() {
  dir_ = UP;
  size_ = 4;
  change_dir_status_ = true;
  for (int i = 0; i < size_; i++) {
    loc_[i].x = i + 10;
    loc_[i].y = 5;
    loc_[i].exist = true;
  }
  for (int i = size_; i < 200; i++) {
    loc_[i].x = 0;
    loc_[i].y = 0;
    loc_[i].exist = false;
  }
}

void Snake::Growth() { size_++; }

int Snake::get_x(int cell) { return loc_[cell].x; }

int Snake::get_y(int cell) { return loc_[cell].y; }

bool Snake::exist(int cell) {
  bool res = false;
  if (loc_[cell].exist) res = true;
  return res;
}

void Snake::anableChangeDir() { change_dir_status_ = true; }

void Snake::DirUp() {
  if (dir_ != DOWN && change_dir_status_) {
    dir_ = UP;
    change_dir_status_ = false;
  }
}

void Snake::DirDown() {
  if (dir_ != UP && change_dir_status_) {
    dir_ = DOWN;
    change_dir_status_ = false;
  }
}

void Snake::DirLeft() {
  if (dir_ != RIGHT && change_dir_status_) {
    dir_ = LEFT;
    change_dir_status_ = false;
  }
}

void Snake::DirRight() {
  if (dir_ != LEFT && change_dir_status_) {
    dir_ = RIGHT;
    change_dir_status_ = false;
  }
}

void Snake::RebuildSnake() {
  for (int i = size_ - 1; i > 0; i--) loc_[i] = loc_[i - 1];
}

void Snake::Move() {
  RebuildSnake();
  if (dir_ == UP) {
    loc_[0].x--;
  }
  if (dir_ == DOWN) {
    loc_[0].x++;
  }
  if (dir_ == RIGHT) {
    loc_[0].y++;
  }
  if (dir_ == LEFT) {
    loc_[0].y--;
  }
}

Direction Snake::get_dir() { return dir_; }

int Snake::get_size() { return size_; }

GameTimer::GameTimer() {
  timer_ = 0;
  activated_ = false;
}

void GameTimer::set() {
  timer_ = CurrentTimeMillis();
  activated_ = true;
}

bool GameTimer::IsActivated() { return activated_; }

bool GameTimer::ItsTime(long long unsigned int lvl_speed) {
  bool res = false;
  if (timer_ - CurrentTimeMillis() > lvl_speed) {
    res = true;
    activated_ = false;
    timer_ = 0;
  }
  return res;
}

unsigned long long GameTimer::CurrentTimeMillis() {
  struct timeval tv;
  gettimeofday(&tv, NULL);
  return (unsigned long long)(tv.tv_sec) * 1000 +
         (unsigned long long)(tv.tv_usec) / 1000;
}

Game::Game() {
  field_allocated = false;
  FirstInitGameIn();
  input.act = Start;
  input.is_new = false;
  state = START;
}

void Game::setState(State newState) { state = newState; }

void Game::FirstInitGameIn() {
  game_i.field = 0;
  game_i.next = 0;
  game_i.score = 0;
  game_i.high_score = LoadMaxScore();
  game_i.level = 1;
  game_i.pause = 0;
}

void Game::RestartGameIn() {
  game_i.score = 0;
  game_i.level = 1;
  game_i.pause = 0;
  ZeroToField();
}

int Game::LoadMaxScore() {
  FILE *file = NULL;
  int high_score = 4;
  file = fopen("snake_high_score.txt", "r");
  if (file) {
    fscanf(file, "%d", &high_score);
    fclose(file);
  }
  return high_score;
}

void Game::SaveMaxScore() {
  FILE *file = NULL;
  file = fopen("snake_high_score.txt", "w");
  if (file) {
    fprintf(file, "%d", game_i.high_score);
    fclose(file);
  }
}

void Game::AllocField() {
  if (!field_allocated) {
    game_i.field = (int **)malloc(20 * sizeof(int *));
    if (game_i.field != NULL) {
      for (int row = 0; row < 20; row++) {
        game_i.field[row] = (int *)malloc(10 * sizeof(int));
      }
      ZeroToField();
      field_allocated = true;
    }
  }
}

void Game::DeallocField() {
  if (game_i.field != 0) {
    for (int row = 0; row < 20; row++) {
      if (game_i.field[row] != 0) free(game_i.field[row]);
    }
    free(game_i.field);
  }
  game_i.field = NULL;
}

bool Game::IsNewInput() { return input.is_new; }

void Game::set_input(UserAction_t new_input) {
  input.act = new_input;
  input.is_new = true;
}

bool Game::CollideBorder() {
  bool res = false;
  int x = snake.get_x(0);
  int y = snake.get_y(0);
  Direction dir = snake.get_dir();
  if (dir == UP && x == 0) {
    res = true;
  }
  if (dir == DOWN && x == 19) {
    res = true;
  }
  if (dir == RIGHT && y == 9) {
    res = true;
  }
  if (dir == LEFT && y == 0) {
    res = true;
  }
  return res;
}

bool Game::CollideSelf() {
  bool res = false;
  int x = snake.get_x(0);
  int y = snake.get_y(0);
  Direction dir = snake.get_dir();
  if (dir == UP && SnakePoint(x - 1, y)) {
    res = true;
  }
  if (dir == DOWN && SnakePoint(x + 1, y)) {
    res = true;
  }
  if (dir == RIGHT && SnakePoint(x, y + 1)) {
    res = true;
  }
  if (dir == LEFT && SnakePoint(x, y - 1)) {
    res = true;
  }
  return res;
}

bool Game::CollideApple() {
  bool res = false;
  int head_x = snake.get_x(0);
  int head_y = snake.get_y(0);
  int apple_x = apple.get_x();
  int apple_y = apple.get_y();
  if (head_x == apple_x && head_y == apple_y) {
    res = true;
  }
  return res;
}

void Game::UpdateField() {
  AllocField();
  ZeroToField();
  AppleToField();
  SnakeToField();
}

bool Game::SnakePoint(int x, int y) {
  bool res = false;
  int size = snake.get_size();
  for (int i = 0; i < size; i++)
    if (snake.exist(i))
      if (x == snake.get_x(i) && y == snake.get_y(i)) res = true;
  return res;
}

void Game::PutApple() {
  int x = 0;
  int y = 0;
  do {
    x = rand() % 20;
    y = rand() % 10;
  } while (SnakePoint(x, y));
  apple.set_xy(x, y);
}

void Game::SnakeToField() {
  int size = snake.get_size();
  for (int i = 0; i < size; i++)
    if (snake.exist(i)) {
      int x = snake.get_x(i);
      int y = snake.get_y(i);
      game_i.field[x][y] = 1;
    }
}

void Game::AppleToField() {
  int x = apple.get_x();
  int y = apple.get_y();
  game_i.field[x][y] = 2;
}

void Game::ZeroToField() {
  for (int i = 0; i < 20; i++)
    for (int j = 0; j < 10; j++) game_i.field[i][j] = 0;
}

bool Game::CheckTime() {
  bool res = false;
  if (!timer.IsActivated()) timer.set();
  long long unsigned int lvl_speed = 5000 / game_i.level;
  if (timer.ItsTime(lvl_speed)) res = true;
  return res;
}

void Game::CheckHighScore() {
  if (game_i.high_score < game_i.score) game_i.high_score = game_i.score;
  SaveMaxScore();
}

void Game::CheckLvl() {
  int lvl = game_i.level;
  int score = game_i.score;
  if (lvl < 11 && (score > (lvl * 5))) game_i.level++;
}

GameInfo_t Game::Result() { return game_i; }

}  // namespace s21

s21::Game &get_game_ref() {
  static s21::Game game;
  return game;
}

void userInput(UserAction_t user_input, bool hold) {
  (void)hold;
  s21::Game &game = get_game_ref();
  if (!game.IsNewInput()) {
    game.set_input(user_input);
  }
}

GameInfo_t updateCurrentState() {
  FiniteStateMachine(get_game_ref());
  return get_game_ref().Result();
}

void FiniteStateMachine(s21::Game &game) {
  switch (game.state) {
    case s21::START:
      StartState(game);
      break;
    case s21::SPAWN:
      SpawnState(game);
      break;
    case s21::MOVING:
      MovingState(game);
      break;
    case s21::PAUSE:
      PauseState(game);
      break;
    case s21::SHIFTING:
      ShiftingState(game);
      break;
    case s21::WIN_STATE:
      WinState(game);
      break;
    case s21::GAMEOVER:
      GameoverState(game);
      break;
    case s21::EXIT_STATE:
      ExitState(game);
      break;
    default:
      break;
  }
  if (game.state != s21::EXIT_STATE) game.UpdateField();
}
namespace s21 {
static void StartState(Game &game) {
  if (game.IsNewInput()) {
    switch (game.input.act) {
      case Start:
        if (game.game_i.pause == 2 || game.game_i.pause == 4) {
          game.RestartGameIn();
        }
        game.snake.Init();
        game.game_i.score = game.snake.get_size();
        game.state = SPAWN;
        break;
      case Terminate:
        game.state = EXIT_STATE;
        break;
      default:
        break;
    }
  }
  game.input.is_new = false;
}

static void SpawnState(Game &game) {
  game.PutApple();
  game.setState(MOVING);
}

static void MovingState(Game &game) {
  if (game.IsNewInput()) {
    switch (game.input.act) {
      case Action:
        game.state = SHIFTING;
        break;
      case Up:
        game.snake.DirUp();
        break;
      case Down:
        game.snake.DirDown();
        break;
      case Right:
        game.snake.DirRight();
        break;
      case Left:
        game.snake.DirLeft();
        break;
      case Terminate:
        game.state = EXIT_STATE;
        break;
      case Pause:
        game.state = PAUSE;
        game.game_i.pause = 1;
        break;
      default:
        break;
    }
    game.input.is_new = false;
  }
  if (game.CheckTime() && game.state != PAUSE && game.state != EXIT_STATE) {
    game.state = SHIFTING;
  }
}

static void PauseState(Game &game) {
  if (game.IsNewInput()) {
    switch (game.input.act) {
      case Pause:
        game.game_i.pause = 0;
        game.state = MOVING;
        break;
      case Terminate:
        game.state = EXIT_STATE;
        break;
      default:
        break;
    }
  }
  game.input.is_new = false;
}

static void ShiftingState(Game &game) {
  if (game.CollideBorder() || game.CollideSelf()) {
    game.state = GAMEOVER;
  } else if (game.CollideApple()) {
    game.snake.Growth();
    game.game_i.score = game.snake.get_size();
    game.CheckHighScore();
    game.CheckLvl();
    if (game.snake.get_size() == 200) {
      game.state = WIN_STATE;
    } else {
      game.PutApple();
      game.snake.Move();
      game.state = MOVING;
    }
  } else {
    game.snake.Move();
    game.state = MOVING;
  }
  game.snake.anableChangeDir();
}

static void WinState(Game &game) {
  game.state = START;
  game.game_i.pause = 4;  // выйгрыш
}
static void GameoverState(Game &game) {
  game.state = START;
  game.game_i.pause = 2;  // game_over
}

static void ExitState(Game &game) {
  game.DeallocField();
  game.game_i.pause = 3;  // terminate app
}

Apple::Apple() {
  x_ = 0;
  y_ = 0;
}

void Apple::set_xy(int x, int y) {
  x_ = x;
  y_ = y;
}

int Apple::get_x() { return x_; }
}  // namespace s21
