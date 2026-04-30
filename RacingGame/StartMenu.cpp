#include "StartMenu.h"
#include "ui_StartMenu.h"
#include<QFile>

StartMenu::StartMenu(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::StartMenu)
{
    ui->setupUi(this);
    connect(ui->startButton,&QPushButton::clicked,this,&StartMenu::startGame);
    connect(ui->exitButton,&QPushButton::clicked,this,&QApplication::quit);

    QFile file("highestscore.txt");
    if(file.open(QIODevice::ReadOnly)){
        int high=file.readLine().toInt();
        ui->highscoreLabel->setText(QString("最高分：%1").arg(high));
        file.close();
    }
}

StartMenu::~StartMenu()
{
    delete ui;
}
