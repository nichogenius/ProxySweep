#include <gamestart.h>
#include <qapplication.h>

int main(int argc, char** argv) {
    QApplication a(argc, argv);
    GameStart s;
    s.show();
    return a.exec();
}
