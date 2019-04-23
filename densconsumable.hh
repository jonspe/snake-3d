#ifndef DENSCONSUMABLE_HH
#define DENSCONSUMABLE_HH

#include "consumable.hh"


class DensConsumable : public Consumable
{
public:
    DensConsumable();
    ~DensConsumable() override;

    void update(float timeDelta) override;
    void render(QOpenGLFunctions *gl) override;

    void loadResources(ResourceManager* resourceManager) override;

private:
    MeshData* mesh_;
    QOpenGLTexture* texture_;

    float floatAngle;
};

#endif // DENSCONSUMABLE_HH
