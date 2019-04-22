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
#include "consumable.hh"
#include "gameobject.hh"

const int SNAKE_DEFINITION = 12;

const float SNAKE_HEAD_LENGTH = 0.06f;
const float SNAKE_TAIL_END_LENGTH = 0.06f;
const float SNAKE_SEGMENT_DIST = 0.04f;

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

    float getTailLength();
    void setTailLength(float length);

    void applyEffect(Effect effect);

    void eat();

    QOpenGLShaderProgram* loadResources(ResourceManager* resourceManager) override;

private:
    void processDigestItems(float timeDelta);

    float moveSpeed_;
    float steerSpeed_;
    float steerDir_;

    struct DigestItem {
        Effect effect;
        float position;
    };

    QVector<QVector3D> tail_;
    QVector<DigestItem*> digestItems_;

    float foodPos_ = 500.0f;
};

#endif // SNAKE_HH
