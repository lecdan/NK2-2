#include "enemycar.h"

EnemyCar::EnemyCar(int x, int y, int width, int height, float speed, QObject *parent)
    : rect(x, y, width, height), speed(speed){}

void EnemyCar::move(float deltaY)
{
    rect.translate(0, deltaY);
}

void EnemyCar::draw(QPainter *painter) const
{
    painter->setBrush(Qt::red);
    painter->setPen(Qt::black);
    painter->drawRect(rect);
    painter->setBrush(Qt::darkGray);
    painter->drawRect(rect.x() + 5, rect.y() + 10, rect.width() - 10, 15);
}

bool EnemyCar::isOutOfScreen() const
{
    return rect.top() > 600;
}

QRect EnemyCar::getRect() const
{
    return rect;
}