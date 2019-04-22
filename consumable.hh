/**
  TIE-02201 Ohjelmointi 2: Perusteet, K2019
  Assignment 12.4: Matopelin paluu
    3D Snake game made with OpenGL 2.1 immediate mode.
    See 'instructions.txt' for further information.

  powerup.hh
    Defines an abstract class for collectible powerups
    on the game board.

  @author Joona Perasto, 272725, joona.perasto@tuni.fi
*/


#ifndef POWERUP_HH
#define POWERUP_HH

#include <QVector3D>

#include "gameobject.hh"


struct Effect {
    float duration = -1.0f; // 0 or negative for permanent (-1 for good measure), positive for temporary

    float lengthAdd = 0.0f; // add to length
    float rainbowAdd = 0.0f; // add to rainbow factor

    float speedMult = 1.0f; // multiply speed
    float steerMult = 1.0f; // multiply steering speed
};


class Consumable : public GameObject
{
public:
    Consumable();
    virtual ~Consumable();

    Effect getEffect();

protected:
    Effect effect_;

};

#endif // POWERUP_HH
