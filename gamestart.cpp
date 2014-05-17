#include "gamestart.h"
#include "ui_gamestart.h"
#include "interface.h"
#include "video.h"
#include <QMessageBox>

void GameStart::parseError(int err) {
    if (err != GAME_CREATED) {
        QMessageBox messageBox;
        messageBox.critical(0,"Error", getError(err));
        messageBox.setFixedSize(500,200);
    }
    else {
        this->hide();
        video_loop();
        this->show();
    }
}

GameStart::GameStart(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GameStart)
{
    ui->setupUi(this);
}

GameStart::~GameStart()
{
    delete ui;
}

void GameStart::on_EasyGame_clicked()
{
    int error = newEasyGame();
    parseError(error);
}

void GameStart::on_ModerateGame_clicked()
{
    int error = newModerateGame();
    parseError(error);
}

void GameStart::on_HardGame_clicked()
{
    int error = newHardGame();
    parseError(error);
}

void GameStart::on_ExpertGame_clicked()
{
    int error = newExpertGame();
    parseError(error);
}


void GameStart::on_StartCustomGame_clicked()
{
    int error = newGame(this->ui->ColumnSelector->value(), this->ui->RowSelector->value(), this->ui->MineSelector->value());
    parseError(error);
}
