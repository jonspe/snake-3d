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


#include <QTime>
#include <cmath>

#include "gamewindow.hh"
#include "level.hh"
#include "fooditem.hh"
#include "snake.hh"

GameWindow::GameWindow():
    scene_(nullptr), player_(nullptr), camera_(nullptr),
    currentState_(GameState::START), startupRotation_(0.0f), prevNs_(0)
{

    // Window settings
    setTitle("Snakey Boi");
    resize(DEFAULT_SIZE);
    setMinimumSize(MIN_SIZE);

    // Enable depth buffer in window
    QSurfaceFormat format;
    format.setDepthBufferSize(16);
    format.setSamples(4);
    setFormat(format);
}

GameWindow::~GameWindow()
{
    delete player_;
    delete camera_;
    delete scene_;
    delete level_;
    delete gl;
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
    level_ = new Level;

    scene_->setCamera(camera_);
    scene_->setLevel(level_);

    QQuaternion cameraRotation = QQuaternion::fromEulerAngles(10.0f, 0.0f, 0.0f);
    QVector3D cameraPosition = cameraRotation.inverted().rotatedVector(QVector3D(0.0f, 0.0f, 6.5f));

    camera_->setFieldOfView(60.0f);
    camera_->setPosition(cameraPosition);
    camera_->setRotation(cameraRotation);

    resetScene();
}

void GameWindow::resetScene()
{
    scene_->clearGameObjects();

    delete player_;
    player_ = new Snake(scene_);
    scene_->addGameObject(player_);

    // Start the game with 20 initial food
    for (int i = 0; i < 20; i++)
        scene_->addRandomFood();
}

void GameWindow::startGame()
{
    savedTime_ = elapsedTimer_.nsecsElapsed();
    pausedTime_ = savedTime_;

    currentState_ = GameState::PLAYING;
}

void GameWindow::pauseGame()
{
    pausedTime_ = elapsedTimer_.nsecsElapsed();
    currentState_ = GameState::PAUSED;
}

void GameWindow::resumeGame()
{
    // Take paused time into account when calculating game time
    savedTime_ += elapsedTimer_.nsecsElapsed() - pausedTime_;
    currentState_ = GameState::PLAYING;
}


void GameWindow::updateCamera(float deltaTime)
{
    camera_->setViewport(width(), height());

    if (currentState_ == GameState::START)
    {
        // Rotate the camera slowly around the center of the scene

        startupRotation_ += 15.0f * deltaTime;

        QQuaternion cameraRotation =
                QQuaternion::fromEulerAngles(10.0f, 0.0f, 0.0f)
                * QQuaternion::fromEulerAngles(0.0f, startupRotation_, 0.0f);

        QVector3D cameraPosition = cameraRotation.inverted().rotatedVector(QVector3D(0.0f, 0.0f, 6.5f));

        camera_->setFieldOfView(60.0f);
        camera_->setPositionTarget(cameraPosition);
        camera_->setRotationTarget(cameraRotation);
    }
    else
    {
        // Rotate camera towards player's velocity
        float rot = - (player_->getHeading()) / 3.1415f * 180.0f;

        QQuaternion cameraRotation =
                QQuaternion::fromEulerAngles(20.0f, 0.0f, 0.0f)
                * QQuaternion::fromEulerAngles(0.0f, rot, 0.0f);

        QVector3D cameraPosition =
                player_->getHeadPosition()
                + cameraRotation.inverted().rotatedVector( QVector3D(0.0f, 0.0f, 1.0f));

        // Speed effect
        if (player_ != nullptr)
        {
            float speed = player_->getProperties()->getMoveSpeed();
            camera_->setFieldOfViewTarget(fmin(80.0f, 45.0f + speed * 8.0f));
        }

        camera_->setViewport(width(), height());
        camera_->setPositionTarget(cameraPosition);
        camera_->setRotationTarget(cameraRotation);
    }

    camera_->update(deltaTime);
}

void GameWindow::updateGameState()
{
    if (player_ == nullptr)
        return;

    if (player_->isDead() && currentState_ == GameState::PLAYING)
    {
        int score = int(player_->getTailLength()*10);
        int msecs = static_cast<int>((elapsedTimer_.nsecsElapsed() - savedTime_) / 1000000);

        QTime time(0, 0, 0, 0);
        time = time.addMSecs(msecs);

        // Really cheap way to tell the results, but problems with rendering text so whatever I guess
        qInfo() << "Oh no! You died!";
        qInfo() << "Final score: " << QString::number(score);
        qInfo() << "Time: " << time.toString("mm:ss.zzz");

        currentState_ = GameState::DEAD;
        savedTime_ = elapsedTimer_.nsecsElapsed();
    }
    else if (!player_->isDead())
    {
        if (currentState_ != GameState::PAUSED && currentState_ != GameState::START)
        {
            currentState_ = GameState::PLAYING;
            camera_->setInterpolationFactor(1.0f);
        }
    }

    // 2 seconds after dying go back to start
    if (currentState_ == GameState::DEAD && elapsedTimer_.nsecsElapsed() - savedTime_ > 3000000000)
    {
        camera_->setInterpolationFactor(0.1f);
        resetScene();
        currentState_ = GameState::START;
    }
}

void GameWindow::renderScene()
{
    // Initialize depth test settings and antialiasing
    gl->glEnable(GL_MULTISAMPLE);
    gl->glEnable(GL_CULL_FACE);
    gl->glEnable(GL_DEPTH_TEST);
    gl->glDepthMask(GL_TRUE);
    gl->glDepthFunc(GL_LEQUAL);

    // Clear previous image
    gl->glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    gl->glClearColor(0.4f, 0.8f, 1.0f, 1.0f);

    scene_->render(gl);

    // Empty buffers
    gl->glFlush();

    gl->glDisable(GL_DEPTH_TEST);
    gl->glDisable(GL_CULL_FACE);
}

void GameWindow::paintGL()
{
    qint64 ns = elapsedTimer_.nsecsElapsed();
    float deltaTime = (ns-prevNs_) * 0.000000001f;
    deltaTime = fmin(0.04f, deltaTime); // prevent big hiccups
    prevNs_ = ns;

    if (currentState_ != GameState::PAUSED && currentState_ != GameState::START)
        scene_->update(deltaTime);

    updateGameState();
    updateCamera(deltaTime);

    renderScene();

    // Show image and call paintGL again next frame
    update();
}

void GameWindow::initializeGL()
{
    // Set OpenGL context to current window
    makeCurrent();

    // Get functions from context to handle OpenGL drawing functions
    gl = QOpenGLContext::currentContext()->functions();
    gl->initializeOpenGLFunctions();

    // Enable antialiasing, backface culling and depth testing
    gl->glEnable(GL_MULTISAMPLE);
    gl->glEnable(GL_CULL_FACE);
    gl->glEnable(GL_DEPTH_TEST);
    gl->glDepthMask(GL_TRUE);
    gl->glDepthFunc(GL_LEQUAL);

    elapsedTimer_.start();

    // Start game after OpenGL context is created and settings applied
    initializeScene();
}


void GameWindow::keyPressEvent(QKeyEvent* event)
{
    if (event->isAutoRepeat()) return;

    int key = event->key();

    // Set key as active (pressed down)
    keyMap_[key] = true;

    if (key == Qt::Key_A && player_ != nullptr)
        player_->steer(1);
    else if (key == Qt::Key_D && player_ != nullptr)
        player_->steer(-1);
    else if (key == Qt::Key_F11)
        toggleFullscreen();
    else if (key == Qt::Key_Space && currentState_ == GameState::START)
        startGame();
    else if (key == Qt::Key_Space && currentState_ == GameState::PAUSED)
        resumeGame();
    else if (key == Qt::Key_Space && currentState_ == GameState::PLAYING)
        pauseGame();
}

void GameWindow::keyReleaseEvent(QKeyEvent* event)
{
    if (event->isAutoRepeat()) return;

    int key = event->key();

    // Steer control logic on key release, so the most recent input will apply
    if (player_ != nullptr && (key == Qt::Key_A || key == Qt::Key_D))
    {
        player_->steer(0);
        if (key == Qt::Key_A && keyMap_[Qt::Key_D])
            player_->steer(-1);
        else if (key == Qt::Key_D && keyMap_[Qt::Key_A])
            player_->steer(1);
    }

    // Set key as inactive (released)
    keyMap_[event->key()] = false;
}
