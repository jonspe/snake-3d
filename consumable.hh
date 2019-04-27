/**
  TIE-02201 Ohjelmointi 2: Perusteet, K2019
  Assignment 12.4: Matopelin paluu
    3D Snake game made with OpenGL 2.1 immediate mode.
    See 'instructions.txt' for further information.

  consumable.hh
    Defines a class for 3D consumable objects on the
    game board. Configurations are loaded from a
    JSON file.

  @author Joona Perasto, 272725, joona.perasto@tuni.fi
*/


#ifndef CONSUMABLE_HH
#define CONSUMABLE_HH

#include <QVector3D>

#include "gameobject.hh"
#include "consumeeffect.hh"


class Consumable : public GameObject
{
public:
    Consumable(const QString& consumableName);
    ~Consumable() override;

    void update(float deltaTime) override;
    void render(QOpenGLFunctions *gl) override;

    QVector3D getPosition();
    void setPosition(QVector3D position);

    ConsumeEffect getEffect();

private:
    void loadResources(const QString& consumableName);

    ConsumeEffect effect_;
    MeshData* mesh_;
    QOpenGLTexture* texture_;

    QVector3D position_;
    float floatAngle_;
};

#endif // CONSUMABLE_HH
