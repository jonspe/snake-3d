#ifndef SNAKE_HH
#define SNAKE_HH

#include <QVector>
#include <QVector3D>
#include <QOpenGLFunctions>

#include "renderable.hh"
#include "powerup.hh"

const float SNAKE_SEGMENT_DIST = 0.05f;

class Snake: public Renderable, protected QOpenGLFunctions
{
public:
    Snake(float length, float speed);
    ~Snake() override;

    void render() override;
    void initGraphics() override;

    void update(float time_delta);

    void setLength(float new_length);
    void applyPowerUp(PowerUp& power_up);
private:
    int segments_;
    float speed_;

    QVector<QVector3D> tail_;
    QVector3D position_;

    GLuint vertex_buffer_id;
};

#endif // SNAKE_HH
