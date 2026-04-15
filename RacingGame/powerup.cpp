#include "powerup.h"

PowerUp::PowerUp(int x, int y, int width, int height, int type, QObject *parent)
    : rect(x, y, width, height), type(type), speed(3) {}

void PowerUp::move(int spd)
{
    rect.translate(0, spd);
}

void PowerUp::draw(QPainter *painter) const
{
    if (type == 0) {
        painter->setBrush(Qt::yellow);
        painter->setPen(Qt::darkYellow);
        painter->drawEllipse(rect);
        painter->drawText(rect, Qt::AlignCenter, "⛽");
    } else {
        painter->setBrush(Qt::cyan);
        painter->setPen(Qt::blue);
        painter->drawEllipse(rect);
        painter->drawText(rect, Qt::AlignCenter, "🛡");
    }
}

bool PowerUp::isOutOfScreen() const
{
    return rect.top() > 600;
}

QRect PowerUp::getRect() const
{
    return rect;
}