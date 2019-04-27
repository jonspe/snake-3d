/**
  TIE-02201 Ohjelmointi 2: Perusteet, K2019
  Assignment 12.4: Matopelin paluu
    3D Snake game made with OpenGL 2.1 immediate mode.
    See 'instructions.txt' for further information.

  consumable.cpp
    Defines a class for 3D consumable objects on the
    game board. Configurations are loaded from a
    JSON file.

  @author Joona Perasto, 272725, joona.perasto@tuni.fi
*/


#include "consumable.hh"

#include <QJsonArray>

Consumable::Consumable(const QString& consumableName): floatAngle_(0.0f)
{
    ResourceManager& resourceManager = ResourceManager::getInstance();
    QJsonObject consumableData = resourceManager.getConsumableData();

    QJsonObject propertiesJson = consumableData[consumableName].toObject();
    QJsonObject effectJson = propertiesJson["effect"].toObject();

    shaderProgram_ = resourceManager.loadProgram(propertiesJson["shaderProgram"].toString());
    mesh_ = resourceManager.loadMesh(propertiesJson["mesh"].toString());
    texture_ = resourceManager.loadTexture(propertiesJson["texture"].toString());

    effect_ = ConsumeEffect(effectJson);

    transform_->setScale(0.1f);
}

Consumable::~Consumable() {}


void Consumable::update(float deltaTime)
{
    floatAngle_ += 180.0f * deltaTime;

    transform_->setPosition(position_ + QVector3D(0.0f, 0.0f, 0.04f * sinf(floatAngle_ * 0.02f)));
    transform_->setRotation(QVector3D(0.0f, 0.0f, floatAngle_));
}

void Consumable::render(QOpenGLFunctions *gl)
{
    shaderProgram_->enableAttributeArray("aVertex");
    shaderProgram_->enableAttributeArray("aTexcoord");
    shaderProgram_->enableAttributeArray("aNormal");

    shaderProgram_->setAttributeArray("aVertex", mesh_->vertexData.constData());
    shaderProgram_->setAttributeArray("aTexcoord", mesh_->texcoordData.constData());
    shaderProgram_->setAttributeArray("aNormal", mesh_->normalData.constData());

    texture_->bind();

    // Finally draw the snake as triangles
    gl->glDrawElements(GL_TRIANGLES, mesh_->indexData.count(),
                       GL_UNSIGNED_INT, mesh_->indexData.constData());

    texture_->release();
}

QVector3D Consumable::getPosition()
{
    return position_;
}

void Consumable::setPosition(QVector3D position)
{
    position_ = position;
    transform_->setPosition(position);
}

ConsumeEffect Consumable::getEffect()
{
    return effect_;
}
