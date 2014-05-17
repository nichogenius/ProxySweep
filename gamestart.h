#ifndef GAMESTART_H
#define GAMESTART_H


#include <QDialog>

namespace Ui {
class GameStart;
}

class GameStart : public QDialog
{
    Q_OBJECT

public:
    explicit GameStart(QWidget *parent = 0);
    ~GameStart();

private slots:
    void on_EasyGame_clicked();

    void on_ModerateGame_clicked();

    void on_HardGame_clicked();

    void on_ExpertGame_clicked();

    void on_StartCustomGame_clicked();

private:
    void parseError(int err);
    Ui::GameStart *ui;
};

#endif // GAMESTART_H
