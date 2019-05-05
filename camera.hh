/**
  TIE-02201 Ohjelmointi 2: Perusteet, K2019
  Assignment 12.4: Matopelin paluu
    3D Snake game made with OpenGL ES 2.0.
    See 'instructions.txt' for further information.

  camera.hh
    Defines a camera object in world space, which can be used
    to calculate view and projection matrices for 3D rendering.

  @author Joona Perasto, 272725, joona.perasto@tuni.fi
*/

#ifndef CAMERA_HH
#define CAMERA_HH

#include <QMatrix4x4>


namespace {
    enum class ProjectionType {
        PERSPECTIVE,
        ORTHO
    };
}

const float POS_INTERPOLATION = 15.0f;
const float ROT_INTERPOLATION = 10.0f;
const float FOV_INTERPOLATION = 8.0f;

class Camera
{
public:
    Camera();

    QMatrix4x4 computeMvpMatrix(QMatrix4x4 modelTransform);

    void update(float timeDelta);

    QVector3D getPosition();
    QVector3D getRotation();
    float getFieldOfView();

    void setViewport(int width, int height);

    void setPosition(QVector3D pos);
    void setPositionTarget(QVector3D pos);

    void setRotation(QQuaternion rot);
    void setRotationTarget(QQuaternion rot);

    void setFieldOfView(float fov);
    void setFieldOfViewTarget(float fov);

private:
    void updateViewMatrix();
    void updateProjectionMatrix();

    QVector3D position_;
    QVector3D positionTarget_;
    QQuaternion rotation_;
    QQuaternion rotationTarget_;

    float fieldOfView_;
    float fieldOfViewTarget_;

    int screenWidth_;
    int screenHeight_;

    QMatrix4x4 viewMatrix_;
    QMatrix4x4 projectionMatrix_;
};

#endif // CAMERA_HH
