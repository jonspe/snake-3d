/**
  TIE-02201 Ohjelmointi 2: Perusteet, K2019
  Assignment 12.4: Matopelin paluu
    3D Snake game made with OpenGL ES 2.0.
    See 'instructions.txt' for further information.

  foodeffect.cpp
    Defines a struct for storing the effects of a food item.

  @author Joona Perasto, 272725, joona.perasto@tuni.fi
*/

#include "foodeffect.hh"


FoodEffect::FoodEffect():
    duration(0.0f), lengthMod(0.0f), thicknessMod(0.0f), speedMod(0.0f),
    steerMod(0.0f), rainbowMod(0.0f) {}


FoodEffect::FoodEffect(QJsonObject effectJson)
{
    duration = float(effectJson["duration"].toDouble());
    lengthMod = float(effectJson["lengthMod"].toDouble());
    thicknessMod = float(effectJson["thicknessMod"].toDouble());
    speedMod = float(effectJson["speedMod"].toDouble());
    steerMod = float(effectJson["steerMod"].toDouble());
    rainbowMod = float(effectJson["rainbowMod"].toDouble());
}
