/**
  TIE-02201 Ohjelmointi 2: Perusteet, K2019
  Assignment 12.4: Matopelin paluu
    3D Snake game made with OpenGL 2.1 immediate mode.
    See 'instructions.txt' for further information.

  main_window.hh
    Defines a class implementing a UI for the game.

  @author Joona Perasto, 272725, joona.perasto@tuni.fi
*/


#ifndef PRG2_SNAKE2_MAINWINDOW_HH
#define PRG2_SNAKE2_MAINWINDOW_HH


#include <QOpenGLWindow>
#include <QOpenGLFunctions_2_1>
#include <QMatrix4x4>

#include <QDebug>
#include <QKeyEvent>
#include <QTimer>
#include <QElapsedTimer>

#include <random>

#include "renderable.hh"
#include "snake.hh"
#include "powerup.hh"


const QSize DEFAULT_SIZE(1280, 720);
const QSize MIN_SIZE(640, 480);


class MainWindow : public QOpenGLWindow {
    Q_OBJECT

public:
    MainWindow();
    ~MainWindow() override = default;

    void keyPressEvent(QKeyEvent* event) override;
    void keyReleaseEvent(QKeyEvent* event) override;
    void toggleFullscreen();

    void gameRender();
protected:
    virtual void initializeGL() override;

private slots:
    void gameUpdate();

private:
    // Timers
    QTimer timer_;
    QElapsedTimer elapsed_timer_;
    qint64 prev_ns_;

    // Gameplay
    Snake* snake_;
    QVector<PowerUp*> powerups_;

    // OpenGL rendering, matrices
    QVector3D camera_pos;
    QMatrix4x4 perspective_mat;

    QOpenGLFunctions_2_1* gl;

    float rot = 0.0f;
};


#endif  // PRG2_SNAKE2_MAINWINDOW_HH
