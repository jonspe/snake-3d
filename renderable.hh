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

#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QOpenGLShader>

class Renderable
{
public:
    virtual ~Renderable() {}

    // Create shader and VBO
    virtual void initShader(QOpenGLFunctions* gl) = 0;

    // Render the object on the GPU
    virtual void render(QOpenGLFunctions* gl) = 0;
};

#endif // RENDERABLE_HH
