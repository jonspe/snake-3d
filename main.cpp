/**
  TIE-02201 Ohjelmointi 2: Perusteet, K2019
  Assignment 12.4: Matopelin paluu
    3D Snake game made with OpenGL 2.1 immediate mode.
    See 'instructions.txt' for further information.

  main.cpp
    Main file.

  @author Joona Perasto, 272725, joona.perasto@tuni.fi
*/



#include "gamewindow.hh"
#include <QApplication>


int main(int argc, char** argv) {
    QApplication a(argc, argv);
    GameWindow* w = new GameWindow;
    w->show();
    return a.exec();
}
