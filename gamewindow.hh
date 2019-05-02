/**
  TIE-02201 Ohjelmointi 2: Perusteet, K2019
  Assignment 12.4: Matopelin paluu
    3D Snake game made with OpenGL ES 2.0.
    See 'instructions.txt' for further information.

  game_window.hh
    Defines a class for handling window events, game logic,
    UI rendering and 3D rendering. The base class where
    everything important happens.

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
#include <QMap>

#include <random>

#include "resourcemanager.hh"
#include "scene.hh"


const QSize DEFAULT_SIZE(1280, 720);
const QSize MIN_SIZE(640, 480);


class GameWindow : public QOpenGLWindow {
    Q_OBJECT

public:
    GameWindow();
    ~GameWindow() override = default;

    void keyPressEvent(QKeyEvent* event) override;
    void keyReleaseEvent(QKeyEvent* event) override;
    void toggleFullscreen();

protected:
    virtual void initializeGL() override;
    virtual void paintGL() override;

private:
    void initializeScene();

    Scene* scene_;
    Snake* player_;
    Camera* camera_;

    // Input
    QMap<int, bool> keyMap;

    QOpenGLFunctions* gl;

    // Timers for update loop
    QElapsedTimer elapsedTimer_;
    qint64 prevNs_;

};


#endif  // PRG2_SNAKE2_MAINWINDOW_HH
