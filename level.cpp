/**
  TIE-02201 Ohjelmointi 2: Perusteet, K2019
  Assignment 12.4: Matopelin paluu
    3D Snake game made with OpenGL ES 2.0.
    See 'instructions.txt' for further information.

  level.cpp
    Defines a class for the 3D level play area.

  @author Joona Perasto, 272725, joona.perasto@tuni.fi
*/


#include "level.hh"


Level::Level()
{
    ResourceManager& resourceManager = ResourceManager::getInstance();

    shaderProgram_ = resourceManager.loadProgram("level_program");
    mesh_ = resourceManager.loadMesh("level.obj");
    texture_ = resourceManager.loadTexture("solid_color_atlas.png");
}

Level::~Level() {}

void Level::render(QOpenGLFunctions *gl)
{
    // Enable vertex attributes
    shaderProgram_->enableAttributeArray("aVertex");
    shaderProgram_->enableAttributeArray("aTexcoord");
    shaderProgram_->enableAttributeArray("aNormal");

    // Send data to vertex attributes
    shaderProgram_->setAttributeArray("aVertex", mesh_->vertexData.constData());
    shaderProgram_->setAttributeArray("aTexcoord", mesh_->texcoordData.constData());
    shaderProgram_->setAttributeArray("aNormal", mesh_->normalData.constData());

    // Bind texture for use in OpenGL
    texture_->bind();

    // Draw the level as triangles.
    gl->glDrawElements(GL_TRIANGLES, mesh_->indexData.count(),
                       GL_UNSIGNED_INT, mesh_->indexData.constData());
}
