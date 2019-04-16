/**
  TIE-02201 Ohjelmointi 2: Perusteet, K2019
  Assignment 12.4: Matopelin paluu
    3D Snake game made with OpenGL 2.1 immediate mode.
    See 'instructions.txt' for further information.

  gameobject.hh
    Defines a base class for game objects around the game board.

  @author Joona Perasto, 272725, joona.perasto@tuni.fi
*/


#ifndef GAMEOBJECT_HH
#define GAMEOBJECT_HH

#include <QVector3D>
#include "renderable.hh"

class GameObject: public Renderable
{
public:
    GameObject();
    virtual ~GameObject();

    virtual void update(float delta_time) = 0;

    QVector3D getPosition();
    QVector3D getVelocity();
    QVector3D getDirection();
    float getSpeed();
    float getHeading();

    void setPosition(QVector3D position);
    void setVelocity(QVector3D velocity);
    void setDirection(QVector3D direction);
    void setSpeed(float speed);
    void setHeading(float heading);

protected:
    QVector3D position_;
    QVector3D velocity_;
};

#endif // GAMEOBJECT_HH
