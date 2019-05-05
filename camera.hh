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


const float POS_INTERPOLATION = 15.0f;
const float ROT_INTERPOLATION = 10.0f;
const float FOV_INTERPOLATION = 8.0f;

/*!
 * \brief Defines a camera object in world space, which can be used
 * to calculate view and projection matrices for 3D rendering.
 */
class Camera
{
public:
    /*!
     * \brief Construct the view and projection matrices by using
     * default values.
     *
     * Default values:
     *  fieldOfView_ = 60.0
     *  screenWidth_ = 800
     *  screenHeight_ = 600
     */
    Camera();

    /*!
     * \brief Interpolate position, rotation and field of view.
     * \param timeDelta
     */
    void update(float timeDelta);

    /*!
     * \brief Compute the MVP matrix for 3D transformations by
     * multiplying projection, view and model matrix together, in that order.
     * \param modelTransform
     * \return mvpMatrix
     */
    QMatrix4x4 computeMvpMatrix(QMatrix4x4 modelTransform);

    /*!
     * \brief Get the position of the camera.
     * \return position
     */
    QVector3D getPosition();

    /*!
     * \brief Get the rotation of the camera in euler angles.
     * \return rotation
     */
    QQuaternion getRotation();

    /*!
     * \brief Get the field of view of the camera in degrees.
     * \return fieldOfView
     */
    float getFieldOfView();

    /*!
     * \brief Sets how smoothly or aggressively the camera interpolates
     * to target.
     * \param factor
     */
    void setInterpolationFactor(float factor);

    /*!
     * \brief Set the width and height of the viewport for aspect
     * ratio calculations.
     * \param width
     * \param height
     */
    void setViewport(int width, int height);

    /*!
     * \brief Set the position of the camera.
     * \param pos
     */
    void setPosition(QVector3D pos);

    /*!
     * \brief Set the target position to interpolate to.
     * \param pos
     */
    void setPositionTarget(QVector3D pos);

    /*!
     * \brief Set the rotation of the camera.
     * \param pos
     */
    void setRotation(QQuaternion rot);

    /*!
     * \brief Set the target rotation to interpolate to.
     * \param rot
     */
    void setRotationTarget(QQuaternion rot);

    /*!
     * \brief Set the field of view of the camera.
     * \param fov
     */
    void setFieldOfView(float fov);

    /*!
     * \brief Set the target field of view to interpolate to.
     * \param fov
     */
    void setFieldOfViewTarget(float fov);

private:
    /*!
     * \brief Rotate and translate the view matrix, in that order.
     */
    void updateViewMatrix();

    /*!
     * \brief Compute the projection matrix with aspect ratio and field of view.
     */
    void updateProjectionMatrix();

    /*!
     * \brief Position of the camera.
     */
    QVector3D position_;

    /*!
     * \brief Target position for camera interpolation.
     */
    QVector3D positionTarget_;

    /*!
     * \brief Rotation of the camera.
     */
    QQuaternion rotation_;

    /*!
     * \brief Target rotation for camera interpolation.
     */
    QQuaternion rotationTarget_;

    /*!
     * \brief Field of view of the camera in degrees.
     */
    float fieldOfView_;

    /*!
     * \brief Target field of view of the camera to interpolate to in degrees.
     */
    float fieldOfViewTarget_;

    /*!
     * \brief Defines how smoothly the interpolation happens.
     */
    float interpolationFactor_;

    /*!
     * \brief Width of the screen.
     */
    int screenWidth_;

    /*!
     * \brief Height of the screen.
     */
    int screenHeight_;

    /*!
     * \brief The view matrix of the camera.
     */
    QMatrix4x4 viewMatrix_;

    /*!
     * \brief The projection matrix of the camera.
     */
    QMatrix4x4 projectionMatrix_;
};

#endif // CAMERA_HH
