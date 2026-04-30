#ifndef PLAYERCAR_H
#define PLAYERCAR_H

#include <QWidget>
#include <QRect>
#include <QPainter>
#include <QPixmap>

class PlayerCar
{
public:
    PlayerCar(int startX, int startY, int width, int height, QWidget *parent);
    void moveLeft(int step);
    void moveRight(int step, int maxX);
    void resetPosition(int windowWidth);
    void draw(QPainter *painter) const;
    void setPixmap(const QPixmap &pix);
    QRect getRect() const;

private:
    int x, y, w, h;
    QWidget *parent;
    QPixmap pixmap;
};

#endif // PLAYERCAR_H
