#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    QCoreApplication::setApplicationName("HMI Constructor");
    QCoreApplication::setOrganizationName("INELSY");

    return a.exec();
}
