#include "GameWidget.h"
#include "./ui_GameWidget.h"
#include<QPainter>
#include<QtMath>

GameWidget::GameWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::GameWidget)
{
    setFixedSize(800, 600);
    setWindowTitle("Racing Game - FG");
    setFocusPolicy(Qt::StrongFocus);
    ui->setupUi(this);

    playerWidth = 50;
    playerHeight = 80;
    playerX = (width() - playerWidth) / 2;
    playerY = height() - playerHeight - 20;

    gameRunning = true;
    score = 0;
    enemyFrameCounter = 0;
    enemyFrameDelay = 60;

    gameTimer = new QTimer(this);
    connect(gameTimer, &QTimer::timeout, this, &GameWidget::updateGame);
    gameTimer->start(1000 / 60);
}

GameWidget::~GameWidget()
{
    delete ui;
}

void GameWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);

    painter.fillRect(rect(), Qt::darkGray);
    painter.setPen(Qt::white);
    painter.setBrush(Qt::NoBrush);
    int laneWidth = width() / 3;
    for (int i = 1; i < 3; ++i) {
        int x = i * laneWidth;
        painter.drawLine(x, 0, x, height());
    }

    painter.setBrush(Qt::green);
    painter.setPen(Qt::black);
    painter.drawRect(playerX, playerY, playerWidth, playerHeight);

    painter.setBrush(Qt::red);
    for (const Enemy &e : enemies) {
        painter.drawRect(e.rect);
    }

    painter.setPen(Qt::white);
    QFont font("Sligoil", 16);
    painter.setFont(font);
    painter.drawText(10, 30, QString("Score: %1").arg(score));

    if (!gameRunning) {
        painter.setPen(Qt::red);
        painter.setFont(QFont("Sligoil", 24));
        painter.drawText(width()/2 - 100, height()/2, "GAME OVER - Press R");
    }
}

void GameWidget::keyPressEvent(QKeyEvent *event)
{
    int step = 20;

    if (!gameRunning && event->key() == Qt::Key_R) {
        gameRunning = true;
        score = 0;
        enemies.clear();
        playerX = (width() - playerWidth) / 2;
        enemyFrameCounter = 0;
        update();
        return;
    }

    if (!gameRunning) return;

    switch (event->key()) {
    case Qt::Key_Left:
        playerX = qMax(0, playerX - step);
        break;
    case Qt::Key_Right:
        playerX = qMin(width() - playerWidth, playerX + step);
        break;
    default:
        QWidget::keyPressEvent(event);
        return;
    }

    update();
}

void GameWidget::updateGame()
{
    if (!gameRunning) return;

    if (enemyFrameCounter <= 0) {
        int lane = rand() % 3;
        int laneWidth = width() / 3;
        int enemyWidth = 45;
        int enemyHeight = 70;
        int enemyX = lane * laneWidth + (laneWidth - enemyWidth) / 2;
        Enemy e;
        e.rect = QRect(enemyX, -enemyHeight, enemyWidth, enemyHeight);
        e.speed = 5;
        enemies.append(e);

        enemyFrameCounter = 40 + (rand() % 40);
    } else {
        enemyFrameCounter--;
    }

    for (Enemy &e : enemies) {
        e.rect.translate(0, e.speed);
    }

    QRect playerRect(playerX, playerY, playerWidth, playerHeight);
    for (const Enemy &e : enemies) {
        if (playerRect.intersects(e.rect)) {
            gameRunning = false;
            update();
            return;
        }
    }

    for (int i = 0; i < enemies.size(); ++i) {
        if (enemies[i].rect.top() > height()) {
            enemies.removeAt(i);
            score += 10;
            --i;
        }
    }

    score++;

    update();
}