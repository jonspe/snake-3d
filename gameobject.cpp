/**
  TIE-02201 Ohjelmointi 2: Perusteet, K2019
  Assignment 12.4: Matopelin paluu
    3D Snake game made with OpenGL 2.1 immediate mode.
    See 'instructions.txt' for further information.

  gameobject.cpp
    Defines a base class for game objects around the game board.

  @author Joona Perasto, 272725, joona.perasto@tuni.fi
*/


#include "gameobject.hh"
#include <math.h>


GameObject::GameObject(): position_(), velocity_() {}
GameObject::~GameObject() {}

void GameObject::update(float delta_time) {
    Q_UNUSED(delta_time);
};

QVector3D GameObject::getPosition()
{
    return position_;
}

QVector3D GameObject::getVelocity()
{
    return velocity_;
}

QVector3D GameObject::getDirection()
{
    return velocity_.normalized();
}

float GameObject::getSpeed()
{
    return velocity_.length();
}

float GameObject::getHeading()
{
    return atan2f(velocity_.y(), velocity_.x());
}



void GameObject::setPosition(QVector3D position)
{
    position_ = position;
}

void GameObject::setVelocity(QVector3D velocity)
{
    velocity_ = velocity;
}

void GameObject::setDirection(QVector3D direction)
{
    velocity_ = direction * velocity_.length();
}

void GameObject::setSpeed(float speed)
{
    velocity_ = velocity_.normalized() * speed;
}

void GameObject::setHeading(float heading)
{
    float speed = velocity_.length();
    velocity_ = QVector3D(cosf(heading), sinf(heading), 0) * speed;
}
