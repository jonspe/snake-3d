/**
  TIE-02201 Ohjelmointi 2: Perusteet, K2019
  Assignment 12.4: Matopelin paluu
    3D Snake game made with OpenGL ES 2.0.
    See 'instructions.txt' for further information.

  gameobject.cpp
    Defines a base class for objects in the game to inherit.

  @author Joona Perasto, 272725, joona.perasto@tuni.fi
*/

#include "gameobject.hh"

GameObject::GameObject(): Renderable ()
{

}

GameObject::~GameObject() {}
