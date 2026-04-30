#ifndef GAMEWIDGET_H
#define GAMEWIDGET_H

#include <QWidget>
#include <QKeyEvent>
#include <QList>
#include <QRect>
#include<QTimer>

class PlayerCar;
class EnemyCar;
class PowerUp;

QT_BEGIN_NAMESPACE
namespace Ui {
class GameWidget;
}
QT_END_NAMESPACE

class GameWidget : public QWidget
{
    Q_OBJECT

signals:
    void backToMenu();

public:
    explicit GameWidget(QWidget *parent = nullptr);
    ~GameWidget() override;
    void startGame();

protected:
    void paintEvent(QPaintEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;

private:
    Ui::GameWidget *ui;

    PlayerCar *player;
    QList<EnemyCar*> enemies;
    QList<PowerUp*> powerups;

    void gameOver();
    void generateEnemy();
    void generatePowerUp();
    void checkCollisions();
    void updateDifficulty();
    void loadHighScore();
    void saveHighScore();

    bool gameRunning;
    int score;
    int highestScore;

    int enemyFrameCounter;
    int enemyFrameDelay;
    float enemyBaseSpeed;

    int slowRemainingFrames;
    bool holdShield;
    int shieldRemainingFrames;

    QTimer *gameTimer;
    QTimer *powerUpTimer;

private slots:
    void updateGame();
};
#endif // GAMEWIDGET_H
