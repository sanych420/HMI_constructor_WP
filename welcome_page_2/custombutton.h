#ifndef CUSTOMBUTTON_H
#define CUSTOMBUTTON_H

#include <QtWidgets>

class CustomButton : public QFrame
{
    Q_OBJECT
public:
    explicit CustomButton(QString name = QString(), QString path = QString(), QWidget *parent = nullptr);

    void mousePressEvent(QMouseEvent* event);

signals:

    void clicked();

public slots:

private:


};

#endif // CUSTOMBUTTON_H
