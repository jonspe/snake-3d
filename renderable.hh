/**
  TIE-02201 Ohjelmointi 2: Perusteet, K2019
  Assignment 12.4: Matopelin paluu
    3D Snake game made with OpenGL ES 2.0.
    See 'instructions.txt' for further information.

  renderable.hh
    Defines an abstract class for 3D renderable objects
    to inherit from.

  @author Joona Perasto, 272725, joona.perasto@tuni.fi
*/


#ifndef RENDERABLE_HH
#define RENDERABLE_HH

#include <QMatrix4x4>
#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QOpenGLBuffer>
#include <QList>

#include "resourcemanager.hh"
#include "transform.hh"


/*!
 * \brief Abstract class for 3D renderable objects
 * to inherit from.
 */
class Renderable
{
public:
    /*!
     * \brief Constructs by creating a new Transform
     */
    Renderable();
    virtual ~Renderable();

    /*!
     * \brief Renders the object. Must be implemented in derived class.
     * \param gl
     */
    virtual void render(QOpenGLFunctions* gl) = 0;

    /*!
     * \brief Gets the transform of the Renderable.
     * \return transform_
     */
    Transform* getTransform() const;

    /*!
     * \brief Gets the shader used by renderable.
     * \return shaderProgram_
     */
    QOpenGLShaderProgram* getShaderProgram() const;

protected:
    /*!
     * \brief Holds the renderables spatial data for 3D rendering.
     */
    Transform* transform_;

    /*!
     * \brief Program that defines how the Renderable is drawn.
     */
    QOpenGLShaderProgram* shaderProgram_;
};

#endif // RENDERABLE_HH
