/**
  TIE-02201 Ohjelmointi 2: Perusteet, K2019
  Assignment 12.4: Matopelin paluu
    3D Snake game made with OpenGL ES 2.0.
    See 'instructions.txt' for further information.

  foodeffect.hh
    Defines a struct for storing the effects of a FoodItem.

  @author Joona Perasto, 272725, joona.perasto@tuni.fi
*/


#ifndef FOODEFFECT_HH
#define FOODEFFECT_HH

#include <QJsonObject>
#include <QMap>


/*!
 * \brief Defines a struct for storing the effects of a FoodItem.
 */
struct FoodEffect
{
    /*!
     * \brief Constructs FoodEffect with properties set to zero.
     */
    FoodEffect();

    /*!
     * \brief Constructs FoodEffect with properties loaded from JSON file.
     */
    FoodEffect(QJsonObject effectJson);

    /*!
     * \brief Defines how long effect lasts.
     */
    float duration;

    /*!
     * \brief Defines how much length is added (addition).
     */
    float lengthMod;

    /*!
     * \brief Defines how much thickness is added (addition).
     */
    float thicknessMod;

    /*!
     * \brief Defines how much speed is added (addition).
     */
    float speedMod;

    /*!
     * \brief Defines how much steering speed is added (addition).
     */
    float steerMod;

    /*!
     * \brief Inactive, doesn't do anything yet
     */
    float rainbowMod;
};

#endif // FOODEFFECT_HH
