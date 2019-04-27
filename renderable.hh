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

class Renderable
{
public:
    Renderable();
    virtual ~Renderable() {}

    // Render the object on the GPU
    virtual void render(QOpenGLFunctions* gl) = 0;

    Transform* getTransform();
    QOpenGLShaderProgram* getShaderProgram();

protected:
    Transform* transform_;
    QOpenGLShaderProgram* shaderProgram_;
};

#endif // RENDERABLE_HH
