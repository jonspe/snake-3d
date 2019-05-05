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


#ifndef GAMEWINDOW_HH
#define GAMEWINDOW_HH


#include <QOpenGLWindow>
#include <QOpenGLFunctions>
#include <QPainter>
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


/*!
 * \brief Class representing the game window. Handles input events,
 * game logic, 3D rendering. The base class where everything important happens.
 */
class GameWindow : public QOpenGLWindow {
    Q_OBJECT

public:
    /*!
     * \brief Creates the game window and enables depth buffer.
     */
    GameWindow();
    ~GameWindow() override;

    /*!
     * \brief Listens to key press events.
     * \param event
     */
    void keyPressEvent(QKeyEvent* event) override;

    /*!
     * \brief Listens to key release events.
     * \param event
     */
    void keyReleaseEvent(QKeyEvent* event) override;

    /*!
     * \brief Toggles between fullscreen and windowed mode.
     */
    void toggleFullscreen();

protected:
    /*!
     * \brief Loads OpenGL resources
     */
    virtual void initializeGL() override;

    /*!
     * \brief Updates and renders every frame
     */
    virtual void paintGL() override;

private:
    /*!
     * \brief Initializes the scene by creating a new instance of Scene, adding
     * a camera and also adds snake and fooditems.
     */
    void initializeScene();

    /*!
     * \brief Resets game by clearing all gameobjects and inserting
     * a new snake and fooditems.
     */
    void resetScene();

    /*!
     * \brief Starts the game. Should be used in conjunction with resetScene().
     */
    void startGame();

    /*!
     * \brief Pauses the game.
     */
    void pauseGame();

    /*!
     * \brief Resumes the game.
     */
    void resumeGame();

    /*!
     * \brief Handles camera positioning and rotation.
     * \param deltaTime
     */
    void updateCamera(float deltaTime);

    /*!
     * \brief Handles game state logic.
     */
    void updateGameState();

    /*!
     * \brief Renders the scene with OpenGL ES 2.0.
     */
    void renderScene();

    Scene* scene_;
    Snake* player_;
    Camera* camera_;
    Level* level_;

    /*!
     * \brief Enum describing the state of the game.
     */
    enum GameState {
        START,
        PLAYING,
        DEAD,
        PAUSED
    };

    GameState currentState_;

    /*!
     * \brief Datastructure for checking keys currently held down.
     */
    QMap<int, bool> keyMap_;

    /*!
     * \brief Contains all OpenGL ES 2.0 drawing functions.
     */
    QOpenGLFunctions* gl;

    /*!
     * \brief The angle at which the camera is when GameState is START.
     */
    float startupRotation_;

    /*!
     * \brief Timer used for calculating deltaTime and game time.
     */
    QElapsedTimer elapsedTimer_;
    qint64 savedTime_;
    qint64 pausedTime_;
    qint64 prevNs_;

};


#endif  // GAMEWINDOW_HH
