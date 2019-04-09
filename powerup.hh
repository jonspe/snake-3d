#ifndef POWERUP_HH
#define POWERUP_HH

#include <QVector3D>

// Base class for different powerups

// Food could be considered as a power-up, with small size mo
class PowerUp
{
public:
    PowerUp();
    virtual ~PowerUp();

    virtual void render();
};

#endif // POWERUP_HH
