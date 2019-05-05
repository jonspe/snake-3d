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

/*!
 * \brief Defines a class representing the properties of the
 * snake. Handles food effect stacking.
 */
class SnakeProperties {
public:
    /*!
     * \brief Constructs properties with default values.
     */
    SnakeProperties();

    /*!
     * \brief Updates effect stack and removes expired effects.
     * \param deltaTime
     */
    void update(float deltaTime);

    /*!
     * \brief Adds a food effect to the stack.
     * \param effect
     */
    void addEffect(FoodEffect effect);

    /*!
     * \brief Gets the length property.
     * \return length
     */
    float getLength();

    /*!
     * \brief Gets the thickness property.
     * \return thickness
     */
    float getThickness();

    /*!
     * \brief Gets the moveSpeed property.
     * \return moveSpeed
     */
    float getMoveSpeed();

    /*!
     * \brief Gets the steerSpeed property.
     * \return steerSpeed
     */
    float getSteerSpeed();

private:
    float length_;
    float thickness_;
    float moveSpeed_;
    float steerSpeed_;

    /*!
     * \brief Struct that contains a food effect and its expiration time.
     */
    struct EffectStackItem
    {
        FoodEffect effect;
        float timeRemoved;
    };

    /*!
     * \brief Calculates the sum effect from all effects in the stack.
     * \return sumEffect
     */
    FoodEffect calculateEffectFromStack();

    /*!
     * \brief Datastructure for active food effects.
     */
    QVector<EffectStackItem> effectStack_;

    /*!
     * \brief Time counter to keep track of effect expiration.
     */
    float timeCounter_;
};


#endif // SNAKEPROPERTIES_HH
