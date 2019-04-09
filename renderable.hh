#ifndef RENDERABLE_HH
#define RENDERABLE_HH

class Renderable
{
public:
    virtual ~Renderable() {}
    virtual void render() = 0;
    virtual void initGraphics() = 0;
};

#endif // RENDERABLE_HH
