#include <gtest/gtest.h>

#include "../brick_game/brick_game_lib.h"
#include "../brick_game/snake/snake_lib.h"
#include "../controller/controller.h"

TEST(snake_tests, initialization) {
  s21::Game game;
  game.set_input(Start);
  FiniteStateMachine(game);
  EXPECT_EQ(game.snake.get_size(), 4);
  game.DeallocField();
}

TEST(snake_tests, movingLeft) {
  s21::Game game;
  game.set_input(Start);
  game.setState(s21::START);
  FiniteStateMachine(game);  // start state
  FiniteStateMachine(game);  // spawn state
  game.set_input(Left);
  FiniteStateMachine(game);  // moving state

  EXPECT_EQ(game.snake.get_dir(), s21::LEFT);
  game.DeallocField();
}

TEST(snake_tests, movingDown) {
  s21::Game game;
  game.set_input(Start);
  game.setState(s21::START);
  FiniteStateMachine(game);  // start state
  FiniteStateMachine(game);  // spawn state
  game.set_input(Left);
  FiniteStateMachine(game);  // moving state
  game.setState(s21::SHIFTING);
  FiniteStateMachine(game);  // shifting state
  game.set_input(Down);
  FiniteStateMachine(game);  // moving state

  EXPECT_EQ(game.snake.get_dir(), s21::DOWN);
  game.DeallocField();
}

TEST(snake_tests, movingRight) {
  s21::Game game;
  game.set_input(Start);
  game.setState(s21::START);
  FiniteStateMachine(game);  // start state
  FiniteStateMachine(game);  // spawn state
  game.set_input(Right);
  FiniteStateMachine(game);  // moving state

  EXPECT_EQ(game.snake.get_dir(), s21::RIGHT);
  game.DeallocField();
}

TEST(snake_tests, movingUp) {
  s21::Game game;
  game.set_input(Start);
  game.setState(s21::START);
  FiniteStateMachine(game);  // start state
  FiniteStateMachine(game);  // spawn state
  game.set_input(Up);
  FiniteStateMachine(game);  // moving state

  EXPECT_EQ(game.snake.get_dir(), s21::UP);
  game.DeallocField();
}
TEST(snake_tests, timerTest) {
  s21::Game game;
  game.set_input(Start);
  game.setState(s21::START);
  FiniteStateMachine(game);  // start state
  FiniteStateMachine(game);  // spawn state
  int i = 0;
  while (i < 10000) {
    FiniteStateMachine(game);  // moving state
    i++;
  }
  game.DeallocField();
}
TEST(snake_tests, gameRestart) {
  s21::Game game;
  game.set_input(Start);
  game.setState(s21::START);
  FiniteStateMachine(game);  // start state
  FiniteStateMachine(game);  // spawn state
  FiniteStateMachine(game);  // moving state
  game.setState(s21::GAMEOVER);
  FiniteStateMachine(game);  // moving state
  EXPECT_EQ(game.game_i.pause, 2);
  game.set_input(Start);
  FiniteStateMachine(game);  // start state
  game.DeallocField();
}
TEST(snake_tests, testPause) {
  s21::Game game = get_game_ref();
  game.set_input(Start);
  game.setState(s21::START);
  FiniteStateMachine(game);  // start state
  FiniteStateMachine(game);  // spawn state
  userInput(Pause, false);
  game.set_input(Pause);
  FiniteStateMachine(game);  // moving state
  EXPECT_EQ(game.game_i.pause, 1);
  game.set_input(Pause);
  FiniteStateMachine(game);  // moving state
  game.DeallocField();
}
TEST(snake_tests, testWin) {
  s21::Game game = get_game_ref();
  game.set_input(Start);
  game.setState(s21::START);
  FiniteStateMachine(game);  // start state
  FiniteStateMachine(game);  // spawn state
  FiniteStateMachine(game);  // moving state
  game.setState(s21::WIN_STATE);
  FiniteStateMachine(game);  // moving state
  EXPECT_EQ(game.game_i.pause, 4);
  FiniteStateMachine(game);  // moving state
  game.DeallocField();
}
TEST(snake_tests, testTerminate) {
  s21::Game game;
  game.set_input(Terminate);
  game.setState(s21::START);
  FiniteStateMachine(game);  // start state
  EXPECT_EQ(game.state, s21::EXIT_STATE);
  FiniteStateMachine(game);  // exit state
}

int main(int argc, char** argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
