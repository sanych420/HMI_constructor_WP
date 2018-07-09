#include "welcomewidget.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    WelcomePage w;
    w.init();
    w.setExtension("pro");

    w.show();

    return a.exec();
}
