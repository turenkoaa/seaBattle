#include "seabattle.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //Client w("localhost", 2323);
    SeaBattle w;
    w.show();

    return a.exec();
}
