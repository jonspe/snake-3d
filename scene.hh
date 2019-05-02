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

    void sortGameObjectsByShader();
    void setCamera(Camera* camera);
    void setLevel(Level* level);
    void setPlayer(Snake* snake);

    const QVector<FoodItem*> getFoodItems() const;

    void addRandomFood();

private:
    QVector<GameObject*> gameObjects_;
    Camera* camera_;
    Level* level_;
    Snake* player_;

    void loadResources();

    // Datastructure for renderable objects
    // Used to sort by shader for efficient rendering, allows for low amount of shader changing
    using RenderMap = QMap<QOpenGLShaderProgram*, QVector<Renderable*>>;
    RenderMap renderMap_;

};

#endif // SCENE_HH
