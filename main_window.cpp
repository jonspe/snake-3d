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

    QSurfaceFormat format;
    format.setDepthBufferSize(16);
    format.setSamples(4);
    setFormat(format);

    // Game init
    snake_ = new Snake(1.0f, 0.7f, 4.0f);
    snake_->steer(1);

    prevNs_ = 0;
    elapsedTimer_.start();
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
}

void MainWindow::paintGL()
{
    handleInput();
    gameUpdate();

    // Clear previous image
    gl->glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    gl->glClearColor(0.4f, 0.8f, 1.0f, 1.0f);

    rot = -snake_->getHeading() / 3.1415f * 180.0f + 90.0f;
    cameraPos = QVector3D(0.0f, 0.0f, -1.0f);

    // Calculate camera matrix
    QMatrix4x4 mvpMatrix;
    float aspect = float(width()) / float(height());
    mvpMatrix.perspective(65.0f, aspect, 0.2f, 10.0f);
    mvpMatrix.translate(cameraPos);
    mvpMatrix.rotate(68.0f, QVector3D(-1.0f, 0.0f, 0.0f));
    mvpMatrix.rotate(rot, QVector3D(0.0, 0.0f, 1.0f));
    mvpMatrix.translate(-snake_->getPosition());

    snake_->render(gl, mvpMatrix);

    // Empty buffers
    gl->glFlush();

    // Show image and when call paintGL again next frame
    update();
}

void MainWindow::initializeGL()
{
    gl = new QOpenGLFunctions;
    gl->initializeOpenGLFunctions();

    gl->glEnable(GL_MULTISAMPLE);
    gl->glEnable(GL_CULL_FACE);
    gl->glEnable(GL_DEPTH_TEST);
    gl->glDepthMask(GL_TRUE);
    gl->glDepthFunc(GL_LESS);

    snake_->loadShaders();
}

void MainWindow::handleInput()
{
    if (isKeyDown(Qt::Key_A))
        snake_->steer(1);
    else if (isKeyDown(Qt::Key_D))
        snake_->steer(-1);
    else
        snake_->steer(0);

    if (wasKeyDown(Qt::Key_F11))
        toggleFullscreen();

    keyPressMap.clear();
}

bool MainWindow::isKeyDown(int key)
{
    if (keyHoldMap.find(key) == keyHoldMap.end())
        return false;
    return keyHoldMap[key];
}

bool MainWindow::wasKeyDown(int key)
{
    if (keyPressMap.find(key) == keyPressMap.end())
        return false;
    return keyPressMap[key];
}

void MainWindow::keyPressEvent(QKeyEvent* event)
{
    if (event->isAutoRepeat()) return;
    keyHoldMap[event->key()] = true;
    keyPressMap[event->key()] = true;
}

void MainWindow::keyReleaseEvent(QKeyEvent* event)
{
    if (event->isAutoRepeat()) return;
    keyHoldMap[event->key()] = false;
}
