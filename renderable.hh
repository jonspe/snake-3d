#ifndef RENDERABLE_HH
#define RENDERABLE_HH

#include <QOpenGLFunctions_2_1>
#include <QVector3D>

class Renderable
{
public:
    virtual ~Renderable() {}
    virtual void render(QOpenGLFunctions_2_1* gl) = 0;
};

#endif // RENDERABLE_HH
