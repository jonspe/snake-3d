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


/*!
 * \brief Class for the 3D snake which the user controls.
 */
class Snake : public GameObject
{
public:
    Snake(Scene* scene);

    ~Snake() override;

    /*!
     * \brief steer
     * \param dir: -1, 0, or 1, where 0 is forward, -1 is left and 1 is right
     */
    void steer(int dir);

    /*!
     * \brief Moves snake forward, checks for collisions and calculates
     * eating effects.
     * \param deltaTime
     */
    void update(float deltaTime) override;

    /*!
     * \brief Renders the snake.
     * \param gl
     */
    void render(QOpenGLFunctions *gl) override;

    /*!
     * \brief isDead
     * \return true if yes, otherwise false
     */
    bool isDead();

    /*!
     * \brief Gets the tail's length by counting segments.
     * \return
     */
    float getTailLength();

    /*!
     * \brief Sets the tail's length.
     * \param length
     */
    void setTailLength(float length);

    /*!
     * \brief Gets snake properties.
     * \return snakeProperties
     */
    SnakeProperties* getProperties();

    /*!
     * \brief Gets the snake's heading in degrees.
     * \return heading
     */
    float getHeading();

    /*!
     * \brief Gets the snake's head's position.
     * \return headPosition
     */
    QVector3D getHeadPosition();

    /*!
     * \brief Eats a FoodItem, adds it to the snake's digestive
     * tract and applies its effects.
     * \param item
     */
    void eat(FoodItem* item);

    /*!
     * \brief Applies a food effect to the snake.
     * \param effect
     */
    void applyEffect(FoodEffect effect);

private:
    /*!
     * \brief Processes foods in the digestive tract and removes them
     * when they reach the end of the tail.
     * \param deltaTime
     */
    void processDigestItems(float deltaTime);

    QVector3D headPosition_;
    SnakeProperties* properties_;

    float steerDir_;
    float heading_;

    bool dead_;

    /*!
     * \brief Creates the tail by inserting points in a straight line
     * towards positive Z direction.
     */
    void initializeTail();

    /*!
     * \brief Datastructure for holding tail segment points.
     */
    QVector<QVector3D> tail_;

    /*!
     * \brief Datastructure for items in the digestive tract.
     */
    QVector<float> digestPositions_;
};

#endif // SNAKE_HH
