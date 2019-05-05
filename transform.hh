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


#ifndef TRANSFORM_HH
#define TRANSFORM_HH

#include <QVector3D>
#include <QQuaternion>
#include <QMatrix4x4>


/*!
 * \class Transform
 * \brief Defines a class used to handle object transformations.
 */
class Transform
{
public:
    /*!
     * \brief Constructs the transform by computing the model
     * matrix by using identity values.
     */
    Transform();

    /*!
     * \brief Returns the model matrix of the transform.
     * \return QMatrix4x4 modelMatrix
     */
    QMatrix4x4 getModelMatrix() const;

    /*!
     * \brief Returns the position of the transform.
     * \return QVector3D position
     */
    QVector3D getPosition() const;

    /*!
     * \brief Returns the rotation of the transform.
     * \return QMatrix4x4 modelMatrix
     */
    QQuaternion getRotation() const;

    /*!
     * \brief Returns the scale of the transform.
     * \return QMatrix4x4 modelMatrix
     */
    QVector3D getScale() const;

    /*!
     * \brief Set the position of the transform.
     * \param position
     */
    void setPosition(QVector3D position);

    /*!
     * \brief Set the rotation of the transform with a quaternion.
     * \param rotation
     */
    void setRotation(QQuaternion rotation);

    /*!
     * \brief Set the rotation of the transform with euler angles.
     * \param rotation
     */
    void setRotation(QVector3D rotation);

    /*!
     * \brief Set the scale of the transform with a vector.
     * \param scale
     */
    void setScale(QVector3D scale);

    /*!
     * \brief Set the components of the scale of the transform to param.
     * \param scale
     */
    void setScale(float scale);

private:
    /*!
     * \brief Member variable representing the position of the transform.
     */
    QVector3D position_;

    /*!
     * \brief Member variable representing the rotation of the transform.
     */
    QQuaternion rotation_;

    /*!
     * \brief Member variable representing the scale of the transform.
     */
    QVector3D scale_;

    /*!
     * \brief Member variable representing the model matrix of the transform.
     */
    QMatrix4x4 modelMatrix_;

    /*!
     * \brief Translate, rotate and scale the model matrix, in that order.
     */
    void updateMatrix();
};

#endif // TRANSFORM_HH
