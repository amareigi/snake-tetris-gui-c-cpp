#include <QApplication>

#include "gui_backend.h"
#include "mainwindow.h"

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  GameGui game;
  game.show();
  return a.exec();
}
