#include "scustombutton.h"

SCustomButton::SCustomButton(const QString &name, const QString &path, QWidget *parent) : QFrame(parent)
{
    this->path = path;

    QLabel* nameLabel = new QLabel(name, this);
    QFont nameFont = nameLabel->font();
    nameFont.setBold(true);
    nameLabel->setFont(nameFont);
    QLabel* pathLabel = new QLabel(path, this);

    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->addWidget(nameLabel);
    layout->addWidget(pathLabel);

    setLayout(layout);

    setVisible(true);

    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
}

void SCustomButton::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        emit clicked(path);
    }
    QWidget::mousePressEvent(event);
}


