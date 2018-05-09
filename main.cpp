#include "qrcodewidget.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QRCodeWidget w;
    w.show();

    return a.exec();
}
