#ifndef SNAKE_HH
#define SNAKE_HH

#include <QVector>
#include <QVector3D>
#include <QOpenGLFunctions_2_1>

#include "renderable.hh"
#include "powerup.hh"

const float SNAKE_SEGMENT_DIST = 0.10f;

class Snake : public Renderable
{
public:
    Snake(float length, float speed, float steer_speed);
    ~Snake() override;

    void render(QOpenGLFunctions_2_1* gl) override;

    void update(float time_delta);
    void steer(int dir);

    void setLength(float new_length);
    void applyPowerUp(PowerUp& power_up);
private:
    float speed_;
    float steer_speed_;

    float heading_;
    float steer_dir_;

    QVector<QVector3D> tail_;
    QVector3D position_;
};

#endif // SNAKE_HH
