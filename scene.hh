/**
  TIE-02201 Ohjelmointi 2: Perusteet, K2019
  Assignment 12.4: Matopelin paluu
    3D Snake game made with OpenGL ES 2.0.
    See 'instructions.txt' for further information.

  scene.hh
    Defines a class representing a 3D scene that stores
    GameObjects, a level mesh and a camera.

  @author Joona Perasto, 272725, joona.perasto@tuni.fi
*/


#ifndef SCENE_HH
#define SCENE_HH

#include <QVector>
#include <QMap>
#include <QOpenGLShaderProgram>
#include <QOpenGLFunctions>
#include "camera.hh"
#include "level.hh"

// Forward declaration for contained classes
// Is this considered bad practice?
class Renderable;
class GameObject;
class FoodItem;
class Snake;

/*!
 * \brief Represents a 3D world with a camera, level and
 * a collection of GameObjects with different functions to handle them.
 */
class Scene
{
public:
    Scene();

    /*!
     * \brief Updates all GameObjects contained in Scene.
     * \param deltaTime
     */
    void update(float deltaTime);

    /*!
     * \brief Render level and all GameObjects with set camera.
     * \param gl
     */
    void render(QOpenGLFunctions* gl);

    /*!
     * \brief Adds a GameObject to the scene.
     * \param gameObject
     */
    void addGameObject(GameObject* gameObject);

    /*!
     * \brief Removes a GameObject from the scene.
     * \param object
     */
    void removeGameObject(GameObject *object);

    /*!
     * \brief Sets given camera as the active camera for the scene.
     * \param camera
     */
    void setCamera(Camera* camera);

    /*!
     * \brief Sets given level as the active level for the scene.
     * \param level
     */
    void setLevel(Level* level);

    /*!
     * \brief Checks if given vector is inside any collider in this scene.
     * \param vector
     * \return true if yes, false if no
     */
    bool isVectorInsideCollider(QVector3D vector);

    /*!
     * \brief Clear all GameObjects from the scene.
     */
    void clearGameObjects();

    /*!
     * \brief Get all FoodItems from the scene.
     * \return foodItems
     */
    const QVector<FoodItem*> getFoodItems() const;

    /*!
     * \brief Get all colliders from the scene.
     * \return colliders
     */
    const PolyData* getColliders() const;

    /*!
     * \brief Adds a random FoodItem to the scene, the most common
     * one being an apple.
     */
    void addRandomFood();

private:
    /*!
     * \brief Datastructure for holding GameObjects.
     */
    QVector<GameObject*> gameObjects_;

    Camera* camera_;
    Level* level_;
    Snake* player_;
    PolyData* colliders_;

    /*!
     * \brief Preloads all necessary resources that
     * could be contained within the scene.
     */
    void loadResources();

    /*!
     * \brief Datastructure for renderable objects, used to sort by shader
     * for efficient rendering, allows for low amount of shader changing
     */
    using RenderMap = QMap<QOpenGLShaderProgram*, QVector<Renderable*>>;
    RenderMap renderMap_;
};

#endif // SCENE_HH
