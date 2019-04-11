#include "snake.hh"

#include <QDebug>
#include <math.h>

#define PI_F 3.141592653f


Snake::Snake(float length, float speed, float steer_speed):
    speed_(speed), steer_speed_(steer_speed), steer_dir_(0)
{
    position_ = QVector3D();
    heading_ = float(PI_F/2);

    int segments = int(length/SNAKE_SEGMENT_DIST);
    for (int i = 0; i < segments; ++i)
    {
        tail_.push_back(position_ + QVector3D(0.0f, -i * SNAKE_SEGMENT_DIST, 0.0f));
    }

    qDebug() << steer_dir_;
}

Snake::~Snake()
{

}

void Snake::update(float time_delta)
{
    heading_ += steer_dir_ * steer_speed_ * time_delta;

    // Wrap the value to [0, 2PI]
    if (heading_ > PI_F)
        heading_ -= PI_F*2;
    else if (heading_ < 0)
        heading_ += PI_F*2;

    // Go forward
    QVector3D direction = getDirection();
    position_ += direction * speed_ * time_delta;

    // Calculate tail positions so that each is a set distance apart
    // Gives a really cool effect that I didn't think would happen
    QVector3D prev_pos = position_;
    for (int i = 1; i < tail_.size(); ++i)
    {
        QVector3D v = tail_.at(i);
        QVector3D n = (v-prev_pos).normalized();
        tail_.replace(i, prev_pos + n*SNAKE_SEGMENT_DIST);

        prev_pos = tail_.at(i);
    }
}

void Snake::steer(int dir)
{
    steer_dir_ = dir;
}

QVector3D Snake::getDirection()
{
    return QVector3D(cosf(heading_), sinf(heading_), 0);
}

QVector3D Snake::getPosition()
{
    return position_;
}

float Snake::getHeading()
{
    return heading_;
}

/*
float calcTailWidth(int index, int size, int length)
{

}
*/

void Snake::render(QOpenGLFunctions_2_1* gl)
{
    gl->glBegin(GL_QUAD_STRIP);

    // Calculate tail vertices
    for (int i = 2; i < tail_.size(); ++i) {
        QVector3D v0 = tail_.at(i-1);
        QVector3D v1 = tail_.at(i);

        QVector3D a = (v1-v0).normalized() * 0.03f;

        gl->glVertex3f(v0.x() - a.y(), v0.y() + a.x(), v0.z());
        gl->glVertex3f(v0.x() + a.y(), v0.y() - a.x(), v0.z());
    }

    gl->glEnd();
}

void Snake::setPosition(QVector3D pos)
{
    position_ = pos;
}

void Snake::setLength(float new_length)
{

}

void Snake::applyPowerUp(PowerUp& power_up)
{

}
