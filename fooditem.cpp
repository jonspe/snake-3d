/**
  TIE-02201 Ohjelmointi 2: Perusteet, K2019
  Assignment 12.4: Matopelin paluu
    3D Snake game made with OpenGL 2.1 immediate mode.
    See 'instructions.txt' for further information.

  fooditem.cpp
    Defines a class for 3D food item objects on the
    game board. Configurations are loaded from a
    JSON file.

  @author Joona Perasto, 272725, joona.perasto@tuni.fi
*/


#include "fooditem.hh"

#include <QJsonArray>

FoodItem::FoodItem(Scene* scene, const QString& itemName): GameObject(scene),
    floatAngle_(0.0f), timeEaten_(0.0f), isEaten_(false)
{
    ResourceManager& resourceManager = ResourceManager::getInstance();
    QJsonObject foodData = resourceManager.getFoodData();

    QJsonObject propertiesJson = foodData[itemName].toObject();
    if (propertiesJson.isEmpty())
    {
        qWarning() << "FoodItem" << itemName << "does not exist.";
        propertiesJson = foodData["null"].toObject();
    }

    QJsonObject effectJson = propertiesJson["effect"].toObject();

    shaderProgram_ = resourceManager.loadProgram(propertiesJson["shaderProgram"].toString());
    mesh_ = resourceManager.loadMesh(propertiesJson["mesh"].toString());
    texture_ = resourceManager.loadTexture(propertiesJson["texture"].toString());

    effect_ = FoodEffect(effectJson);

    transform_->setScale(0.1f);
}

FoodItem::~FoodItem() {}


void FoodItem::update(float deltaTime)
{
    floatAngle_ += 180.0f * deltaTime;

    transform_->setPosition(position_ + QVector3D(0.0f, 0.04f * (1 + sinf(floatAngle_ * 0.02f)), 0.0f));
    transform_->setRotation(QVector3D(0.0f, floatAngle_, 0.0f));

    if (isEaten_)
    {
        timeEaten_ += deltaTime;
        float scale = 1 - timeEaten_/ANIM_TIME;

        transform_->setScale(0.1f * scale);
        if (scale <= 0.0f)
            scene_->removeGameObject(this);
    }
}

void FoodItem::render(QOpenGLFunctions *gl)
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

void FoodItem::consume()
{
    isEaten_ = true;
    timeEaten_ = 0.0f;
}

bool FoodItem::canBeEaten()
{
    return !isEaten_;
}

QVector3D FoodItem::getPosition()
{
    return position_;
}

void FoodItem::setPosition(QVector3D position)
{
    position_ = position;
    transform_->setPosition(position);
}

FoodEffect FoodItem::getEffect()
{
    return effect_;
}
