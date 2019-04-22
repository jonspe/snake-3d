#include "renderable.hh"


QOpenGLShaderProgram* Renderable::getShaderProgram()
{
    return shaderProgram_;
};

QMatrix4x4 Renderable::getModelTransform()
{
    return modelTransform_;
}
