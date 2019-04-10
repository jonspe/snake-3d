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

    if (heading_ > PI_F)
        heading_ -= PI_F*2;
    else if (heading_ < 0)
        heading_ += PI_F*2;

    QVector3D direction = QVector3D(cosf(heading_), sinf(heading_), 0);
    position_ += direction * speed_ * time_delta;

    QVector3D prev_pos = position_;
    for (int i = 1; i < tail_.size(); ++i)
    {
        QVector3D v = tail_.at(i);
        QVector3D n = (v-prev_pos).normalized();
        tail_.replace(i, prev_pos + n*SNAKE_SEGMENT_DIST);

        prev_pos = tail_.at(i);
    }

    //steer_dir_ = 0;
}

void Snake::steer(int dir)
{
    steer_dir_ = dir;
}

void Snake::render(QOpenGLFunctions_2_1* gl)
{
    gl->glLineWidth(9.0f);
    gl->glBegin(GL_LINES);

    QVector3D last = position_;
    for (int i = 1; i < tail_.size(); ++i) {
        QVector3D v1 = last;
        QVector3D v2 = tail_.at(i);
        gl->glVertex3f(v1.x(), v1.y(), v1.z());
        gl->glVertex3f(v2.x(), v2.y(), v2.z());
        last = v2;
    }

    gl->glEnd();

    gl->glPointSize(14.0f);
    gl->glBegin(GL_POINTS);
    gl->glVertex3f(position_.x(), position_.y(), position_.z());
    gl->glEnd();
}


void Snake::setLength(float new_length)
{

}

void Snake::applyPowerUp(PowerUp& power_up)
{

}
