/**
  TIE-02201 Ohjelmointi 2: Perusteet, K2019
  Assignment 12.4: Matopelin paluu
    3D Snake game made with OpenGL 2.1 immediate mode.
    See 'instructions.txt' for further information.

  snake.hh
    Defines a class for the snake which the user controls.

  @author Joona Perasto, 272725, joona.perasto@tuni.fi
*/


#ifndef SNAKE_HH
#define SNAKE_HH

#include <QVector>
#include <QVector3D>
#include <QOpenGLFunctions>

#include "renderable.hh"
#include "powerup.hh"
#include "gameobject.hh"

const int SNAKE_DEFINITION = 16;

const float SNAKE_HEAD_LENGTH = 0.06f;
const float SNAKE_TAIL_END_LENGTH = 0.06f;
const float SNAKE_SEGMENT_DIST = 0.03f;

const float SNAKE_MIN_LENGTH = SNAKE_HEAD_LENGTH + SNAKE_TAIL_END_LENGTH;


class Snake : public GameObject
{
public:
    Snake(float length = 0.6f,
          float moveSpeed = 0.7f,
          float steerSpeed = 4.0f);

    ~Snake() override;

    void steer(int dir);
    void update(float timeDelta) override;
    void render(QOpenGLFunctions *gl) override;

    void eat();

    QOpenGLShaderProgram* loadShaders(ResourceManager* resourceManager) override;

private:
    float moveSpeed_;
    float steerSpeed_;
    float steerDir_;

    QVector<QVector3D> tail_;

    float foodPos_ = 500.0f;
};

#endif // SNAKE_HH
