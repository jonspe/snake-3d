/**
  TIE-02201 Ohjelmointi 2: Perusteet, K2019
  Assignment 12.4: Matopelin paluu
    3D Snake game made with OpenGL 2.1 immediate mode.
    See 'instructions.txt' for further information.

  renderable.hh
    Defines an abstract class for renderable objects
    to inherit from.

  @author Joona Perasto, 272725, joona.perasto@tuni.fi
*/


#ifndef RENDERABLE_HH
#define RENDERABLE_HH

#include <QMatrix4x4>
#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>

class Renderable
{
public:
    virtual ~Renderable() {}

    // Create VBO, allocate memory etc.
    virtual void loadShaders() = 0;

    // Render the object on the GPU
    virtual void render(QOpenGLFunctions* gl, QMatrix4x4 &viewMatrix) = 0;

protected:
    QOpenGLShaderProgram shaderProgram_;
    QMatrix4x4 modelTransform_;

};

#endif // RENDERABLE_HH
