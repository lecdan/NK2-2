#ifndef ENEMYCAR_H
#define ENEMYCAR_H

#include <QRect>
#include <QPainter>
#include <QPixmap>

class EnemyCar
{
public:
    EnemyCar(int x, int y, int width, int height, float speed, QObject *parent);
    void move(float deltaY);
    void draw(QPainter *painter) const;
    bool isOutOfScreen() const;
    static QPixmap& commonPixmap();
    static void setCommonPixmap(const QPixmap &pix);
    QRect getRect() const;

private:
    QRect rect;
    float speed;
};

#endif // ENEMYCAR_H
