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

private:
    Ui::GameStart *ui;
};

#endif // GAMESTART_H
