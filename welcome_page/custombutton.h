#ifndef CUSTOMBUTTON_H
#define CUSTOMBUTTON_H

#include <QtWidgets>

class CustomButton : public QFrame
{
    Q_OBJECT
public:
    explicit CustomButton(const QString &name = QString(), const QString &path = QString(), QWidget *parent = nullptr);

    void mousePressEvent(QMouseEvent* event);

signals:

    void clicked();

public slots:

private:


};

class SpecialButton : public QPushButton
{
    Q_OBJECT
    public:
    SpecialButton(bool trueIsNewFalseIsOpen, QWidget* parent = nullptr);

};

#endif // CUSTOMBUTTON_H
