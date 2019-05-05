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

class Renderable;
class GameObject;
class FoodItem;
class Snake;

class Scene
{
public:
    Scene();

    void update(float deltaTime);
    void render(QOpenGLFunctions* gl);

    void addGameObject(GameObject* gameObject);
    void removeGameObject(GameObject *object);

    void setCamera(Camera* camera);
    void setLevel(Level* level);

    bool isVectorInsideCollider(QVector3D vector);

    void clear();

    const QVector<FoodItem*> getFoodItems() const;
    const PolyData* getColliders() const;

    void addRandomFood();

private:
    QVector<GameObject*> gameObjects_;
    Camera* camera_;
    Level* level_;
    Snake* player_;
    PolyData* colliders_;

    void loadResources();

    // Datastructure for renderable objects
    // Used to sort by shader for efficient rendering, allows for low amount of shader changing
    using RenderMap = QMap<QOpenGLShaderProgram*, QVector<Renderable*>>;
    RenderMap renderMap_;

};

#endif // SCENE_HH
