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

#include "foodconsumable.hh"
#include "densconsumable.hh"

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
    gameObjects_.append(gameObject);
    addRenderable(gameObject);
}

void GameWindow::initializeGame()
{
    playerSnake_ = new Snake(1.0f, 0.7f, 4.0f);
    playerSnake_->loadResources(resourceManager_);
    addGameObject(playerSnake_);
}

void GameWindow::updateGame()
{
    qint64 ns = elapsedTimer_.nsecsElapsed();
    float timeDelta = float(ns-prevNs_) * 1.0f/1000000000.0f;
    prevNs_ = ns;

    for (GameObject* object : gameObjects_)
        object->update(timeDelta);
}

void GameWindow::renderGame()
{
    // Clear previous image
    gl->glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    gl->glClearColor(0.4f, 0.8f, 1.0f, 1.0f);

    float rot = - (playerSnake_->getHeading()) / 3.1415f * 180.0f + 90.0f;

    // Calculate camera matrix, replace with the Camera class later on
    float aspect = float(width()) / float(height());

    QMatrix4x4 projectionMatrix;
    projectionMatrix.perspective(55.0f, aspect, 0.2f, 10.0f);

    QMatrix4x4 viewMatrix;
    viewMatrix.translate(QVector3D(0.0f, 0.0f, -1.0f));
    viewMatrix.rotate(68.0f, QVector3D(-1.0f, 0.0f, 0.0f));
    viewMatrix.rotate(rot, QVector3D(0.0, 0.0f, 1.0f));
    viewMatrix.translate(-playerSnake_->getHeadPosition());

    QVector3D lightDir = QVector3D(0.8f, 0.4f, 0.8f).normalized();

    for (QOpenGLShaderProgram* program : renderMap_.keys())
    {
        program->bind();
        program->setUniformValue("ambient", 0.7f);

        for (Renderable* renderable : renderMap_[program])
        {
            QMatrix4x4 modelMatrix = renderable->getTransform()->getModelMatrix();
            QMatrix4x4 mvpMatrix = projectionMatrix * viewMatrix * modelMatrix;
            QVector3D eyeLightDir = lightDir;

            program->setUniformValue("mvpMatrix", mvpMatrix);
            program->setUniformValue("modelMatrix", modelMatrix);
            program->setUniformValue("eyeLightDir", eyeLightDir);

            renderable->render(gl);
        }

        program->release();
    }

    // Empty buffers
    gl->glFlush();
}

void GameWindow::loadResources()
{
    // Create single instance for a resource manager
    resourceManager_ = new ResourceManager;

    // Load necessary resources at the beginning instead of during runtime
    resourceManager_->createProgram("snake_program",
                                    "snake_vertex.glsl",
                                    "snake_fragment.glsl");

    resourceManager_->createProgram("consumable_program",
                                    "consumable_vertex.glsl",
                                    "consumable_fragment.glsl");

    resourceManager_->loadMesh("apple_mesh.obj");
    resourceManager_->loadTexture("apple_tex_stylized.png");
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

void GameWindow::addRandomFood()
{
    DensConsumable* food = new DensConsumable();
    food->loadResources(resourceManager_);
    food->getTransform()->setPosition(
                QVector3D(rand()%1000 / 500.0f-1.0f, rand()%1000 / 500.0f-1.0f, 0.0f));

    addGameObject(food);
}

void GameWindow::keyPressEvent(QKeyEvent* event)
{
    if (event->isAutoRepeat()) return;

    int key = event->key();

    // Set key as active (pressed down)
    keyMap[key] = true;

    if (key == Qt::Key_A)
        playerSnake_->steer(1);
    else if (key == Qt::Key_D)
        playerSnake_->steer(-1);
    else if (key == Qt::Key_F11)
        toggleFullscreen();
    else if (key == Qt::Key_Space)
        playerSnake_->eat();
    else if (key == Qt::Key_V)
        addRandomFood();
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
