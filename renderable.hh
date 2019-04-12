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

#include <QOpenGLFunctions_2_1>

class Renderable
{
public:
    virtual ~Renderable() {}

    // Init object by for example, generating a VBO
    virtual void initRender(QOpenGLFunctions_2_1* gl) = 0;

    // Do CPU related vertex data tasks before passing to GPU
    virtual void setupRender(QOpenGLFunctions_2_1* gl) = 0;

    // Render the object on the GPU
    virtual void render(QOpenGLFunctions_2_1* gl) = 0;
};

#endif // RENDERABLE_HH
