#include "gui_backend.h"

#include <QDebug>
GameGui::GameGui() {
  resize(DOT_WIDTH * FIELD_WIDTH * 2, DOT_HEIGHT * FIELD_HEIGHT);
  setWindowTitle("brick_game");
  timerId = startTimer(100);
  field_ = 0;
  next_ = 0;
  score_ = 0;
  high_score_ = 0;
  level_ = 1;
  speed_ = 0;
  pause_ = 0;
  key = 0;
}

void GameGui::timerEvent(QTimerEvent *) {
  if (pause_ != 3) {
    controllerFunc(&key, &field_, &next_, &score_, &high_score_, &level_,
                   &speed_, &pause_);
    this->repaint();
  } else {
    doExitGame();
  }
}

void GameGui::keyPressEvent(QKeyEvent *event) { key = event->key(); }

void GameGui::paintEvent(QPaintEvent *e) {
  Q_UNUSED(e);
  doDrawBorder();
  doDrawStats();
  if (next_ != 0) doDrawNext();
  if (pause_ != 3 && field_ != 0) doDrawField();
  if (pause_ == 2) doDrawGameOver();
  if (pause_ == 1) doDrawPause();
  if (pause_ == 4) doDrawWin();
}

void GameGui::doDrawField() {
  QPainter qp(this);
  for (int i = 0; i < 10; i++)
    for (int j = 0; j < 20; j++) {
      if (field_[j][i] == 1) {
        qp.setBrush(Qt::green);
        qp.drawEllipse(i * DOT_WIDTH, j * DOT_HEIGHT, DOT_WIDTH, DOT_HEIGHT);
      }
      if (field_[j][i] == 2) {
        qp.setBrush(Qt::red);
        qp.drawEllipse(i * DOT_WIDTH, j * DOT_HEIGHT, DOT_WIDTH, DOT_HEIGHT);
      }
    }
}

void GameGui::doDrawBorder() {
  QPainter qp(this);
  qp.setRenderHint(QPainter::Antialiasing, true);
  qp.drawLine(QPointF(0, 0), QPointF(DOT_WIDTH * FIELD_WIDTH, 0));
  qp.drawLine(QPointF(0, 0), QPointF(0, DOT_HEIGHT * FIELD_HEIGHT));
  qp.drawLine(QPointF(DOT_WIDTH * FIELD_WIDTH, 0),
              QPointF(DOT_WIDTH * FIELD_WIDTH, DOT_HEIGHT * FIELD_HEIGHT));
  qp.drawLine(QPointF(0, DOT_HEIGHT * FIELD_HEIGHT),
              QPointF(DOT_WIDTH * FIELD_WIDTH, DOT_HEIGHT * FIELD_HEIGHT));
}

void GameGui::doDrawStats() {
  QPainter qp(this);
  QString score = QString::number(score_);
  qp.drawText(QPoint(DOT_WIDTH * FIELD_WIDTH + 20, 30), "Score");
  qp.drawText(QPoint(DOT_WIDTH * FIELD_WIDTH + 20, 50), score);

  QString high_score = QString::number(high_score_);
  qp.drawText(QPoint(DOT_WIDTH * FIELD_WIDTH + 20, 70), "High Score");
  qp.drawText(QPoint(DOT_WIDTH * FIELD_WIDTH + 20, 90), high_score);

  QString level = QString::number(level_);
  qp.drawText(QPoint(DOT_WIDTH * FIELD_WIDTH + 20, 110), "Level");
  qp.drawText(QPoint(DOT_WIDTH * FIELD_WIDTH + 20, 130), level);

  QString speed = QString::number(speed_);
  qp.drawText(QPoint(DOT_WIDTH * FIELD_WIDTH + 20, 150), "Speed");
  qp.drawText(QPoint(DOT_WIDTH * FIELD_WIDTH + 20, 170), speed);

  qp.drawText(QPoint(DOT_WIDTH * FIELD_WIDTH + 20, 300), "s - start");
  qp.drawText(QPoint(DOT_WIDTH * FIELD_WIDTH + 20, 320), "t - exit(terminate)");
  qp.drawText(QPoint(DOT_WIDTH * FIELD_WIDTH + 20, 340), "a - action");
  qp.drawText(QPoint(DOT_WIDTH * FIELD_WIDTH + 20, 360), "p - pause, unpause");
}

void GameGui::doDrawNext() {
  QPainter qp(this);
  qp.drawText(QPoint(DOT_WIDTH * FIELD_WIDTH + 20, 190), "Next");
  for (int i = 0; i < 4; i++)
    for (int j = 0; j < 4; j++)
      if (next_[j][i] == 1) {
        qp.setBrush(Qt::green);
        qp.drawEllipse(i * DOT_WIDTH + DOT_WIDTH * FIELD_WIDTH,
                       j * DOT_HEIGHT + 210, DOT_WIDTH, DOT_HEIGHT);
      }
}

void GameGui::doDrawPause() {
  QPainter qp(this);
  qp.drawText(
      QPoint((DOT_WIDTH * FIELD_WIDTH) / 3, (DOT_HEIGHT * FIELD_HEIGHT) / 2),
      "Pause");
  qp.drawText(
      QPoint((DOT_WIDTH * FIELD_WIDTH) / 5, (DOT_HEIGHT * FIELD_HEIGHT) / 3),
      "Press 'p' to unpause");
}

void GameGui::doDrawGameOver() {
  QPainter qp(this);
  qp.drawText(
      QPoint((DOT_WIDTH * FIELD_WIDTH) / 3, (DOT_HEIGHT * FIELD_HEIGHT) / 2),
      "GameOver");
  qp.drawText(
      QPoint((DOT_WIDTH * FIELD_WIDTH) / 4, (DOT_HEIGHT * FIELD_HEIGHT) / 3),
      "Press 's' to restart");
}

void GameGui::doExitGame() { this->close(); }

void GameGui::doDrawWin() {
  QPainter qp(this);
  qp.drawText(
      QPoint((DOT_WIDTH * FIELD_WIDTH) / 3, (DOT_HEIGHT * FIELD_HEIGHT) / 2),
      "!!!Winner!!!");
  qp.drawText(
      QPoint((DOT_WIDTH * FIELD_WIDTH) / 4, (DOT_HEIGHT * FIELD_HEIGHT) / 3),
      "Press 's' to restart");
}
