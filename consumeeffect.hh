/**
  TIE-02201 Ohjelmointi 2: Perusteet, K2019
  Assignment 12.4: Matopelin paluu
    3D Snake game made with OpenGL ES 2.0.
    See 'instructions.txt' for further information.

  consumeeffect.hh
    Defines a struct for storing the effects of a consumable.

  @author Joona Perasto, 272725, joona.perasto@tuni.fi
*/


#ifndef CONSUMEEFFECT_HH
#define CONSUMEEFFECT_HH

#include <QJsonObject>
#include <QMap>


struct ConsumeEffect
{
    ConsumeEffect();
    ConsumeEffect(QJsonObject effectJson);

    float duration;

    float lengthMod;
    float speedMod;
    float steerMod;

    float rainbowMod;
};

#endif // CONSUMEEFFECT_HH
