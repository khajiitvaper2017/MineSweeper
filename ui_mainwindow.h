/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.1.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLCDNumber>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "clickablelabel.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *menu_layout;
    QVBoxLayout *verticalLayout_2;
    QLCDNumber *label_mines;
    QLCDNumber *label_time;
    QVBoxLayout *game_buttons;
    QRadioButton *difficulty_1;
    QRadioButton *difficulty_2;
    QRadioButton *difficulty_3;
    QHBoxLayout *custom;
    QRadioButton *difficulty_custom;
    QVBoxLayout *counts;
    QSpinBox *x_count;
    QSpinBox *y_count;
    QSpinBox *mines_count;
    QPushButton *button_game;
    ClickableLabel *game_map;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(560, 560);
        MainWindow->setMaximumSize(QSize(1000, 1000));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        menu_layout = new QHBoxLayout();
        menu_layout->setObjectName(QString::fromUtf8("menu_layout"));
        menu_layout->setSizeConstraint(QLayout::SetDefaultConstraint);
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        label_mines = new QLCDNumber(centralwidget);
        label_mines->setObjectName(QString::fromUtf8("label_mines"));
        label_mines->setMaximumSize(QSize(200, 100));

        verticalLayout_2->addWidget(label_mines);

        label_time = new QLCDNumber(centralwidget);
        label_time->setObjectName(QString::fromUtf8("label_time"));
        label_time->setMaximumSize(QSize(200, 100));
        label_time->setSegmentStyle(QLCDNumber::Flat);

        verticalLayout_2->addWidget(label_time);


        menu_layout->addLayout(verticalLayout_2);

        game_buttons = new QVBoxLayout();
        game_buttons->setObjectName(QString::fromUtf8("game_buttons"));
        difficulty_1 = new QRadioButton(centralwidget);
        difficulty_1->setObjectName(QString::fromUtf8("difficulty_1"));
        difficulty_1->setMaximumSize(QSize(200, 20));

        game_buttons->addWidget(difficulty_1, 0, Qt::AlignHCenter);

        difficulty_2 = new QRadioButton(centralwidget);
        difficulty_2->setObjectName(QString::fromUtf8("difficulty_2"));
        difficulty_2->setMaximumSize(QSize(200, 20));
        difficulty_2->setChecked(true);

        game_buttons->addWidget(difficulty_2, 0, Qt::AlignHCenter);

        difficulty_3 = new QRadioButton(centralwidget);
        difficulty_3->setObjectName(QString::fromUtf8("difficulty_3"));
        difficulty_3->setMaximumSize(QSize(200, 20));

        game_buttons->addWidget(difficulty_3, 0, Qt::AlignHCenter);

        custom = new QHBoxLayout();
        custom->setObjectName(QString::fromUtf8("custom"));
        difficulty_custom = new QRadioButton(centralwidget);
        difficulty_custom->setObjectName(QString::fromUtf8("difficulty_custom"));
        difficulty_custom->setMaximumSize(QSize(200, 20));

        custom->addWidget(difficulty_custom, 0, Qt::AlignHCenter);


        game_buttons->addLayout(custom);

        counts = new QVBoxLayout();
        counts->setObjectName(QString::fromUtf8("counts"));
        x_count = new QSpinBox(centralwidget);
        x_count->setObjectName(QString::fromUtf8("x_count"));
        x_count->setEnabled(false);
        x_count->setMinimum(2);

        counts->addWidget(x_count, 0, Qt::AlignHCenter);

        y_count = new QSpinBox(centralwidget);
        y_count->setObjectName(QString::fromUtf8("y_count"));
        y_count->setEnabled(false);
        y_count->setMinimum(2);

        counts->addWidget(y_count, 0, Qt::AlignHCenter);

        mines_count = new QSpinBox(centralwidget);
        mines_count->setObjectName(QString::fromUtf8("mines_count"));
        mines_count->setEnabled(false);
        mines_count->setMinimum(3);

        counts->addWidget(mines_count, 0, Qt::AlignHCenter);


        game_buttons->addLayout(counts);

        button_game = new QPushButton(centralwidget);
        button_game->setObjectName(QString::fromUtf8("button_game"));
        button_game->setMinimumSize(QSize(100, 21));
        button_game->setMaximumSize(QSize(120, 21));
        button_game->setFocusPolicy(Qt::NoFocus);
        button_game->setLayoutDirection(Qt::LeftToRight);
        button_game->setStyleSheet(QString::fromUtf8("QPushButton {background-color: #FFFFFF; color: black;}"));

        game_buttons->addWidget(button_game, 0, Qt::AlignHCenter|Qt::AlignVCenter);


        menu_layout->addLayout(game_buttons);


        verticalLayout->addLayout(menu_layout);

        game_map = new ClickableLabel(centralwidget);
        game_map->setObjectName(QString::fromUtf8("game_map"));
        game_map->setMaximumSize(QSize(1000, 1000));

        verticalLayout->addWidget(game_map, 0, Qt::AlignHCenter);

        MainWindow->setCentralWidget(centralwidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MineSweeper", nullptr));
        difficulty_1->setText(QCoreApplication::translate("MainWindow", "Beginner (9x9 with 10 mines)", nullptr));
        difficulty_2->setText(QCoreApplication::translate("MainWindow", "Average (16x16 with 40 mines)", nullptr));
        difficulty_3->setText(QCoreApplication::translate("MainWindow", "Expert (30x16 with 99 mines)", nullptr));
        difficulty_custom->setText(QCoreApplication::translate("MainWindow", "Custom", nullptr));
        button_game->setText(QCoreApplication::translate("MainWindow", "Start New Game", nullptr));
        game_map->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
