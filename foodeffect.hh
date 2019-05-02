/**
  TIE-02201 Ohjelmointi 2: Perusteet, K2019
  Assignment 12.4: Matopelin paluu
    3D Snake game made with OpenGL ES 2.0.
    See 'instructions.txt' for further information.

  foodeffect.hh
    Defines a struct for storing the effects of a FoodItem.

  @author Joona Perasto, 272725, joona.perasto@tuni.fi
*/


#ifndef CONSUMEEFFECT_HH
#define CONSUMEEFFECT_HH

#include <QJsonObject>
#include <QMap>


struct FoodEffect
{
    FoodEffect();
    FoodEffect(QJsonObject effectJson);

    float duration;

    float lengthMod;
    float thicknessMod;
    float speedMod;
    float steerMod;
    float rainbowMod;
};

#endif // CONSUMEEFFECT_HH
