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

void MainWindow::addRenderable(Renderable *renderable)
{
    QOpenGLShaderProgram* program = renderable->getShaderProgram();
    renderMap_[program].append(renderable);
}

void MainWindow::initializeGame()
{
    snake_ = new Snake(3.0f, 0.7f, 4.0f);
    snake_->loadShaders(resourceManager_);
    snake_->steer(1);

    addRenderable(snake_);

    for (int i = 0; i < 4; i++)
    {
        Snake* snake = new Snake(2.5f, 0.8f, 4.0f);
        snake->setPosition(QVector3D(0, 0, 0));
        snake->loadShaders(resourceManager_);
        snake->steer(-1);
        addRenderable(snake);
        snakes.append(snake);
    }
}

void MainWindow::updateGame()
{
    qint64 ns = elapsedTimer_.nsecsElapsed();
    float timeDelta = float(ns-prevNs_) * 1.0f/1000000000.0f;
    prevNs_ = ns;

    snake_->update(timeDelta);

    for (auto snake : snakes)
    {
        if (rand() % 30 == 0)
            snake->steer(-1);
        if (rand() % 31 == 0)
            snake->steer(1);
        if (rand() % 63 == 0)
            snake->steer(0);

        snake->update(timeDelta);
    }
}

void MainWindow::renderGame()
{
    // Clear previous image
    gl->glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    gl->glClearColor(0.4f, 0.8f, 1.0f, 1.0f);

    // Render 3D Scene
    rot = - (snake_->getHeading()) / 3.1415f * 180.0f + 90.0f;
    cameraPos = QVector3D(0.0f, 0.0f, -1.0f);

    // Calculate camera matrix
    QMatrix4x4 mvpMatrix;
    float aspect = float(width()) / float(height());
    mvpMatrix.perspective(65.0f, aspect, 0.2f, 10.0f);
    mvpMatrix.translate(cameraPos);
    mvpMatrix.rotate(68.0f, QVector3D(-1.0f, 0.0f, 0.0f));
    mvpMatrix.rotate(rot, QVector3D(0.0, 0.0f, 1.0f));
    mvpMatrix.translate(-snake_->getPosition());

    for (QOpenGLShaderProgram* program : renderMap_.keys())
    {
        program->bind();
        program->setUniformValue("mvpMatrix", mvpMatrix);

        for (Renderable* renderable : renderMap_[program])
        {
            renderable->render(gl);
        }
    }

    // Empty buffers
    gl->glFlush();
}

void MainWindow::loadResources()
{
    resourceManager_ = new ResourceManager;
    resourceManager_->createProgram("snake_program",
                                   "snake_vertex.glsl",
                                   "snake_fragment.glsl");
}

void MainWindow::paintGL()
{
    handleInput();
    updateGame();
    renderGame();

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

    loadResources();
    initializeGame();
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
