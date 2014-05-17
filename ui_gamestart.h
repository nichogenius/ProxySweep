/********************************************************************************
** Form generated from reading UI file 'gamestart.ui'
**
** Created by: Qt User Interface Compiler version 5.2.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GAMESTART_H
#define UI_GAMESTART_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>

QT_BEGIN_NAMESPACE

class Ui_GameStart
{
public:
    QPushButton *EasyGame;
    QPushButton *ModerateGame;
    QPushButton *HardGame;
    QPushButton *ExpertGame;
    QPushButton *StartCustomGame;
    QSpinBox *RowSelector;
    QSpinBox *ColumnSelector;
    QSpinBox *MineSelector;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;

    void setupUi(QDialog *GameStart)
    {
        if (GameStart->objectName().isEmpty())
            GameStart->setObjectName(QStringLiteral("GameStart"));
        GameStart->resize(400, 227);
        EasyGame = new QPushButton(GameStart);
        EasyGame->setObjectName(QStringLiteral("EasyGame"));
        EasyGame->setGeometry(QRect(60, 30, 80, 25));
        ModerateGame = new QPushButton(GameStart);
        ModerateGame->setObjectName(QStringLiteral("ModerateGame"));
        ModerateGame->setGeometry(QRect(60, 80, 101, 25));
        HardGame = new QPushButton(GameStart);
        HardGame->setObjectName(QStringLiteral("HardGame"));
        HardGame->setGeometry(QRect(60, 130, 80, 25));
        ExpertGame = new QPushButton(GameStart);
        ExpertGame->setObjectName(QStringLiteral("ExpertGame"));
        ExpertGame->setGeometry(QRect(60, 180, 80, 25));
        StartCustomGame = new QPushButton(GameStart);
        StartCustomGame->setObjectName(QStringLiteral("StartCustomGame"));
        StartCustomGame->setGeometry(QRect(230, 180, 131, 25));
        RowSelector = new QSpinBox(GameStart);
        RowSelector->setObjectName(QStringLiteral("RowSelector"));
        RowSelector->setGeometry(QRect(290, 40, 45, 26));
        RowSelector->setMinimum(3);
        RowSelector->setValue(14);
        ColumnSelector = new QSpinBox(GameStart);
        ColumnSelector->setObjectName(QStringLiteral("ColumnSelector"));
        ColumnSelector->setGeometry(QRect(290, 80, 45, 26));
        ColumnSelector->setMinimum(3);
        ColumnSelector->setValue(10);
        MineSelector = new QSpinBox(GameStart);
        MineSelector->setObjectName(QStringLiteral("MineSelector"));
        MineSelector->setGeometry(QRect(290, 120, 45, 26));
        MineSelector->setMinimum(1);
        MineSelector->setValue(24);
        label = new QLabel(GameStart);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(230, 50, 53, 17));
        label_2 = new QLabel(GameStart);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(230, 90, 53, 17));
        label_3 = new QLabel(GameStart);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(230, 130, 53, 17));

        retranslateUi(GameStart);

        QMetaObject::connectSlotsByName(GameStart);
    } // setupUi

    void retranslateUi(QDialog *GameStart)
    {
        GameStart->setWindowTitle(QApplication::translate("GameStart", "Dialog", 0));
        EasyGame->setText(QApplication::translate("GameStart", "Easy Game", 0));
        ModerateGame->setText(QApplication::translate("GameStart", "Moderate Game", 0));
        HardGame->setText(QApplication::translate("GameStart", "Hard Game", 0));
        ExpertGame->setText(QApplication::translate("GameStart", "Expert Game", 0));
        StartCustomGame->setText(QApplication::translate("GameStart", "Start Custom Game", 0));
        label->setText(QApplication::translate("GameStart", "Rows", 0));
        label_2->setText(QApplication::translate("GameStart", "Columns", 0));
        label_3->setText(QApplication::translate("GameStart", "Mines", 0));
    } // retranslateUi

};

namespace Ui {
    class GameStart: public Ui_GameStart {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GAMESTART_H
