#include "foodconsumable.hh"

FoodConsumable::FoodConsumable(): Consumable (), floatAngle(0.0f)
{
    effect_.duration = -1.0f; // permanent
    effect_.lengthAdd = 0.1f;

    transform_->setScale(0.06f);
}

FoodConsumable::~FoodConsumable() {}


void FoodConsumable::update(float timeDelta)
{
    floatAngle += 140.0f * timeDelta;
    transform_->setRotation(QVector3D(0.0f, 0.0f, floatAngle));
}

void FoodConsumable::render(QOpenGLFunctions *gl)
{
    shaderProgram_->enableAttributeArray("aVertex");
    shaderProgram_->enableAttributeArray("aTexcoord");
    shaderProgram_->enableAttributeArray("aNormal");

    shaderProgram_->setAttributeArray("aVertex", mesh_->vertexData.constData());
    shaderProgram_->setAttributeArray("aTexcoord", mesh_->texcoordData.constData());
    shaderProgram_->setAttributeArray("aNormal", mesh_->normalData.constData());

    //shaderProgram_->
    texture_->bind();

    // Finally draw the snake as triangles
    gl->glDrawElements(GL_TRIANGLES, mesh_->indexData.count(),
                       GL_UNSIGNED_INT, mesh_->indexData.constData());

    texture_->release();
}

void FoodConsumable::loadResources(ResourceManager* resourceManager)
{
    // Load premade program
    shaderProgram_ = resourceManager->loadProgram("consumable_program");
    mesh_ = resourceManager->loadMesh("apple_mesh.obj");
    texture_ = resourceManager->loadTexture("apple_tex_stylized.png");

    // Link shader program to OpenGL
    shaderProgram_->link();

    shaderProgram_->enableAttributeArray("aVertex");
    shaderProgram_->enableAttributeArray("aTexcoord");
    shaderProgram_->enableAttributeArray("aNormal");

    shaderProgram_->setAttributeArray("aVertex", mesh_->vertexData.constData());
    shaderProgram_->setAttributeArray("aTexcoord", mesh_->texcoordData.constData());
    shaderProgram_->setAttributeArray("aNormal", mesh_->normalData.constData());

    shaderProgram_->bind();
    shaderProgram_->setUniformValue("texture", 0);
}

