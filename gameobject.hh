/**
  TIE-02201 Ohjelmointi 2: Perusteet, K2019
  Assignment 12.4: Matopelin paluu
    3D Snake game made with OpenGL ES 2.0.
    See 'instructions.txt' for further information.

  gameobject.hh
    Defines a base class for objects in the game to inherit.

  @author Joona Perasto, 272725, joona.perasto@tuni.fi
*/


#ifndef GAMEOBJECT_HH
#define GAMEOBJECT_HH

#include "renderable.hh"
#include "scene.hh"

/*!
 * \brief Base class for objects in the game to inherit.
 */
class GameObject : public Renderable
{
public:
    /*!
     * \brief Construct the GameObject
     * \param scene
     */
    GameObject(Scene* scene);

    /*!
     * \brief ~GameObject
     */
    virtual ~GameObject();

    /*!
     * \brief Update function that derived classes must implement.
     * \param deltaTime
     */
    virtual void update(float deltaTime) = 0;

protected:
    /*!
     * \brief Scene to store the GameObject in.
     */
    Scene* scene_;
};

#endif // GAMEOBJECT_HH
