#ifndef POWERUP_H
#define POWERUP_H

#include <QRect>
#include <QPainter>

class PowerUp
{
public:
    PowerUp(int x, int y, int width, int height, int type,QObject *parent);
    void move(int speed);
    void draw(QPainter *painter) const;
    bool isOutOfScreen() const;
    QRect getRect() const;
    int getType() const { return type; }

private:
    QRect rect;
    int type;
    int speed;
};

#endif // POWERUP_H
