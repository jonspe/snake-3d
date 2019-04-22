#ifndef FOODCONSUMABLE_HH
#define FOODCONSUMABLE_HH

#include "consumable.hh"


class FoodConsumable : public Consumable
{
public:
    FoodConsumable();
    ~FoodConsumable() override;

    void update(float timeDelta) override;
    void render(QOpenGLFunctions *gl) override;

    void loadResources(ResourceManager* resourceManager) override;

private:
    MeshData* mesh;
};

#endif // FOODCONSUMABLE_HH
