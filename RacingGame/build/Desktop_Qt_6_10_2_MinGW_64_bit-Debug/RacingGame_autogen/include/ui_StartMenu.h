/********************************************************************************
** Form generated from reading UI file 'StartMenu.ui'
**
** Created by: Qt User Interface Compiler version 6.10.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_STARTMENU_H
#define UI_STARTMENU_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_StartMenu
{
public:
    QLabel *highscoreLabel;
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout;
    QLabel *mainLabel;
    QPushButton *startButton;
    QPushButton *exitButton;
    QLabel *menuLabel;

    void setupUi(QWidget *StartMenu)
    {
        if (StartMenu->objectName().isEmpty())
            StartMenu->setObjectName("StartMenu");
        StartMenu->resize(800, 600);
        StartMenu->setStyleSheet(QString::fromUtf8(""));
        highscoreLabel = new QLabel(StartMenu);
        highscoreLabel->setObjectName("highscoreLabel");
        highscoreLabel->setGeometry(QRect(520, 540, 241, 47));
        layoutWidget = new QWidget(StartMenu);
        layoutWidget->setObjectName("layoutWidget");
        layoutWidget->setGeometry(QRect(50, 40, 701, 481));
        verticalLayout = new QVBoxLayout(layoutWidget);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        mainLabel = new QLabel(layoutWidget);
        mainLabel->setObjectName("mainLabel");
        QFont font;
        font.setPointSize(25);
        mainLabel->setFont(font);
        mainLabel->setAlignment(Qt::AlignmentFlag::AlignCenter);

        verticalLayout->addWidget(mainLabel);

        startButton = new QPushButton(layoutWidget);
        startButton->setObjectName("startButton");
        QFont font1;
        font1.setPointSize(20);
        startButton->setFont(font1);
        startButton->setAutoDefault(true);
        startButton->setFlat(false);

        verticalLayout->addWidget(startButton);

        exitButton = new QPushButton(layoutWidget);
        exitButton->setObjectName("exitButton");
        exitButton->setFont(font1);
        exitButton->setAutoDefault(true);
        exitButton->setFlat(false);

        verticalLayout->addWidget(exitButton);

        menuLabel = new QLabel(StartMenu);
        menuLabel->setObjectName("menuLabel");
        menuLabel->setGeometry(QRect(0, 0, 800, 600));
        menuLabel->setPixmap(QPixmap(QString::fromUtf8(":/images/menu.png")));
        menuLabel->setScaledContents(true);
        menuLabel->raise();
        highscoreLabel->raise();
        layoutWidget->raise();

        retranslateUi(StartMenu);

        startButton->setDefault(false);


        QMetaObject::connectSlotsByName(StartMenu);
    } // setupUi

    void retranslateUi(QWidget *StartMenu)
    {
        StartMenu->setWindowTitle(QCoreApplication::translate("StartMenu", "Form", nullptr));
        highscoreLabel->setText(QString());
        mainLabel->setText(QCoreApplication::translate("StartMenu", "<html><head/><body><p><span style=\" font-size:18pt; font-weight:700; color:#00ff7f;\">\350\272\262\351\201\277\346\225\214\350\275\246\357\274\214\350\216\267\345\276\227\345\274\272\345\212\233\351\201\223\345\205\267\357\274\201</span></p></body></html>", nullptr));
        startButton->setText(QCoreApplication::translate("StartMenu", "\345\274\200\345\247\213\346\270\270\346\210\217", nullptr));
        exitButton->setText(QCoreApplication::translate("StartMenu", "\351\200\200\345\207\272\346\270\270\346\210\217", nullptr));
        menuLabel->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class StartMenu: public Ui_StartMenu {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_STARTMENU_H
