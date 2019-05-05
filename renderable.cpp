/**
  TIE-02201 Ohjelmointi 2: Perusteet, K2019
  Assignment 12.4: Matopelin paluu
    3D Snake game made with OpenGL ES 2.0.
    See 'instructions.txt' for further information.

  renderable.cpp
    Defines an abstract class for 3D renderable objects
    to inherit from.

  @author Joona Perasto, 272725, joona.perasto@tuni.fi
*/


#include "renderable.hh"


Renderable::Renderable(): transform_(), shaderProgram_(nullptr) {
    transform_ = new Transform;
    shaderProgram_ = nullptr;
}

Renderable::~Renderable()
{
    delete transform_;
}

QOpenGLShaderProgram* Renderable::getShaderProgram()
{
    return shaderProgram_;
};

Transform* Renderable::getTransform()
{
    return transform_;
}

