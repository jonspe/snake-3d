/**
  TIE-02201 Ohjelmointi 2: Perusteet, K2019
  Assignment 12.4: Matopelin paluu
    3D Snake game made with OpenGL 2.1 immediate mode.
    See 'instructions.txt' for further information.

  main_window.cpp
    Defines a class implementing a UI for the game.

  @author Joona Perasto, 272725, joona.perasto@tuni.fi
*/


#include "gamewindow.hh"

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

void GameWindow::addRenderable(Renderable *renderable)
{
    QOpenGLShaderProgram* program = renderable->getShaderProgram();
    renderMap_[program].append(renderable);
}

void GameWindow::addGameObject(GameObject *gameObject)
{
    // TODO: add to data structure for updating all gameobjects
    // ________

    // Add to data structure for rendering objects
    addRenderable(gameObject);
}

void GameWindow::initializeGame()
{
    playerSnake_ = new Snake(1.0f, 0.7f, 4.0f);
    playerSnake_->loadResources(resourceManager_);
    playerSnake_->setDirection(QVector3D(0, 1, 0));

    addRenderable(playerSnake_);
}

void GameWindow::updateGame()
{
    qint64 ns = elapsedTimer_.nsecsElapsed();
    float timeDelta = float(ns-prevNs_) * 1.0f/1000000000.0f;
    prevNs_ = ns;

    // TODO: Update all gameobjects instead of just playerSnake
    playerSnake_->update(timeDelta);
}

void GameWindow::renderGame()
{
    // Clear previous image
    gl->glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    gl->glClearColor(0.4f, 0.8f, 1.0f, 1.0f);

    // Render 3D Scene
    float rot = - (playerSnake_->getHeading()) / 3.1415f * 180.0f + 90.0f;
    QVector3D cameraPos(0.0f, 0.0f, -1.0f);

    // Calculate camera matrix
    QMatrix4x4 mvpMatrix;
    float aspect = float(width()) / float(height());
    mvpMatrix.perspective(65.0f, aspect, 0.2f, 10.0f);
    mvpMatrix.translate(cameraPos);
    mvpMatrix.rotate(68.0f, QVector3D(-1.0f, 0.0f, 0.0f));
    mvpMatrix.rotate(rot, QVector3D(0.0, 0.0f, 1.0f));
    mvpMatrix.translate(-playerSnake_->getPosition());

    for (QOpenGLShaderProgram* program : renderMap_.keys())
    {
        program->bind();
        program->setUniformValue("mvpMatrix", mvpMatrix);

        for (Renderable* renderable : renderMap_[program])
            renderable->render(gl);
    }

    // Empty buffers
    gl->glFlush();
}

void GameWindow::loadResources()
{
    // Create single instance for a resource manager
    resourceManager_ = new ResourceManager;

    // Create a shader program for snake before it is made
    resourceManager_->createProgram("snake_program",
                                    "snake_vertex.glsl",
                                    "snake_fragment.glsl");

    resourceManager_->createProgram("basicShader_program",
                                    "basicShader_vertex.glsl",
                                    "basicShader_fragment.glsl");

    // TODO: Load additional shaders and textures here
}

void GameWindow::paintGL()
{
    updateGame();
    renderGame();

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

    // Load textures and shaders etc
    loadResources();

    // Start game after OpenGL context is created and settings applied
    initializeGame();
}

void GameWindow::keyPressEvent(QKeyEvent* event)
{
    if (event->isAutoRepeat()) return;

    // Set key as active (pressed down)
    keyMap[event->key()] = true;

    if (event->key() == Qt::Key_A)
        playerSnake_->steer(1);
    else if (event->key() == Qt::Key_D)
        playerSnake_->steer(-1);
    else if (event->key() == Qt::Key_F11)
        toggleFullscreen();
    else if (event->key() == Qt::Key_Space)
        playerSnake_->eat();

}

void GameWindow::keyReleaseEvent(QKeyEvent* event)
{
    if (event->isAutoRepeat()) return;

    int key = event->key();

    // Steer control logic on key release, so the most recent input will apply
    if (key == Qt::Key_A || key == Qt::Key_D)
    {
        playerSnake_->steer(0);
        if (key == Qt::Key_A && keyMap[Qt::Key_D])
            playerSnake_->steer(-1);
        else if (key == Qt::Key_D && keyMap[Qt::Key_A])
            playerSnake_->steer(1);
    }

    // Set key as inactive (released)
    keyMap[event->key()] = false;
}
