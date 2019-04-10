#ifndef POWERUP_HH
#define POWERUP_HH

#include <QVector3D>

#include "renderable.hh"

// Base class for different powerups
// Food could be considered as a power-up, with small size and speed modifiers

class PowerUp : public Renderable
{
public:
    PowerUp();
    virtual ~PowerUp();
};

#endif // POWERUP_HH
