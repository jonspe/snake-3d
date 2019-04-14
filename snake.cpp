/**
  TIE-02201 Ohjelmointi 2: Perusteet, K2019
  Assignment 12.4: Matopelin paluu
    3D Snake game made with OpenGL 2.1 immediate mode.
    See 'instructions.txt' for further information.

  snake.cpp
    Defines a class for the snake which the user controls.

  @author Joona Perasto, 272725, joona.perasto@tuni.fi
*/


#include "snake.hh"

#include <QDebug>
#include <QtMath>

#include <math.h>
#include <ctime>

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


void Snake::initShaders()
{
    shaderProgram_.addShaderFromSourceCode(QOpenGLShader::Vertex,
        "attribute highp vec4 aVertex;\n"
        "attribute highp vec4 aNormal;\n"
        "uniform highp mat4 viewMatrix;\n"
        "varying highp vec4 normal;\n"
        "void main(void)\n"
        "{\n"
        "   gl_Position = viewMatrix * aVertex;\n"
        "   normal = aNormal;\n"
        "}");
    shaderProgram_.addShaderFromSourceCode(QOpenGLShader::Fragment,
        "varying highp vec4 normal;\n"
        "void main(void)\n"
        "{\n"
        "   gl_FragColor = vec4(normal.xyz, 1.0f);\n"
        "}");

    shaderProgram_.bindAttributeLocation("aVertex", 0);
    shaderProgram_.bindAttributeLocation("aNormal", 1);

    shaderProgram_.enableAttributeArray(0);
    shaderProgram_.enableAttributeArray(1);
    shaderProgram_.setAttributeBuffer(0, GL_FLOAT, 0, 3);
    shaderProgram_.setAttributeBuffer(1, GL_FLOAT, 0, 3);

    // Link shader program to OpenGL
    shaderProgram_.link();
}

void Snake::render(QOpenGLFunctions* gl, QMatrix4x4 &viewMatrix)
{
    QVector<GLfloat> vertexData;
    QVector<GLfloat> normalData;
    QVector<GLuint> indexData;

    for (int loop = 0; loop < tail_.size()-1; ++loop) {
        QVector3D v0 = tail_.at(loop);
        QVector3D v1 = tail_.at(loop+1);

        // Normalized vector towards the next part of tail
        QVector3D norm = (v1-v0).normalized();

        for (int radial = 0; radial < 16; ++radial)
        {
            float angle = float(radial) / 16.0f * float(M_PI * 2);

            // Vertex position
            vertexData.push_back(v0.x() - norm.y() * cosf(angle) * 0.03f);
            vertexData.push_back(v0.y() + norm.x() * cosf(angle) * 0.03f);
            vertexData.push_back(0.03f * sinf(angle));

            // Vertex normal
            normalData.push_back(-norm.y() * cosf(angle));
            normalData.push_back(norm.x() * cosf(angle));
            normalData.push_back(sinf(angle));

            // Order vertex indices so that a cylinder is formed out of triangles

            // Don't add nonexistent indices at end of tail
            if (loop == tail_.size()-2)
                continue;

            // First triangle of quad
            indexData.push_back(GLuint(loop*16 + radial));
            indexData.push_back(GLuint(loop*16 + (radial + 1)%16 ));
            indexData.push_back(GLuint((loop+1)*16 + (radial + 1)%16 ));

            // Second triangle of quad
            indexData.push_back(GLuint(loop*16 + radial));
            indexData.push_back(GLuint((loop+1)*16 + (radial + 1)%16 ));
            indexData.push_back(GLuint((loop+1)*16 + radial));
        }
    }

    // Bind shader to OpenGL
    shaderProgram_.bind();

    // Enable vertex and normal arrays and insert data to buffers
    shaderProgram_.enableAttributeArray(0);
    shaderProgram_.enableAttributeArray(1);
    shaderProgram_.setAttributeArray(0, vertexData.constData(), 3);
    shaderProgram_.setAttributeArray(1, normalData.constData(), 3);

    shaderProgram_.setUniformValue("viewMatrix", viewMatrix);

    // Finally draw the snake as triangles
    gl->glDrawElements(GL_TRIANGLES, indexData.count(),
                       GL_UNSIGNED_INT, indexData.constData());

    shaderProgram_.disableAttributeArray(0);
    shaderProgram_.disableAttributeArray(1);
}
