#ifndef CAMERA_HH
#define CAMERA_HH

#include <QMatrix4x4>


class Camera
{
public:
    Camera();

    QMatrix4x4 getScreenTransform(QMatrix4x4 modelTransform);

    QVector3D getPosition();
    QVector3D getRotation();
    float getFieldOfView();

    void setPosition(QVector3D pos);
    void setRotation(QVector3D rot);
    void setFieldOfView(float fov);
private:
    QVector3D position;
    QVector3D rotation;

    float fieldOfView;

    QMatrix4x4 viewTransform;
    QMatrix4x4 projectionTransform;
};

#endif // CAMERA_HH
