#include "foodconsumable.hh"

FoodConsumable::FoodConsumable(): Consumable ()
{
    effect_.duration = -1.0f; // permanent
    effect_.lengthAdd = 0.1f;
}

FoodConsumable::~FoodConsumable() {}


void FoodConsumable::update(float timeDelta)
{

}

void FoodConsumable::render(QOpenGLFunctions *gl)
{

}

void FoodConsumable::loadResources(ResourceManager* resourceManager)
{
    // Load premade program
    shaderProgram_ = resourceManager->loadProgram("basicShader_program");

    // Link shader program to OpenGL
    shaderProgram_->link();

    shaderProgram_->enableAttributeArray("aVertex");
    shaderProgram_->enableAttributeArray("aUV");
    shaderProgram_->enableAttributeArray("aNormal");
}

