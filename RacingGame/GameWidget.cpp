#include "GameWidget.h"
#include "playercar.h"
#include "enemycar.h"
#include "powerup.h"
#include "./ui_GameWidget.h"
#include<QPainter>
#include<QtMath>
#include <QFont>
#include <QFile>
#include <QTextStream>
#include<QtMinMax>

GameWidget::GameWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::GameWidget)
    ,gameRunning(true)
    ,score(0)
    ,highestScore(0)
    ,enemyFrameCounter(0)
    ,enemyFrameDelay(45)
    ,enemyBaseSpeed(3.0)
    ,slowRemainingFrames(0)
    ,holdShield(false)
    ,shieldRemainingFrames(0)
{
    setFixedSize(800, 600);
    setWindowTitle("Racing Game - SG");
    setFocusPolicy(Qt::StrongFocus);
    ui->setupUi(this);

    loadHighScore();

    player=new PlayerCar(350,500,50,80,this);

    gameRunning = true;
    score = 0;
    enemyFrameCounter = 0;
    enemyFrameDelay = 60;

    gameTimer = new QTimer(this);
    connect(gameTimer, &QTimer::timeout, this, &GameWidget::updateGame);
    gameTimer->start(1000 / 60);
    powerUpTimer = new QTimer(this);
    connect(powerUpTimer, &QTimer::timeout, this, &GameWidget::generatePowerUp);
    powerUpTimer->start(3000);
}

GameWidget::~GameWidget()
{
    delete ui;
    delete player;
    qDeleteAll(enemies);
    qDeleteAll(powerups);
}

void GameWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);

    QLinearGradient gradient(0, 0, 0, height());
    gradient.setColorAt(0, QColor(30, 30, 60));
    gradient.setColorAt(1, QColor(10, 10, 30));
    painter.fillRect(rect(), gradient);

    static int roadOffset = 0;
    roadOffset = (roadOffset + 5) % 40;

    int laneWidth = width() / 3;

    painter.setPen(QPen(Qt::white, 3));
    for (int i = 1; i < 3; ++i) {
        int x = i * laneWidth;
        painter.drawLine(x, 0, x, height());
    }

    painter.setPen(QPen(Qt::gray, 1, Qt::DashLine));
    for (int lane = 0; lane < 3; ++lane) {
        int laneLeft = lane * laneWidth;
        int laneRight = laneLeft + laneWidth;
        int startX = laneLeft + 20;
        int endX   = laneRight - 20;
        for (int y = roadOffset; y < height(); y += 40) {
            painter.drawLine(startX, y, endX, y);
        }
    }

    player->draw(&painter);

    for (EnemyCar *e : enemies) {
        e->draw(&painter);
    }

    for (PowerUp *p : powerups) {
        p->draw(&painter);
    }

    painter.setPen(Qt::white);
    QFont font("Consolas", 14);
    painter.setFont(font);
    painter.drawText(10, 30, QString("SCORE: %1").arg(score));
    painter.drawText(10, 55, QString("BEST: %1").arg(highestScore));

    painter.drawText(width() - 150, 30, QString("SPEED: %1").arg(enemyBaseSpeed, 0, 'f', 1));

    if (holdShield) {
        painter.setPen(Qt::cyan);
        painter.drawText(width() - 150, 60, "SHIELD ACTIVE");
    }
    if (slowRemainingFrames > 0) {
        painter.setPen(Qt::yellow);
        painter.drawText(width() - 150, 90, "SLOW MOTION");
    }

    if (!gameRunning) {
        painter.setPen(Qt::red);
        painter.setFont(QFont("Arial", 28));
        painter.drawText(width() / 2 - 140, height() / 2, "GAME OVER - PRESS R");
    }
}

void GameWidget::keyPressEvent(QKeyEvent *event)
{
    int step = 25;

    if (!gameRunning && event->key() == Qt::Key_R) {
        startGame();
        return;
    }

    if (!gameRunning) return;

    switch (event->key()) {
    case Qt::Key_Left:
        player->moveLeft(step);
        break;
    case Qt::Key_Right:
        player->moveRight(step, width());
        break;
    default:
        QWidget::keyPressEvent(event);
        break;
    }

    update();
}

void GameWidget::updateGame()
{
    if (!gameRunning) return;

    updateDifficulty();

    if (enemyFrameCounter <= 0) {
        generateEnemy();
        enemyFrameCounter = enemyFrameDelay;
    } else {
        enemyFrameCounter--;
    }

    float currentSpeed = enemyBaseSpeed;
    if (slowRemainingFrames > 0){
        currentSpeed = enemyBaseSpeed * 0.4;
        slowRemainingFrames--;
    }

    for (EnemyCar *e : enemies) {
        e->move(currentSpeed);
    }

    for (PowerUp *p : powerups) {
        p->move(3);
    }

     checkCollisions();

    for (int i = 0; i < enemies.size(); ++i) {
        if (enemies[i]->isOutOfScreen()) {
            delete enemies[i];
            enemies.removeAt(i);
            score += 10;
            --i;
        }
    }

    for (int i = 0; i < powerups.size(); ++i) {
        if (powerups[i]->isOutOfScreen()) {
            delete powerups[i];
            powerups.removeAt(i);
            --i;
        }
    }

    score++;

    if (score > highestScore) {
        highestScore = score;
        saveHighScore();
    }

    if (holdShield && shieldRemainingFrames > 0) {
        shieldRemainingFrames--;
        if (shieldRemainingFrames <= 0) {
            holdShield = false;
        }
    }

    update();
}

void GameWidget::updateDifficulty()
{
    int newDelay = 45 - (score / 500) * 5;
    enemyFrameDelay = qMax(15, newDelay);

    enemyBaseSpeed = 3.0 + score / 800.0;
    enemyBaseSpeed = qMin(12.0f,enemyBaseSpeed);
}

void GameWidget::generateEnemy()
{
    bool isWide = (rand() % 100 < 30);
    int laneCount = 3;
    int laneWidth = width() / laneCount;
    int carWidth = 45;
    int carHeight = 70;

    int lane = rand() % laneCount;
    int carX;

    if (isWide) {
        carX = lane * laneWidth + carWidth/ 2;
        if (carX + carWidth > width()) carX = width() - carWidth;
        if (carX < 0) carX = 0;
    } else {
        carX = lane * laneWidth + (laneWidth - carWidth) / 2;
    }

    EnemyCar *enemy = new EnemyCar(carX, -carHeight, carWidth, carHeight, enemyBaseSpeed, this);
    enemies.append(enemy);
}

void GameWidget::generatePowerUp()
{
    if (!gameRunning) return;
    int x = rand() % (width() - 30);
    int y = -30;
    int type = rand() % 2;
    PowerUp *p = new PowerUp(x, y, 30, 30,type,this);
    powerups.append(p);
}

void GameWidget::checkCollisions()
{
    QRect playerRect = player->getRect();

    for (EnemyCar *e : enemies) {
        if (playerRect.intersects(e->getRect())) {
            if (holdShield) {
                holdShield = false;
                shieldRemainingFrames = 0;
                enemies.removeOne(e);
                delete e;
                return;
            } else {
                gameOver();
                return;
            }
        }
    }

    for (int i = 0; i < powerups.size(); ++i) {
        PowerUp *p = powerups[i];
        if (playerRect.intersects(p->getRect())) {
            if (p->getType() == 0) {   // 燃油减速
                slowRemainingFrames = 120;   // 减速 2 秒 (60 FPS * 2)
            } else if (p->getType() == 1) {  // 护盾
                holdShield = true;
                shieldRemainingFrames = 180;  // 护盾持续 3 秒
            }
            delete p;
            powerups.removeAt(i);
            break;
        }
    }
}

void GameWidget::gameOver()
{
    gameRunning = false;
    gameTimer->stop();
    powerUpTimer->stop();
    update();
}

void GameWidget::startGame()
{
    qDeleteAll(enemies);
    enemies.clear();
    qDeleteAll(powerups);
    powerups.clear();

    gameRunning = true;
    score = 0;
    enemyFrameCounter = 10;
    enemyFrameDelay = 45;
    enemyBaseSpeed = 3.0;
    slowRemainingFrames = 0;
    holdShield = false;
    shieldRemainingFrames = 0;

    player->resetPosition(width());

    gameTimer->start(1000 / 60);
    powerUpTimer->start(3000);

    update();
}

void GameWidget::loadHighScore()
{
    QFile file("highestscore.txt");
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&file);
        highestScore = in.readLine().toInt();
        file.close();
    } else {
        highestScore = 0;
    }
}

void GameWidget::saveHighScore()
{
    QFile file("highestscore.txt");
    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream out(&file);
        out << highestScore;
        file.close();
    }
}