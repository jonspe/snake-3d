/**
  TIE-02201 Ohjelmointi 2: Perusteet, K2019
  Assignment 12.4: Matopelin paluu
    3D Snake game made with OpenGL ES 2.0.
    See 'instructions.txt' for further information.

  camera.cpp
    Defines a camera object in world space, which can be used
    to calculate view and projection matrices for 3D rendering.

  @author Joona Perasto, 272725, joona.perasto@tuni.fi
*/


#include "camera.hh"

Camera::Camera():
    fieldOfView_(60.0f), fieldOfViewTarget_(60.0f),
    screenWidth_(800), screenHeight_(600)
{
    updateViewMatrix();
    updateProjectionMatrix();
}

QMatrix4x4 Camera::computeMvpMatrix(QMatrix4x4 modelMatrix)
{
    return projectionMatrix_ * viewMatrix_ * modelMatrix;
}

void Camera::update(float timeDelta)
{
    position_ += (positionTarget_ - position_) * timeDelta * POS_INTERPOLATION;
    rotation_ = QQuaternion::slerp(rotation_, rotationTarget_, timeDelta * ROT_INTERPOLATION);
    fieldOfView_ += (fieldOfViewTarget_ - fieldOfView_) * timeDelta * FOV_INTERPOLATION;

    updateProjectionMatrix();
}

void Camera::setViewport(int width, int height)
{
    screenWidth_ = width;
    screenHeight_ = height;
    updateProjectionMatrix();
}

void Camera::setPosition(QVector3D pos)
{
    position_ = pos;
    positionTarget_ = pos;
    updateViewMatrix();
}

void Camera::setPositionTarget(QVector3D pos)
{
    positionTarget_ = pos;
    updateViewMatrix();
}

void Camera::setRotation(QQuaternion rot)
{
    rotation_ = rot;
    rotationTarget_ = rot;
    updateViewMatrix();
}

void Camera::setRotationTarget(QQuaternion rot)
{
    rotationTarget_ = rot;
    updateViewMatrix();
}

void Camera::setFieldOfView(float fov)
{
    fieldOfView_ = fov;
    fieldOfViewTarget_ = fov;
    updateProjectionMatrix();
}

void Camera::setFieldOfViewTarget(float fov)
{
    fieldOfViewTarget_ = fov;
    updateProjectionMatrix();
}

void Camera::updateViewMatrix()
{
    viewMatrix_ = QMatrix4x4();
    viewMatrix_.rotate(rotation_);
    viewMatrix_.translate(-position_);
}

void Camera::updateProjectionMatrix()
{
    float aspect = float(screenWidth_) / float(screenHeight_);
    projectionMatrix_ = QMatrix4x4();
    projectionMatrix_.perspective(fieldOfView_, aspect, 0.03f, 20.0f);
}
