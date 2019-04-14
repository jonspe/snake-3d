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

const float SNAKE_HEAD_LENGTH = 0.06f;
const float SNAKE_TAIL_END_LENGTH = 0.06f;
const float SNAKE_SEGMENT_DIST = 0.04f;

const float SNAKE_MIN_LENGTH = SNAKE_HEAD_LENGTH + SNAKE_TAIL_END_LENGTH;


class Snake : public GameObject
{
public:
    Snake(float length, float speed, float steerSpeed);
    ~Snake() override;

    void steer(int dir);

    void initShaders() override;
    void render(QOpenGLFunctions *gl, QMatrix4x4 &viewMatrix) override;

    void update(float timeDelta) override;
private:
    float moveSpeed_;
    float steerSpeed_;
    float steerDir_;

    QVector<QVector3D> tail_;

    float foodPos_ = 0.0f;
    QOpenGLShaderProgram shaderProgram_;
};

#endif // SNAKE_HH
