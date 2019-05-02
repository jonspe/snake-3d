#ifndef CAMERA_HH
#define CAMERA_HH

#include <QMatrix4x4>


namespace {
    enum class ProjectionType {
        PERSPECTIVE,
        ORTHO
    };
}

class Camera
{
public:
    Camera();

    QMatrix4x4 computeMvpMatrix(QMatrix4x4 modelTransform);

    QVector3D getPosition();
    QVector3D getRotation();
    float getFieldOfView();

    void setViewport(int width, int height);
    void setPosition(QVector3D pos);
    void setRotation(QQuaternion rot);
    void setFieldOfView(float fov);

private:
    void updateViewMatrix();
    void updateProjectionMatrix();

    QVector3D position_;
    QQuaternion rotation_;

    float fieldOfView_;
    int screenWidth_;
    int screenHeight_;

    QMatrix4x4 viewMatrix_;
    QMatrix4x4 projectionMatrix_;
};

#endif // CAMERA_HH
