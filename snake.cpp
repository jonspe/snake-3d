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


void Snake::initRendering(QOpenGLFunctions *gl)
{
    // Initialize Vertex Buffer Object
    gl->glGenBuffers(1, &vbo_);
    gl->glBindBuffer(GL_ARRAY_BUFFER, vbo_);

    // Allocate memory for snake vertices
    gl->glBufferData(GL_ARRAY_BUFFER, 50000, nullptr, GL_DYNAMIC_DRAW);

    // Vertex positions
    gl->glEnableVertexAttribArray(0);
    gl->glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 6, reinterpret_cast<void*>(0));

    // Vertex normals
    gl->glEnableVertexAttribArray(1);
    gl->glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 6, reinterpret_cast<void*>(3));

    shaderProgram_.addShaderFromSourceCode(QOpenGLShader::Vertex,
        "attribute highp vec4 aVertex;\n"
        "attribute highp vec3 aNormal;\n"
        "uniform highp mat4 viewMatrix;\n"
        "varying mediump vec3 normal;\n"
        "varying mediump vec3 pos;\n"
        "void main(void)\n"
        "{\n"
        "   vec4 position = viewMatrix * aVertex;\n"
        "   gl_Position = position;\n"
        "   normal = aNormal;\n"
        "   pos = aVertex.xyz;\n"
        "}");
    shaderProgram_.addShaderFromSourceCode(QOpenGLShader::Fragment,
        "varying mediump vec3 normal;\n"
        "varying mediump vec3 pos;\n"
        "void main(void)\n"
        "{\n"
//        "   gl_FragColor = vec4(normal, 1.0f);\n"
        "   gl_FragColor = vec4(pos.y*1.0f, 0.6f, 0.0f, 1.0f);\n"
        "}");

    shaderProgram_.bindAttributeLocation("aVertex", 0);
    shaderProgram_.bindAttributeLocation("aNormal", 1);

    // Link shader program to OpenGL
    shaderProgram_.link();
}

void Snake::render(QOpenGLFunctions* gl, QMatrix4x4 &viewMatrix)
{
    gl->glBindBuffer(GL_ARRAY_BUFFER, vbo_);

    QVector<GLuint> indices;

    for (int i = 0; i < tail_.size()-1; ++i) {
        GLfloat data[16 * 6]; //16 vertices, xyz for position, xyz, for normal

        QVector3D v0 = tail_.at(i);
        QVector3D v1 = tail_.at(i+1);

        QVector3D norm = (v1-v0).normalized();

        for (int radial = 0; radial < 16; ++radial)
        {
            float angle = float(radial) / 16.0f * float(M_PI * 2);

            // Vertex position
            data[0 + radial*6] = v0.x() - norm.y() * cosf(angle) * 0.06f;
            data[1 + radial*6] = v0.y() + norm.x() * cosf(angle) * 0.06f;
            data[2 + radial*6] = 0.06f * sinf(angle);

            // Vertex normal
            data[3 + radial*6] = -norm.y() * cosf(angle);
            data[4 + radial*6] = norm.x() * cosf(angle);
            data[5 + radial*6] = sinf(angle);

            // Order vertex indices so that a cylinder is formed

            // First triangle of quad
            indices.push_back(GLuint(i*16 + radial));
            indices.push_back(GLuint(i*16 + (radial + 1)%16 ));
            indices.push_back(GLuint((i+1)*16 + (radial + 1)%16 ));

            // Second triangle of quad
            indices.push_back(GLuint(i*16 + radial));
            indices.push_back(GLuint((i+1)*16 + (radial + 1)%16 ));
            indices.push_back(GLuint((i+1)*16 + radial));
        }

        // Update mesh vertex data at offset
        GLintptr offset = sizeof(data) * GLuint(i);
        gl->glBufferSubData(GL_ARRAY_BUFFER, offset, sizeof(data), &data);
    }

    // Apply shader and finally draw snake
    shaderProgram_.bind();
    shaderProgram_.setUniformValue("viewMatrix", viewMatrix);

    gl->glDrawElements(GL_TRIANGLES, indices.count(),
                       GL_UNSIGNED_INT, indices.data());

    gl->glBindBuffer(GL_ARRAY_BUFFER, 0);
}
