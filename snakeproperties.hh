#ifndef SNAKEPROPERTIES_HH
#define SNAKEPROPERTIES_HH

#include <QVector>
#include "foodeffect.hh"

const float DEFAULT_LENGTH = 1.0f;
const float DEFAULT_THICKNESS = 0.05f;
const float DEFAULT_SPEED = 0.7f;
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
