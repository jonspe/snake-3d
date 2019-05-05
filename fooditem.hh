/**
  TIE-02201 Ohjelmointi 2: Perusteet, K2019
  Assignment 12.4: Matopelin paluu
    3D Snake game made with OpenGL 2.1 immediate mode.
    See 'instructions.txt' for further information.

  fooditem.hh
    Defines a class for 3D consumable objects on the
    game board. Configurations are loaded from a
    JSON file.

  @author Joona Perasto, 272725, joona.perasto@tuni.fi
*/


#ifndef CONSUMABLE_HH
#define CONSUMABLE_HH

#include <QVector3D>

#include "gameobject.hh"
#include "foodeffect.hh"

const float ANIM_TIME = 0.45f;
const float FOOD_SCALE = 0.1f;

/*!
 * \brief A class for 3D consumable objects on the game board.
 */
class FoodItem : public GameObject
{
public:
    /*!
     * \brief Constructs the FoodItem by looking up the itemName
     * from a JSON table.
     * \param scene
     * \param itemName
     */
    FoodItem(Scene* scene, const QString& itemName);

    /*!
     * \brief Animates the food and perform eating check.
     * \param deltaTime
     */
    void update(float deltaTime) override;

    /*!
     * \brief Renders the model.
     * \param gl
     */
    void render(QOpenGLFunctions *gl) override;

    /*!
     * \brief Tells the item to start disappearing.
     */
    void consume();

    /*!
     * \brief canBeEaten
     * \return true if yes, false if no
     */
    bool canBeEaten() const;

    /*!
     * \brief Gets the position of the food.
     * \return position
     */
    QVector3D getPosition() const;

    /*!
     * \brief Gets the effect of the food.
     * \return effect
     */
    FoodEffect getEffect() const;

    /*!
     * \brief Sets the position of the food.
     * \param position
     */
    void setPosition(QVector3D position);

private:
    /*!
     * \brief Position of the food.
     */
    QVector3D position_;

    /*!
     * \brief Effect that applies modifiers to snake when eaten.
     */
    FoodEffect effect_;

    /*!
     * \brief Nesh to render.
     */
    MeshData* mesh_;

    /*!
     * \brief Texture to bind to mesh when rendering.
     */
    QOpenGLTexture* texture_;

    /*!
     * \brief isEaten_
     */
    bool isEaten_;

    /*!
     * \brief timeEaten_
     */
    float timeEaten_;

    /*!
     * \brief Variable for rotating and floating animation.
     */
    float floatAngle_;
};

#endif // CONSUMABLE_HH
