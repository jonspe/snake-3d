/**
  TIE-02201 Ohjelmointi 2: Perusteet, K2019
  Assignment 12.4: Matopelin paluu
    3D Snake game made with OpenGL ES 2.0.
    See 'instructions.txt' for further information.

  snakeproperties.cpp
    Defines a class representing the properties of the
    snake. Handles food effect stacking.

  @author Joona Perasto, 272725, joona.perasto@tuni.fi
*/

#include "snakeproperties.hh"


#include <QDebug>

const float EPSILON = 0.00001f;


SnakeProperties::SnakeProperties(): timeCounter_(0.0f)
{
    length_ = DEFAULT_LENGTH;
    thickness_ = DEFAULT_THICKNESS;
    moveSpeed_ = DEFAULT_SPEED;
    steerSpeed_ = DEFAULT_STEER;
}

void SnakeProperties::update(float deltaTime)
{
    timeCounter_ += deltaTime;

    auto it = effectStack_.begin();

    // Remove temporary effects if they've run out
    while (it != effectStack_.end())
    {
        EffectStackItem item = *it;
        if (item.timeRemoved < timeCounter_)
        {
            it = effectStack_.erase(it);
            continue;
        }

        ++it;
    }
}

void SnakeProperties::addEffect(FoodEffect effect)
{
    // Effect is permanent if duration 0 or below
    if (effect.duration < EPSILON)
    {
        length_ += effect.lengthMod;
        thickness_ += effect.thicknessMod;
        moveSpeed_ += effect.speedMod;
        steerSpeed_ += effect.steerMod;
    }
    else
    {
        effectStack_.append(
                    EffectStackItem{
                        effect,
                        timeCounter_ + effect.duration});
    }
}

float SnakeProperties::getLength()
{
    FoodEffect effect = calculateEffectFromStack();
    return length_ + effect.lengthMod;
}

float SnakeProperties::getThickness()
{
    FoodEffect effect = calculateEffectFromStack();
    return thickness_ + effect.thicknessMod;
}

float SnakeProperties::getMoveSpeed()
{
    FoodEffect effect = calculateEffectFromStack();
    return moveSpeed_ + effect.speedMod;
}

float SnakeProperties::getSteerSpeed()
{
    FoodEffect effect = calculateEffectFromStack();
    return steerSpeed_ + effect.steerMod;
}


FoodEffect SnakeProperties::calculateEffectFromStack()
{
    FoodEffect calculatedEffect;

    // Calculate modifiers by addition
    for (EffectStackItem item : effectStack_)
    {
        calculatedEffect.lengthMod += item.effect.lengthMod;
        calculatedEffect.speedMod += item.effect.speedMod;
        calculatedEffect.steerMod += item.effect.steerMod;
        calculatedEffect.thicknessMod += item.effect.thicknessMod;
        calculatedEffect.rainbowMod += item.effect.rainbowMod;
    }

    return calculatedEffect;
}
