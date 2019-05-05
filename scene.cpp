/**
  TIE-02201 Ohjelmointi 2: Perusteet, K2019
  Assignment 12.4: Matopelin paluu
    3D Snake game made with OpenGL ES 2.0.
    See 'instructions.txt' for further information.

  scene.cpp
    Defines a class representing a 3D scene that stores
    GameObjects, a level mesh and a camera.

  @author Joona Perasto, 272725, joona.perasto@tuni.fi
*/


#include "scene.hh"

#include "renderable.hh"
#include "gameobject.hh"
#include "fooditem.hh"
#include "level.hh"
#include "snake.hh"

Scene::Scene(): camera_(nullptr), colliders_(nullptr)
{
    loadResources();
}

void Scene::update(float deltaTime)
{
    for (GameObject* object : gameObjects_)
        object->update(deltaTime);
}

void Scene::render(QOpenGLFunctions* gl)
{
    // Cant render without camera
    if (camera_ == nullptr)
        return;

    // Sort game objects by shader in advance for efficiency
    // Happens every frame so could be done more efficient, but this makes stuff a lot easier
    renderMap_.clear();
    for (Renderable* renderable : gameObjects_)
    {
        QOpenGLShaderProgram* program = renderable->getShaderProgram();
        renderMap_[program].append(renderable);
    }

    // Add the level to render queue
    renderMap_[level_->getShaderProgram()].append(level_);

    QVector3D lightDir = QVector3D(0.7f, 0.7f, 0.7f).normalized();

    // Loop through map sorted by shader programs
    for (QOpenGLShaderProgram* program : renderMap_.keys())
    {
        // Set object's shader program in OpenGL
        program->bind();

        // Send ambient lighting value to shader program
        program->setUniformValue("ambient", 0.7f);

        for (Renderable* renderable : renderMap_[program])
        {
            // Calculate transformation matrices for object
            QMatrix4x4 modelMatrix = renderable->getTransform()->getModelMatrix();
            QMatrix4x4 mvpMatrix = camera_->computeMvpMatrix(modelMatrix);
            QVector3D eyeLightDir = lightDir;

            // Send matrices and light direction to the program
            program->setUniformValue("mvpMatrix", mvpMatrix);
            program->setUniformValue("modelMatrix", modelMatrix);
            program->setUniformValue("eyeLightDir", eyeLightDir);

            renderable->render(gl);
        }

        // Unbind the shader program from OpenGL
        program->release();
    }
}

void Scene::addGameObject(GameObject *gameObject)
{
    gameObjects_.append(gameObject);
}

void Scene::removeGameObject(GameObject *object)
{
    int objIndex = gameObjects_.indexOf(object);

    if (objIndex != -1)
        gameObjects_.remove(objIndex);
}

void Scene::setCamera(Camera *camera)
{
    camera_ = camera;
}

void Scene::setLevel(Level *level)
{
    level_ = level;
}

bool Scene::isVectorInsideCollider(QVector3D vector)
{
    // Convert to 2D Point
    QPointF vectorPoint(
        qreal(vector.x()),
        qreal(vector.z())
    );

    for (QPolygonF collider : *colliders_)
        if (collider.containsPoint(vectorPoint, Qt::FillRule::OddEvenFill))
            return true;

    return false;
}

void Scene::clear()
{
    gameObjects_.clear();
}

const QVector<FoodItem*> Scene::getFoodItems() const
{
    QVector<FoodItem*> items;
    for (GameObject* obj : gameObjects_)
    {
        FoodItem* item = dynamic_cast<FoodItem*>(obj);
        if (item != nullptr)
            items.append(item);
    }

    return items;
}

const PolyData* Scene::getColliders() const
{
    return colliders_;
}

void Scene::addRandomFood()
{
    FoodItem* food = nullptr;
    int r = rand() % 21;
    if (r <= 16)
        food = new FoodItem(this, "apple");
    else if (r <= 18)
        food = new FoodItem(this, "burger");
    else
        food = new FoodItem(this, "odens");

    // Make sure that the food doesn't get spawned inside a collider
    bool insideCollider = true;
    QVector3D foodPos;

    while (insideCollider)
    {
        foodPos = QVector3D(
            rand()%1000 / 1000.0f * 20.0f-10.0f,
            0.0f,
            rand()%1000 / 1000.0f * 20.0f-10.0f
        );

        insideCollider = isVectorInsideCollider(foodPos);
    }

    food->setPosition(foodPos);
    addGameObject(food);
}

void Scene::loadResources()
{
    // Create single instance for a resource manager
    ResourceManager& resourceManager = ResourceManager::getInstance();

    // Load necessary resources at the beginning instead of during runtime to prevent hiccups
    resourceManager.createProgram("snake_program",
                                  "snake_vertex.glsl",
                                  "snake_fragment.glsl");

    resourceManager.createProgram("food_program",
                                  "basic_vertex.glsl",
                                  "food_fragment.glsl");

    resourceManager.createProgram("level_program",
                                  "basic_vertex.glsl",
                                  "level_fragment.glsl");

    resourceManager.loadMesh("apple_mesh.obj");
    resourceManager.loadMesh("burger_mesh.obj");
    resourceManager.loadMesh("dens_mesh.obj");
    resourceManager.loadMesh("level.obj");

    resourceManager.loadTexture("solid_color_atlas.png");
    resourceManager.loadTexture("odens_tex.png");

    colliders_ = resourceManager.loadPolygons("poly_colliders.obj");
}
