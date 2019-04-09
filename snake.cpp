#include "snake.hh"

Snake::Snake(float length, float speed): speed_(speed)
{
    position_ = QVector3D(.0f, .0f, .0f);
    segments_ = int(length/SNAKE_SEGMENT_DIST);

    tail_.push_back(position_);

    for (int i = 0; i < segments_; ++i)
    {
        tail_.push_back(position_ + QVector3D(0.0f, -i * SNAKE_SEGMENT_DIST, 0.0f));
    }
}

Snake::~Snake()
{

}

void Snake::render()
{
    int offset = 0;
    const GLsizeiptr LINE_SIZE = 6 * sizeof(GLfloat);

    for (auto it = tail_.begin(); it != tail_.end()-1; ++it)
    {
        GLfloat data[] = {
            it->x(),     it->y(),     it->z(),
            (it+1)->x(), (it+1)->y(), (it+1)->z()
        };

        glBufferSubData(GL_ARRAY_BUFFER, offset, LINE_SIZE, data);
        offset += sizeof(data);
    }

    glDrawArrays(GL_LINES, 0, offset - LINE_SIZE);
}

void Snake::initGraphics()
{
    glGenBuffers(1, &vertex_buffer_id);
    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer_id);
    glBufferData(GL_ARRAY_BUFFER, 10000, nullptr, GL_STREAM_DRAW); // allocate 10000 bytes

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
}

void Snake::setLength(float new_length)
{

}

void Snake::applyPowerUp(PowerUp& power_up)
{

}
