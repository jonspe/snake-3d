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
#include <QMap>

#include <random>

#include "renderable.hh"
#include "snake.hh"
#include "consumable.hh"
#include "resourcemanager.hh"


const QSize DEFAULT_SIZE(1280, 720);
const QSize MIN_SIZE(640, 480);


class GameWindow : public QOpenGLWindow {
    Q_OBJECT

public:
    GameWindow();
    ~GameWindow() override = default;

    void addRenderable(Renderable* renderable);
    void addGameObject(GameObject* gameObject);

    void keyPressEvent(QKeyEvent* event) override;
    void keyReleaseEvent(QKeyEvent* event) override;
    void toggleFullscreen();

protected:
    virtual void initializeGL() override;
    virtual void paintGL() override;

private:
    // Datastructure for renderable objects
    // Used to sort by shader for efficient rendering, allows for low amount of shader changing
    using RenderMap = QMap<QOpenGLShaderProgram*, QVector<Renderable*>>;

    void loadResources();
    void initializeGame();
    void updateGame();
    void renderGame();

    ResourceManager* resourceManager_;

    // Objects
    Snake* playerSnake_;

    // Input
    QMap<int, bool> keyMap;

    // Rendering
    QOpenGLFunctions* gl;
    RenderMap renderMap_;

    // Timers for update loop
    QElapsedTimer elapsedTimer_;
    qint64 prevNs_;

};


#endif  // PRG2_SNAKE2_MAINWINDOW_HH
