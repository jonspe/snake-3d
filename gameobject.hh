#ifndef GAMEOBJECT_HH
#define GAMEOBJECT_HH

#include "renderable.hh"

class GameObject : public Renderable
{
public:
    GameObject();
    virtual ~GameObject();

    virtual void update(float timeDelta) = 0;
};

#endif // GAMEOBJECT_HH
