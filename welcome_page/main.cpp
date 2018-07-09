#include "swelcomepage.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    SWelcomePage w;
    w.init();
    w.setExtension("ini");

    w.show();

    return a.exec();
}
