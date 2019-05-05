/**
  TIE-02201 Ohjelmointi 2: Perusteet, K2019
  Assignment 12.4: Matopelin paluu
    3D Snake game made with OpenGL ES 2.0.
    See 'instructions.txt' for further information.

  snake.cpp
    Defines a class for the 3D snake which the user controls.

  @author Joona Perasto, 272725, joona.perasto@tuni.fi
*/


#include <QDebug>
#include <QtMath>

#include <math.h>
#include <ctime>

#include "snake.hh"
#include "resourcemanager.hh"
#include "fooditem.hh"


#define PI_F 3.141592653f


namespace {
    float bumpFunction(float x);
}


Snake::Snake(Scene* scene): GameObject (scene), steerDir_(0), heading_(0), dead_(false)
{
    properties_ = new SnakeProperties();

    // Load premade program
    ResourceManager& resourceManager = ResourceManager::getInstance();
    shaderProgram_ = resourceManager.loadProgram("snake_program");

    // Link shader program to OpenGL
    shaderProgram_->link();

    shaderProgram_->enableAttributeArray("aVertex");
    shaderProgram_->enableAttributeArray("aNormal");
    shaderProgram_->enableAttributeArray("aTail");

    initializeTail();
}

Snake::~Snake() {}

void Snake::update(float deltaTime)
{
    if (isDead())
    {
        // Meh disintegration effect
        transform_->setPosition(transform_->getPosition() + QVector3D(0, -0.07f * deltaTime, 0));
        return;
    }

    properties_->update(deltaTime);
    setTailLength(properties_->getLength());

    float steerSpeed = properties_->getSteerSpeed();
    float moveSpeed = properties_->getMoveSpeed();

    heading_ += steerDir_ * steerSpeed * deltaTime;

    QVector3D dir(-sinf(heading_), 0.0f, -cosf(heading_));

    // use headPosition in world coordinates, because snake transform should be kept default zero
    headPosition_ += dir * moveSpeed * deltaTime;

    for (FoodItem* item: scene_->getFoodItems())
    {
        if (!item->canBeEaten())
            continue;

        float dist = (item->getPosition() - headPosition_).length();

        // If within distance, eat food and spawn a new one
        if (dist < 0.14f)
        {
            eat(item);
            item->consume();
            scene_->addRandomFood();
        }
    }

    // Check for collisions
    const PolyData* colliders = scene_->getColliders();
    for (QPolygonF collider : *colliders)
    {
        QPointF playerPoint( qreal(headPosition_.x()), qreal(headPosition_.z()) );
        if (collider.containsPoint(playerPoint, Qt::FillRule::OddEvenFill))
            dead_ = true;
    }

    // Check for tail collisions, ignore the first few segments
    for (int i = 8; i < tail_.size(); ++i)
    {
        if ((headPosition_ - tail_.at(i)).lengthSquared() < 0.012f)
            dead_ = true;
    }

    processDigestItems(deltaTime);

    // Calculate tail positions so that each is a set distance apart
    // Gives a really cool effect, like rope at 1.0 friction with ground
    // Problem: if snake is long and goes around an object, it could intersect with it
    QVector3D prevPos = headPosition_;
    for (int i = 0; i < tail_.size(); ++i)
    {
        QVector3D v = tail_.at(i);
        QVector3D n = (v - prevPos).normalized();
        tail_.replace(i, prevPos + n*SNAKE_SEGMENT_DIST);

        prevPos = tail_.at(i);
    }
}

void Snake::processDigestItems(float deltaTime)
{
    for (auto it = digestPositions_.begin(); it != digestPositions_.end();)
    {
        *it += properties_->getMoveSpeed() * deltaTime;

        if (*it >= getTailLength())
        {
            digestPositions_.erase(it);
            continue;
        }

        ++it;
    }
}

void Snake::initializeTail()
{
    tail_.clear();

    int segments = int(properties_->getLength()/SNAKE_SEGMENT_DIST);
    for (int i = 0; i < segments; ++i)
        tail_.push_back(transform_->getPosition() + QVector3D(0.0f, 0.0f, i * SNAKE_SEGMENT_DIST));
}

void Snake::applyEffect(FoodEffect effect)
{
    properties_->addEffect(effect);
}

void Snake::steer(int dir)
{
    steerDir_ = dir;
}


void Snake::eat(FoodItem* item)
{
    applyEffect(item->getEffect());
    digestPositions_.append(-0.1f);
}


void Snake::render(QOpenGLFunctions* gl)
{
    QVector<QVector3D> vertexData;
    QVector<QVector3D> normalData;
    QVector<QVector3D> tailData;
    QVector<GLuint> indexData;

    int tailSize = tail_.size();

    // Generate dynamic cylindrical mesh for snake loop by loop
    for (int loop = 0; loop < tailSize-1; ++loop) {
        QVector3D v0 = tail_.at(loop);
        QVector3D v1 = tail_.at(loop+1);

        // Normalized vector towards the next part of tail
        QVector3D dir = (v1-v0).normalized();

        float bulge = 0.0f;
        float pos = loop * SNAKE_SEGMENT_DIST;

        // Calculate the sum of bumps from digestive consumable items
        for (float digestPosition : digestPositions_)
            bulge += bumpFunction((pos - digestPosition) * 8.0f);

        for (int radial = 0; radial < SNAKE_DEFINITION; ++radial)
        {
            float angle = float(radial) / float(SNAKE_DEFINITION) * float(M_PI * 2);
            float cosAngle = cosf(angle);

            // Calculate vertex normal with cross product
            float xNormal = -dir.z() * cosAngle;
            float yNormal = -sinf(angle);
            float zNormal = dir.x() * cosAngle;

            vertexData.append(v0);
            normalData.append(QVector3D(xNormal, yNormal, zNormal));
            tailData.append(QVector3D(pos, bulge, cosAngle));

            // Order vertex indices so that a cylinder is formed out of triangles
            // Could be further optimized by changing indices only when snake length is changed

            // Don't add nonexistent indices at end of tail
            if (loop == tailSize-2)
                continue;

            // First triangle of quad
            indexData.push_back(GLuint(loop*SNAKE_DEFINITION + radial));
            indexData.push_back(GLuint(loop*SNAKE_DEFINITION + (radial + 1)%SNAKE_DEFINITION ));
            indexData.push_back(GLuint((loop+1)*SNAKE_DEFINITION + (radial + 1)%SNAKE_DEFINITION ));

            // Second triangle of quad
            indexData.push_back(GLuint(loop*SNAKE_DEFINITION + radial));
            indexData.push_back(GLuint((loop+1)*SNAKE_DEFINITION + (radial + 1)%SNAKE_DEFINITION ));
            indexData.push_back(GLuint((loop+1)*SNAKE_DEFINITION + radial));
        }
    }

    shaderProgram_->setAttributeArray("aVertex", vertexData.constData());
    shaderProgram_->setAttributeArray("aNormal", normalData.constData());
    shaderProgram_->setAttributeArray("aTail", tailData.constData());

    shaderProgram_->setUniformValue("tailLength", properties_->getLength());
    shaderProgram_->setUniformValue("tailThickness", properties_->getThickness());

    // Finally draw the snake as triangles
    gl->glDrawElements(GL_TRIANGLES, indexData.count(),
                       GL_UNSIGNED_INT, indexData.constData());
}

bool Snake::isDead()
{
    return dead_;
}

float Snake::getTailLength()
{
    return tail_.size() * SNAKE_SEGMENT_DIST;
}

void Snake::setTailLength(float length)
{
    int prevSegments = int(getTailLength()/SNAKE_SEGMENT_DIST);
    int newSegments = int(length/SNAKE_SEGMENT_DIST);

    if (newSegments > prevSegments)
    {
        // Get direction from second last to last for proper segment insertion
        QVector3D tailEnd = tail_.last();
        QVector3D dir = ( *(tail_.end()-1) - *(tail_.end()-2) ).normalized();
        tail_.resize(newSegments);

        for (int i=prevSegments; i<newSegments; ++i)
            tail_.replace(i, tailEnd += dir * (i-prevSegments) * SNAKE_SEGMENT_DIST);

    } else {
        tail_.resize(newSegments);
    }
}

SnakeProperties* Snake::getProperties()
{
    return properties_;
}

float Snake::getHeading()
{
    return heading_;
}

QVector3D Snake::getHeadPosition()
{
    return headPosition_;
}

namespace {
    float bumpFunction(float x)
    {
        if (abs(x) > 1)
            return 0.0f;

        float xm = x-1;
        float xp = x+1;
        return xm*xm*xp*xp;
    }
}
