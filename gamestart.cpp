#include "gamestart.h"
#include "ui_gamestart.h"

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
