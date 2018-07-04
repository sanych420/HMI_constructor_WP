#ifndef WELCOMEWIDGET_H
#define WELCOMEWIDGET_H

#include <QtWidgets>
#include <custombutton.h>


class WelcomeWidget : public QWidget
{
    Q_OBJECT

public:
    WelcomeWidget(QWidget *parent = 0);
    ~WelcomeWidget();

public slots:

signals:

void buttonNew_clicked();

void buttonOpen_clicked();

private:

    void init();

    void updateRecents();

    QStringList readRecents(QSettings &settings);

    void writeRecents(const QStringList &files, QSettings &settings);

    void prependToRecents(const QString &filename);

    int recentsMaxNumber = 5;

    QScrollArea* recentsWidget;

    QVector<QWidget*> recents;

    QVector<CustomButton*> recentsButtons;

    QStringList filePaths;

    QString strippedName(const QString &fullFileName);

private slots:

    void on_buttonNew_clicked();

    void on_buttonOpen_clicked();

    void openFile(QString fileName);

    void createNewFile(QString fileName);

    void recentFileClicked();



};

#endif // WELCOMEWIDGET_H
