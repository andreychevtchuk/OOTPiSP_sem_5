#include "qpaintwidget.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    myPaintWidget w;
    w.show();
    return a.exec();
}
