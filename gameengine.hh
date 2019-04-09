#ifndef GAMEENGINE_HH
#define GAMEENGINE_HH

#include <QTimer>

#include "snake.hh"

class GameEngine: public QObject
{
    Q_OBJECT

public:
    GameEngine();
    void gameLoop();

    void resetSnake();

public slots:
    void update();
    void render();

private:
    Snake* snake_;
    QVector<PowerUp> powerups;
};

#endif // GAMEENGINE_HH
