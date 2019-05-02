#include "scene.hh"

#include "renderable.hh"
#include "gameobject.hh"
#include "fooditem.hh"
#include "level.hh"
#include "snake.hh"

Scene::Scene(): camera_(nullptr)
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

    // Speed effect
    if (player_ != nullptr)
    {
        float speed = player_->getProperties()->getMoveSpeed();
        camera_->setFieldOfView(55.0f + speed * 10.0f);
    }

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
    qDebug() << gameObject;
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

void Scene::setPlayer(Snake *snake)
{
    player_ = snake;
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

void Scene::addRandomFood()
{
    FoodItem* food = nullptr;
    int r = rand() % 10;
    if (r <= 4)
        food = new FoodItem(this, "apple");
    else if (r <= 7)
        food = new FoodItem(this, "burger");
    else
        food = new FoodItem(this, "odens");

    food->setPosition(
                QVector3D(rand()%1000 / 1000.0f * 10.0f-5.0f, 0.0f, rand()%1000 / 1000.0f * 10.0f-5.0f));

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
    resourceManager.loadMesh("dens_mesh.obj");
    resourceManager.loadMesh("level.obj");

    resourceManager.loadTexture("apple_tex_stylized.png");
    resourceManager.loadTexture("odens_tex.png");
    resourceManager.loadTexture("level_tex.png");
}
