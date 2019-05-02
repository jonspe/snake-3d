#include "camera.hh"

Camera::Camera(): fieldOfView_(60.0f), screenWidth_(800), screenHeight_(600)
{
    updateViewMatrix();
    updateProjectionMatrix();
}

QMatrix4x4 Camera::computeMvpMatrix(QMatrix4x4 modelMatrix)
{
    return projectionMatrix_ * viewMatrix_ * modelMatrix;
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
    updateViewMatrix();
}

void Camera::setRotation(QQuaternion rot)
{
    rotation_ = rot;
    updateViewMatrix();
}

void Camera::setFieldOfView(float fov)
{
    fieldOfView_ = fov;
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
