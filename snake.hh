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
#include <QOpenGLFunctions_2_1>

#include "renderable.hh"
#include "powerup.hh"
#include "gameobject.hh"

const float SNAKE_SEGMENT_DIST = 0.02f;

class Snake : public GameObject
{
public:
    Snake(float length, float speed, float steer_speed);
    ~Snake() override;

    void steer(int dir);
    void setLength(float new_length);
    void applyPowerUp(PowerUp& power_up);

    void render(QOpenGLFunctions_2_1* gl) override;
    void setupRender(QOpenGLFunctions_2_1* gl) override;
    void initRender(QOpenGLFunctions_2_1* gl) override;

    void update(float time_delta) override;
private:
    float move_speed_;
    float steer_speed_;
    float steer_dir_;

    QVector<QVector3D> tail_;

    GLintptr vbo_;
};

#endif // SNAKE_HH
