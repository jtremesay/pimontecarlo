#include "Widget.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    srand(static_cast<unsigned int>(time(nullptr)));

    QApplication a(argc, argv);
    Widget w;
    w.show();

    return a.exec();
}
