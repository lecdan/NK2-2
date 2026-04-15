#include "playercar.h"

PlayerCar::PlayerCar(int startX, int startY, int width, int height, QWidget *parent)
    : x(startX), y(startY), w(width), h(height), parent(parent){}

void PlayerCar::moveLeft(int step)
{
    x = qMax(0, x - step);
}

void PlayerCar::moveRight(int step, int maxX)
{
    x = qMin(maxX - w, x + step);
}

void PlayerCar::resetPosition(int windowWidth)
{
    x = (windowWidth - w) / 2;
}

void PlayerCar::draw(QPainter *painter) const
{

    QLinearGradient grad(x, y, x, y + h);
    grad.setColorAt(0, Qt::green);
    grad.setColorAt(1, Qt::darkGreen);
    painter->setBrush(grad);
    painter->setPen(Qt::black);
    painter->drawRect(x, y, w, h);
    painter->setBrush(Qt::cyan);
    painter->drawRect(x + 10, y + 10, w - 20, 20);
    painter->setBrush(Qt::yellow);
    painter->drawEllipse(x + 5, y + h - 15, 8, 8);
     painter->drawEllipse(x + w - 13, y + h - 15, 8, 8);
}

QRect PlayerCar::getRect() const
{
    return QRect(x, y, w, h);
}

