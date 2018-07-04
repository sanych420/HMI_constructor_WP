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

    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);

}

void CustomButton::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        emit clicked();
    }
}

