/**
  TIE-02201 Ohjelmointi 2: Perusteet, K2019
  Assignment 12.4: Matopelin paluu
    3D Snake game made with OpenGL 2.1 immediate mode.
    See 'instructions.txt' for further information.

  snake.cpp
    Defines a class for the snake which the user controls.

  @author Joona Perasto, 272725, joona.perasto@tuni.fi
*/


#include "snake.hh"

#include <QDebug>
#include <math.h>

#define PI_F 3.141592653f


Snake::Snake(float length, float speed, float steer_speed): GameObject (),
    move_speed_(speed), steer_speed_(steer_speed), steer_dir_(0)
{
    int segments = int(length/SNAKE_SEGMENT_DIST);
    for (int i = 0; i < segments; ++i)
    {
        tail_.push_back(getPosition() + QVector3D(0.0f, -i * SNAKE_SEGMENT_DIST, 0.0f));
    }
}

Snake::~Snake() {}


void Snake::update(float time_delta)
{
    // Multiply by move_speed_ to ensure same turning radius across speeds
    float headingIncrement = steer_dir_ * steer_speed_ * move_speed_ * time_delta;

    setSpeed(move_speed_);
    setHeading(getHeading() + headingIncrement);
    position_ += velocity_ * time_delta;

    // Calculate tail positions so that each is a set distance apart
    // Gives a really cool effect, like rope at 1.0 friction with ground
    QVector3D prev_pos = position_;
    for (int i = 1; i < tail_.size(); ++i)
    {
        QVector3D v = tail_.at(i);
        QVector3D n = (v-prev_pos).normalized();
        tail_.replace(i, prev_pos + n*SNAKE_SEGMENT_DIST);

        prev_pos = tail_.at(i);
    }
}

void Snake::steer(int dir)
{
    steer_dir_ = dir;
}


void Snake::initRender(QOpenGLFunctions_2_1 *gl) {}
void Snake::setupRender(QOpenGLFunctions_2_1 *gl) {}

void Snake::render(QOpenGLFunctions_2_1* gl)
{
    gl->glBegin(GL_QUAD_STRIP);

    int s = tail_.size();

    // Calculate tail vertices
    for (int i = 2; i < s; ++i) {
        QVector3D v0 = tail_.at(i-1);
        QVector3D v1 = tail_.at(i);

        QVector3D a = (v1-v0).normalized() * 0.03f;

        gl->glVertex3f(v0.x() - a.y(), v0.y() + a.x(), v0.z());
        gl->glVertex3f(v0.x() + a.y(), v0.y() - a.x(), v0.z());
    }

    // Thinking of VBO (Vertex Buffer Object) implementation
    /*
    gl->glEnableClientState(GL_VERTEX_ARRAY);
    gl->glEnableClientState(GL_COLOR_ARRAY);
    gl->glVertexPointer(3, GL_FLOAT, 6*sizeof(float), data);
    gl->glColorPointer(3, GL_FLOAT, 6*sizeof(float), data);

    gl->glDrawElements(GL_TRIANGLES, num_vertices);
    */

    gl->glEnd();
}

void Snake::setLength(float new_length) {}
void Snake::applyPowerUp(PowerUp& power_up) {}
