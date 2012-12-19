#include <QtGui/QApplication>
#include "qpemainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QPEMainWindow w;
    w.show();
    
    return a.exec();
}
