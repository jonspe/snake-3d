#include "renderable.hh"


Renderable::Renderable(): transform_(), shaderProgram_(nullptr) {
    transform_ = new Transform;
    shaderProgram_ = nullptr;
}

QOpenGLShaderProgram* Renderable::getShaderProgram()
{
    return shaderProgram_;
};

Transform* Renderable::getTransform()
{
    return transform_;
}

