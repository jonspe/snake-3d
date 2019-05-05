/**
  TIE-02201 Ohjelmointi 2: Perusteet, K2019
  Assignment 12.4: Matopelin paluu
    3D Snake game made with OpenGL ES 2.0.
    See 'instructions.txt' for further information.

  transform.hh
    Defines a class used to handle object transformations,
    such as position, rotation and scale.

  @author Joona Perasto, 272725, joona.perasto@tuni.fi
*/


#include "transform.hh"
#include <math.h>


Transform::Transform():
    position_(QVector3D(0, 0, 0)),
    rotation_(QQuaternion()),
    scale_(QVector3D(1, 1, 1))
{
    updateMatrix();
}

QMatrix4x4 Transform::getModelMatrix() const
{
    return modelMatrix_;
}

QVector3D Transform::getPosition() const
{
    return position_;
}

QQuaternion Transform::getRotation() const
{
    return rotation_;
}

QVector3D Transform::getScale() const
{
    return scale_;
}



void Transform::setPosition(QVector3D position)
{
    position_ = position;
    updateMatrix();
}

void Transform::setRotation(QQuaternion quat)
{
    rotation_ = quat;
    updateMatrix();
}

void Transform::setRotation(QVector3D euler)
{
    rotation_ = QQuaternion::fromEulerAngles(euler);
    updateMatrix();
}

void Transform::setScale(QVector3D scale)
{
    scale_ = scale;
    updateMatrix();
}

void Transform::setScale(float scale)
{
    scale_ = QVector3D(scale, scale, scale);
    updateMatrix();
}



void Transform::updateMatrix()
{
    modelMatrix_ = QMatrix4x4();
    modelMatrix_.translate(position_);
    modelMatrix_.rotate(rotation_);
    modelMatrix_.scale(scale_);
}


