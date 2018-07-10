#ifndef SCUSTOMBUTTON_H
#define SCUSTOMBUTTON_H

#include <QtWidgets>

class SCustomButton : public QFrame
{
    Q_OBJECT
public:
    explicit SCustomButton(const QString &name = QString(), const QString &path = QString(), QWidget *parent = nullptr);

    void mousePressEvent(QMouseEvent* event);

signals:

    void clicked(const QString &path);

public slots:

private:
    QString path;

};

#endif // SCUSTOMBUTTON_H
