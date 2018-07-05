#include "custombutton.h"

CustomButton::CustomButton(QString name, QString path, QWidget *parent) : QFrame(parent)
{
    setStyleSheet("CustomButton"
                  " {"
                  "   background-color: rgb(240,240,240);"
                  "   border: 1px solid rgb(240,240,240);"
                  " }"
                  "CustomButton:hover { background-color: white; }");

    QLabel* nameLabel = new QLabel(name, this);
    QLabel* pathLabel = new QLabel(path, this);

    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->addWidget(nameLabel);
    layout->addWidget(pathLabel);

    setLayout(layout);

    setVisible(true);

    //setMaximumHeight(60);

    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

}

void CustomButton::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        emit clicked();
    }
}

SpecialButton::SpecialButton(bool trueIsNewFalseIsOpen, QWidget *parent)
{

    setParent(parent);
    QScreen* screen = QGuiApplication::primaryScreen();

    QSize minSize, maxSize;

    minSize.setHeight(screen->availableSize().height() / 30);
    minSize.setWidth(screen->availableSize().width() / 20);

    maxSize.setHeight(screen->availableSize().height() / 25);
    maxSize.setWidth(screen->availableSize().width() / 15);

    setMinimumSize(minSize);
    setMaximumSize(maxSize);

    setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Minimum);

    setStyleSheet("SpecialButton"
                  " {"
                  "   background-color: rgb(240,240,240);"
                  "   border: 1px solid rgb(25,25,25);"
                  " }"
                  "SpecialButton:hover { background-color: white; }");

    if (trueIsNewFalseIsOpen)
    {
        setText(tr("New..."));
        setIcon(QIcon(QPixmap(":/new.png")));
    }
    else
    {
        setText(tr("Open..."));
        setIcon(QIcon(QPixmap(":/open.png")));
    }
}

