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

    void setupUi(QWidget *StartMenu)
    {
        if (StartMenu->objectName().isEmpty())
            StartMenu->setObjectName("StartMenu");
        StartMenu->resize(800, 600);
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

        verticalLayout->addWidget(startButton);

        exitButton = new QPushButton(layoutWidget);
        exitButton->setObjectName("exitButton");
        exitButton->setFont(font1);

        verticalLayout->addWidget(exitButton);


        retranslateUi(StartMenu);

        QMetaObject::connectSlotsByName(StartMenu);
    } // setupUi

    void retranslateUi(QWidget *StartMenu)
    {
        StartMenu->setWindowTitle(QCoreApplication::translate("StartMenu", "Form", nullptr));
        highscoreLabel->setText(QString());
        mainLabel->setText(QCoreApplication::translate("StartMenu", "\350\265\233\350\275\246\345\277\253\350\267\221", nullptr));
        startButton->setText(QCoreApplication::translate("StartMenu", "\345\274\200\345\247\213\346\270\270\346\210\217", nullptr));
        exitButton->setText(QCoreApplication::translate("StartMenu", "\351\200\200\345\207\272\346\270\270\346\210\217", nullptr));
    } // retranslateUi

};

namespace Ui {
    class StartMenu: public Ui_StartMenu {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_STARTMENU_H
