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

    QOpenGLShaderProgram* loadResources(ResourceManager* resourceManager) override;

private:
    GLfloat* vertexData;
    GLuint* indexData;
};

#endif // FOODCONSUMABLE_HH