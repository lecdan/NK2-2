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
    if (!pixmap.isNull()) {
        painter->drawPixmap(x, y, w, h, pixmap);
    } 
}

QRect PlayerCar::getRect() const
{
    return QRect(x, y, w, h);
}

void PlayerCar::setPixmap(const QPixmap &pix) {
    pixmap = pix;
}
