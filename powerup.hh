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

// Base class for different powerups
// Food could be considered as a power-up, with small size and speed modifiers

class PowerUp : public GameObject
{
public:
    PowerUp();
    virtual ~PowerUp();
};

#endif // POWERUP_HH
