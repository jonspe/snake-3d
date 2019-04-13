/**
  TIE-02201 Ohjelmointi 2: Perusteet, K2019
  Assignment 12.4: Matopelin paluu
    3D Snake game made with OpenGL 2.1 immediate mode.
    See 'instructions.txt' for further information.

  main_window.cpp
    Defines a class implementing a UI for the game.

  @author Joona Perasto, 272725, joona.perasto@tuni.fi
*/


#include "main_window.hh"

MainWindow::MainWindow() {

    // Window settings
    setTitle("Snakey Boi");
    resize(DEFAULT_SIZE);
    setMinimumSize(MIN_SIZE);

    // Game init
    snake_ = new Snake(3.4f, 0.7f, 4.0f);
    snake_->steer(1);

    connect(&timer_, &QTimer::timeout, this, &MainWindow::gameUpdate);
}

void MainWindow::toggleFullscreen()
{
    if (visibility() == Visibility::FullScreen)
        setVisibility(Visibility::Windowed);
    else
        setVisibility(Visibility::FullScreen);
}

void MainWindow::gameUpdate()
{
    qint64 ns = elapsedTimer_.nsecsElapsed();
    float timeDelta = float(ns-prevNs_) * 1.0f/1000000000.0f;
    prevNs_ = ns;

    snake_->update(timeDelta);
    gameRender();
}

void MainWindow::gameRender()
{
    // Clear previous image
    gl->glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    rot = -snake_->getHeading() / 3.1415f * 180.0f + 90.0f;
    cameraPos = QVector3D(0.0f, 0.0f, -2.1f);

    // Calculate camera matrix

    QMatrix4x4 mat;
    float aspect = float(width()) / float(height());
    mat.perspective(60.0f, aspect, 0.2f, 5.0f);
    mat.translate(cameraPos);
    mat.rotate(50.0f, QVector3D(-1.0f, 0.0f, 0.0f));
    mat.rotate(rot, QVector3D(0.0, 0.0f, 1.0f));
    mat.translate(-snake_->getPosition());

    snake_->render(gl, mat);

    // Empty buffers
    gl->glFlush();

    // Window requires updating to show rendered result
    update();
}

void MainWindow::initializeGL() {
    gl = new QOpenGLFunctions;
    gl->initializeOpenGLFunctions();

    gl->glEnable(GL_CULL_FACE);
    gl->glEnable(GL_DEPTH_TEST);
    gl->glDepthMask(GL_TRUE);
    gl->glDepthFunc(GL_LESS);

    snake_->initRendering(gl);

    cameraPos = QVector3D(0.0f, 0.0f, -2.1f);

    timer_.setInterval(16);
    timer_.start();

    prevNs_ = 0;
    elapsedTimer_.start();
}

void MainWindow::keyPressEvent(QKeyEvent* event)
{
    // Ignore repeated keys
    if (event->isAutoRepeat()) return;
    qDebug() << event->key();

    switch(event->key()) {
    case Qt::Key_F11:
        toggleFullscreen();
        break;
    case Qt::Key_A:
        snake_->steer(1);
        break;
    case Qt::Key_D:
        snake_->steer(-1);
        break;

    default:
        break;
    }
}

void MainWindow::keyReleaseEvent(QKeyEvent* event)
{
    // Ignore repeated keys
    if (event->isAutoRepeat()) return;

    switch(event->key()) {
    case Qt::Key_A:
        snake_->steer(0);
        break;
    case Qt::Key_D:
        snake_->steer(0);
        break;

    default:
        break;
    }
}
