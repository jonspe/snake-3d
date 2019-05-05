/**
  TIE-02201 Ohjelmointi 2: Perusteet, K2019
  Assignment 12.4: Matopelin paluu
    3D Snake game made with OpenGL ES 2.0.
    See 'instructions.txt' for further information.

  snake.hh
    Defines a class for the 3D snake which the user controls.

  @author Joona Perasto, 272725, joona.perasto@tuni.fi
*/


#ifndef SNAKE_HH
#define SNAKE_HH

#include <QVector>
#include <QVector3D>
#include <QOpenGLFunctions>

#include "renderable.hh"
#include "fooditem.hh"
#include "gameobject.hh"
#include "scene.hh"
#include "snakeproperties.hh"

const int SNAKE_DEFINITION = 16;
const float SNAKE_SEGMENT_DIST = 0.03f;


class Snake : public GameObject
{
public:
    Snake(Scene* scene);

    ~Snake() override;

    void steer(int dir);
    void update(float deltaTime) override;
    void render(QOpenGLFunctions *gl) override;

    bool isDead();

    float getTailLength();
    void setTailLength(float length);

    SnakeProperties* getProperties();

    float getHeading();
    QVector3D getHeadPosition();

    void eat(FoodItem* item);
    void applyEffect(FoodEffect effect);

private:
    void processDigestItems(float deltaTime);

    QVector3D headPosition_;
    SnakeProperties* properties_;

    float steerDir_;
    float heading_;

    bool dead_;

    void initializeTail();

    QVector<QVector3D> tail_;
    QVector<float> digestPositions_;
};

#endif // SNAKE_HH
