#include "swelcomepage.h"
#include <QApplication>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QFile css(":/styles.css");
    css.open(QFile::ReadOnly);
    QString styleSheet = QLatin1String(css.readAll());

    a.setStyleSheet(styleSheet);

    SWelcomePage w;
    w.init();
    w.setExtension("");

    w.resize(1280, 720);
    w.setWindowTitle("Welcome page");

    w.show();

    return a.exec();
}
