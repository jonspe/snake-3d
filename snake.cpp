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
#include <math.h>

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


void Snake::initShader(QOpenGLFunctions *gl)
{
    // Initialize Vertex Buffer Object
    gl->glGenBuffers(1, &vbo_);
    gl->glBindBuffer(GL_ARRAY_BUFFER, vbo_);

    // Allocate 10000 bytes for snake vertices
    gl->glBufferData(GL_ARRAY_BUFFER, 10000, nullptr, GL_STREAM_DRAW);
    gl->glEnableVertexAttribArray(0);
    gl->glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 3, nullptr);

    // Define vertex and fragment shaders
    program_.addShaderFromSourceCode(QOpenGLShader::Vertex,
        "attribute highp vec4 vertex;\n"
        "void main(void)\n"
        "{\n"
        "   gl_Position = matrix * vertex;\n"
        "}");
    program_.addShaderFromSourceCode(QOpenGLShader::Fragment,
        "uniform mediump vec4 color;\n"
        "void main(void)\n"
        "{\n"
        "   gl_FragColor = vec4(0.0f, 1.0f, 1.0f, 1.0f);\n"
        "}");

    // Link shader program to OpenGL
    program_.link();
}

void Snake::render(QOpenGLFunctions* gl)
{
    gl->glBindBuffer(GL_ARRAY_BUFFER, vbo_);

    QVector<GLuint> indices;

    for (int i = 0; i < tail_.size()-1; ++i) {
        float data[6];

        QVector3D v0 = tail_.at(i);
        QVector3D v1 = tail_.at(i+1);

        // Give snake width
        QVector3D a = (v1-v0).normalized() * 0.03f;

        data[0] = v0.x() - a.y();
        data[1] = v0.y() + a.x();
        data[2] = v0.z();

        data[3] = v0.x() + a.y();
        data[4] = v0.y() - a.x();
        data[5] = v0.z();

        // Store vertex indices for OpenGL
        indices.push_back( GLuint(i*2) );
        indices.push_back( GLuint(i*2 + 1));

        // Update mesh vertex data at offset
        GLintptr offset = sizeof(data) * GLuint(i);
        gl->glBufferSubData(GL_ARRAY_BUFFER, offset, sizeof(data), &data);
    }

    // Apply shader and finally draw snake
    program_.bind();
    gl->glDrawElements(GL_QUAD_STRIP, indices.count(),
                       GL_UNSIGNED_INT, indices.data());
}
