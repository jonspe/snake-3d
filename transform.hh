/**
  TIE-02201 Ohjelmointi 2: Perusteet, K2019
  Assignment 12.4: Matopelin paluu
    3D Snake game made with OpenGL 2.1 immediate mode.
    See 'instructions.txt' for further information.

  gameobject.hh
    Defines a base class for game objects around the game board.

  @author Joona Perasto, 272725, joona.perasto@tuni.fi
*/


#ifndef TRANSFORM_HH
#define TRANSFORM_HH

#include <QVector3D>
#include <QQuaternion>
#include <QMatrix4x4>

class Transform
{
public:
    Transform();
    ~Transform();

    QMatrix4x4 getModelMatrix();

    QVector3D getPosition();
    QQuaternion getRotation();
    QVector3D getScale();

    void setPosition(QVector3D position);
    void setRotation(QQuaternion rotation);
    void setRotation(QVector3D rotation);
    void setScale(QVector3D scale);
    void setScale(float scale);

private:
    QVector3D position_;
    QQuaternion rotation_;
    QVector3D scale_;

    QMatrix4x4 modelMatrix_;

    void updateMatrix();
};

#endif // TRANSFORM_HH
