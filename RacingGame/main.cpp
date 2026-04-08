#include "GameWidget.h"

#include <QApplication>
#include <ctime>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    srand(time(nullptr));
    GameWidget w;
    w.show();
    return a.exec();
}
