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
#include <QOpenGLFunctions>
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


class MainWindow : public QOpenGLWindow, protected QOpenGLFunctions {
    Q_OBJECT

public:
    MainWindow();
    ~MainWindow() override = default;

    void keyPressEvent(QKeyEvent* event) override;
    void keyReleaseEvent(QKeyEvent* event) override;
    void toggleFullscreen();

protected:
    virtual void initializeGL() override;
    virtual void paintGL() override;

private slots:
    void gameUpdate();

private:
    // Timers
    QElapsedTimer elapsedTimer_;
    qint64 prevNs_;

    // Gameplay
    Snake* snake_;
    QVector<PowerUp*> powerUps_;

    // Rendering
    QVector3D cameraPos;
    QOpenGLFunctions* gl;

    float rot = 0.0f;
};


#endif  // PRG2_SNAKE2_MAINWINDOW_HH
