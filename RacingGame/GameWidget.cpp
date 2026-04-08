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

}

void GameWidget::keyPressEvent(QKeyEvent *event)
{
    int step = 20;

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