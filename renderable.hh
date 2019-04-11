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
#include <QVector3D>

class Renderable
{
public:
    virtual ~Renderable() {}
    virtual void render(QOpenGLFunctions_2_1* gl) = 0;
};

#endif // RENDERABLE_HH
