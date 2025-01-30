#ifndef GUI_BACKEND_H
#define GUI_BACKEND_H

#include <QKeyEvent>
#include <QPainter>
#include <QWidget>

#include "../../controller/controller.h"

class GameGui : public QWidget {
  Q_OBJECT
 public:
  GameGui();

 protected:
  void timerEvent(QTimerEvent *) override;
  void keyPressEvent(QKeyEvent *e) override;
  void paintEvent(QPaintEvent *e) override;

 private:
  void doDrawField();
  void doDrawBorder();
  void doDrawStats();
  void doDrawNext();
  void doDrawPause();
  void doDrawGameOver();
  void doExitGame();
  void doDrawWin();

  int key;
  static const int DOT_WIDTH = 20;
  static const int DOT_HEIGHT = 20;
  static const int FIELD_WIDTH = 10;
  static const int FIELD_HEIGHT = 20;
  int **field_;
  int **next_;
  int score_;
  int high_score_;
  int level_;
  int speed_;
  int pause_;
  int timerId;
};

#endif  // GUI_BACKEND_H
