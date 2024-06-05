#include "serialeditor.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    SerialEditor w;
    w.show();
    return a.exec();
}
