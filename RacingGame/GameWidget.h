#ifndef GAMEWIDGET_H
#define GAMEWIDGET_H

#include <QWidget>
#include <QKeyEvent>
#include <QList>
#include <QRect>
#include<QTimer>

QT_BEGIN_NAMESPACE
namespace Ui {
class GameWidget;
}
QT_END_NAMESPACE

class GameWidget : public QWidget
{
    Q_OBJECT

public:
    explicit GameWidget(QWidget *parent = nullptr);
    ~GameWidget() override;

protected:
    void paintEvent(QPaintEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;

private:
    Ui::GameWidget *ui;
    int playerX;
    int playerY;
    int playerWidth;
    int playerHeight;

    struct Enemy {
        QRect rect;
        int speed;
    };
    QList<Enemy> enemies;

    bool gameRunning;
    int score;

    int enemyFrameCounter;
    int enemyFrameDelay;

    QTimer *gameTimer;

private slots:
    void updateGame();
};
#endif // GAMEWIDGET_H
