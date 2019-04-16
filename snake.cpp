/**
  TIE-02201 Ohjelmointi 2: Perusteet, K2019
  Assignment 12.4: Matopelin paluu
    3D Snake game made with OpenGL 2.1 immediate mode.
    See 'instructions.txt' for further information.

  snake.cpp
    Defines a class for the snake which the user controls.

  @author Joona Perasto, 272725, joona.perasto@tuni.fi
*/


#include <QDebug>
#include <QtMath>

#include <math.h>
#include <ctime>

#include "snake.hh"
#include "resourcemanager.hh"


#define PI_F 3.141592653f


Snake::Snake(float length, float speed, float steerSpeed): GameObject (),
    moveSpeed_(speed), steerSpeed_(steerSpeed), steerDir_(0)
{
    int segments = int(length/SNAKE_SEGMENT_DIST);
    for (int i = 0; i < segments; ++i)
    {
        tail_.push_back(getPosition() + QVector3D(0.0f, -i * SNAKE_SEGMENT_DIST, 0.0f));
    }
}

Snake::~Snake() {}

void Snake::update(float timeDelta)
{
    // Multiply by move_speed_ to ensure same turning radius across speeds
    float headingIncrement = steerDir_ * steerSpeed_ * moveSpeed_ * timeDelta;

    setSpeed(moveSpeed_);
    setHeading(getHeading() + headingIncrement);
    position_ += velocity_ * timeDelta;

    // Calculate tail positions so that each is a set distance apart
    // Gives a really cool effect, like rope at 1.0 friction with ground
    QVector3D prevPos = position_;
    for (int i = 0; i < tail_.size(); ++i)
    {
        QVector3D v = tail_.at(i);
        QVector3D n = (v - prevPos).normalized();
        tail_.replace(i, prevPos + n*SNAKE_SEGMENT_DIST);

        prevPos = tail_.at(i);
    }
}

void Snake::steer(int dir)
{
    steerDir_ = dir;
}


void Snake::loadShaders(ResourceManager* resourceManager)
{
    // Create unique program from vertex and fragment shaders
    shaderProgram_ = resourceManager->createProgram("snake_program",
                                                    "snake_vertex.glsl",
                                                    "snake_fragment.glsl");

    // Link shader program to OpenGL
    shaderProgram_->link();

    shaderProgram_->setAttributeBuffer("aVertex", GL_FLOAT, 0, 3);
    shaderProgram_->setAttributeBuffer("aNormal", GL_FLOAT, 0, 3);
    shaderProgram_->setAttributeBuffer("aTail", GL_FLOAT, 0, 3);

    shaderProgram_->enableAttributeArray("aVertex");
    shaderProgram_->enableAttributeArray("aNormal");
    shaderProgram_->enableAttributeArray("aTail");
}

void Snake::render(QOpenGLFunctions* gl, QMatrix4x4 &mvpMatrix)
{
    QVector<GLfloat> vertexData;
    QVector<GLfloat> normalData;
    QVector<GLfloat> tailData;
    QVector<GLuint> indexData;

    int tailSize = tail_.size();

    // Generate dynamic cylindrical mesh for snake
    for (int loop = 0; loop < tailSize-1; ++loop) {
        QVector3D v0 = tail_.at(loop);
        QVector3D v1 = tail_.at(loop+1);

        // Normalized vector towards the next part of tail
        QVector3D norm = (v1-v0).normalized();

        for (int radial = 0; radial < SNAKE_DEFINITION; ++radial)
        {
            float angle = float(radial) / float(SNAKE_DEFINITION) * float(M_PI * 2);
            float cosAngle = cosf(angle);

            float xNormal = -norm.y() * cosAngle;
            float yNormal = norm.x() * cosAngle;
            float zNormal = sinf(angle);

            // Vertex position
            vertexData.push_back(v0.x());
            vertexData.push_back(v0.y());
            vertexData.push_back(0.0f);

            // Vertex normals
            normalData.push_back(xNormal);
            normalData.push_back(yNormal);
            normalData.push_back(zNormal);

            float pos = loop * SNAKE_SEGMENT_DIST;

            // Tail data (relative position from head)
            tailData.push_back(pos); // tail position
            tailData.push_back(0.0f); // bulge (variable for eating food)
            tailData.push_back(cosAngle); // tba

            // Order vertex indices so that a cylinder is formed out of triangles

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

    // Bind shader to OpenGL
    shaderProgram_->bind();

//    // Enable vertex and normal arrays and insert data to buffers
//    shaderProgram_.enableAttributeArray("aVertex");
//    shaderProgram_.enableAttributeArray("aNormal");
//    shaderProgram_.enableAttributeArray("aTail");

    shaderProgram_->setAttributeArray("aVertex", vertexData.constData(), 3);
    shaderProgram_->setAttributeArray("aNormal", normalData.constData(), 3);
    shaderProgram_->setAttributeArray("aTail", tailData.constData(), 3);

    shaderProgram_->setUniformValue("mvpMatrix", mvpMatrix);
    shaderProgram_->setUniformValue("tailLength", SNAKE_SEGMENT_DIST * tailSize);

    // Finally draw the snake as triangles
    gl->glDrawElements(GL_TRIANGLES, indexData.count(),
                       GL_UNSIGNED_INT, indexData.constData());

//    shaderProgram_.disableAttributeArray("aVertex");
//    shaderProgram_.disableAttributeArray("aNormal");
//    shaderProgram_.disableAttributeArray("aTail");
}
