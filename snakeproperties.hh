/**
  TIE-02201 Ohjelmointi 2: Perusteet, K2019
  Assignment 12.4: Matopelin paluu
    3D Snake game made with OpenGL ES 2.0.
    See 'instructions.txt' for further information.

  snakeproperties.hh
    Defines a class representing the properties of the
    snake. Handles food effect stacking.

  @author Joona Perasto, 272725, joona.perasto@tuni.fi
*/

#ifndef SNAKEPROPERTIES_HH
#define SNAKEPROPERTIES_HH

#include <QVector>
#include "foodeffect.hh"

const float DEFAULT_LENGTH = 1.0f;
const float DEFAULT_THICKNESS = 0.05f;
const float DEFAULT_SPEED = 1.1f;
const float DEFAULT_STEER = 3.0f;


class SnakeProperties {
public:
    SnakeProperties();

    void update(float deltaTime);
    void addEffect(FoodEffect effect);

    float getLength();
    float getThickness();
    float getMoveSpeed();
    float getSteerSpeed();

private:
    float length_;
    float thickness_;
    float moveSpeed_;
    float steerSpeed_;

    struct EffectStackItem
    {
        FoodEffect effect;
        float timeRemoved;
    };

    FoodEffect calculateEffectFromStack();
    QVector<EffectStackItem> effectStack_;

    float timeCounter_;
};


#endif // SNAKEPROPERTIES_HH
