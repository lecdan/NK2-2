#include "GameWidget.h"
#include"StartMenu.h"

#include <QApplication>
#include <ctime>
#include<QStackedWidget>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    srand(time(nullptr));

    QStackedWidget stacked;
    StartMenu *menu=new StartMenu;
    GameWidget *game=new GameWidget;
    stacked.addWidget(menu);
    stacked.addWidget(game);
    stacked.setCurrentWidget(menu);
    stacked.resize(menu->size());
    stacked.show();

    QObject::connect(menu,&StartMenu::startGame,[&](){
        game->startGame();
        stacked.setCurrentWidget(game);
        stacked.resize(game->size());
    });
    QObject::connect(game,&GameWidget::backToMenu,[&](){
        stacked.setCurrentWidget(menu);
        stacked.resize(menu->size());
    });

    return a.exec();
}
