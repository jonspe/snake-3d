/**
  TIE-02201 Ohjelmointi 2: Perusteet, K2019
  Assignment 12.4: Matopelin paluu
    3D Snake game made with OpenGL ES 2.0.
    See 'instructions.txt' for further information.

  game_window.cpp
    Defines a class for handling window events, game logic,
    UI rendering and 3D rendering. The base class where
    everything important happens.

  @author Joona Perasto, 272725, joona.perasto@tuni.fi
*/


#include "gamewindow.hh"
#include "level.hh"
#include "fooditem.hh"
#include "snake.hh"

GameWindow::GameWindow() {
    // Window settings
    setTitle("Snakey Boi");
    resize(DEFAULT_SIZE);
    setMinimumSize(MIN_SIZE);

    QSurfaceFormat format;
    format.setDepthBufferSize(16);
    format.setSamples(4);
    setFormat(format);

    prevNs_ = 0;
    elapsedTimer_.start();
}

void GameWindow::toggleFullscreen()
{
    if (visibility() == Visibility::FullScreen)
        setVisibility(Visibility::Windowed);
    else
        setVisibility(Visibility::FullScreen);
}


void GameWindow::initializeScene()
{
    scene_ = new Scene;
    camera_ = new Camera;
    scene_->setCamera(camera_);

    player_ = new Snake(scene_);
    scene_->setPlayer(player_);

    Level* level = new Level();

    scene_->addGameObject(player_);
    scene_->setLevel(level);
}

void GameWindow::paintGL()
{
    qint64 ns = elapsedTimer_.nsecsElapsed();
    float deltaTime = (ns-prevNs_) * 0.000000001f;
    prevNs_ = ns;

    scene_->update(deltaTime);

    // Clear previous image
    gl->glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    gl->glClearColor(0.4f, 0.8f, 1.0f, 1.0f);

    float rot = - (player_->getHeading()) / 3.1415f * 180.0f;

    QQuaternion cameraRotation =
            QQuaternion::fromEulerAngles(20.0f, 0.0f, 0.0f)
            * QQuaternion::fromEulerAngles(0.0f, rot, 0.0f);

    QVector3D cameraPosition =
            player_->getHeadPosition()
            + cameraRotation.inverted().rotatedVector( QVector3D(0.0f, 0.0f, 1.0f));

    camera_->setViewport(width(), height());
    camera_->setPosition(cameraPosition);
    camera_->setRotation(cameraRotation);

    scene_->render(gl);

    // Empty buffers
    gl->glFlush();

    // Show image and call paintGL again next frame
    update();
}

void GameWindow::initializeGL()
{
    // Create instance for handling OpenGL drawing functions
    gl = new QOpenGLFunctions;
    gl->initializeOpenGLFunctions();

    // Initialize depth test settings and antialiasing
    gl->glEnable(GL_MULTISAMPLE);
    gl->glEnable(GL_CULL_FACE);
    gl->glEnable(GL_DEPTH_TEST);
    gl->glDepthMask(GL_TRUE);
    gl->glDepthFunc(GL_LEQUAL);

    // Start game after OpenGL context is created and settings applied
    initializeScene();
}


void GameWindow::keyPressEvent(QKeyEvent* event)
{
    if (event->isAutoRepeat()) return;

    int key = event->key();

    // Set key as active (pressed down)
    keyMap[key] = true;

    if (key == Qt::Key_A)
        player_->steer(1);
    else if (key == Qt::Key_D)
        player_->steer(-1);
    else if (key == Qt::Key_F11)
        toggleFullscreen();
    else if (key == Qt::Key_V)
        scene_->addRandomFood();
}

void GameWindow::keyReleaseEvent(QKeyEvent* event)
{
    if (event->isAutoRepeat()) return;

    int key = event->key();

    // Steer control logic on key release, so the most recent input will apply
    if (key == Qt::Key_A || key == Qt::Key_D)
    {
        player_->steer(0);
        if (key == Qt::Key_A && keyMap[Qt::Key_D])
            player_->steer(-1);
        else if (key == Qt::Key_D && keyMap[Qt::Key_A])
            player_->steer(1);
    }

    // Set key as inactive (released)
    keyMap[event->key()] = false;
}
