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

    void setMaxRecentsNumber(int number)
    {
        recentsMaxNumber = number;
    }

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

    bool fileExists(const QString &fullFileName);

    int recentsMaxNumber = 5;

    QWidget* recentsWidget;

    QScrollArea* recentsArea;

    QVector<QWidget*> recents;

    QVector<CustomButton*> recentsButtons;

    QStringList filePaths;

    QString strippedName(const QString &fullFileName);

    QVBoxLayout* layout;

    QGridLayout* mainLayout;

    bool isFirstTimeUpdated = true;

    private slots:

    void on_buttonNew_clicked();

    void on_buttonOpen_clicked();

    void openFile(QString fileName);

    void createNewFile(QString fileName);

    void recentFileClicked();

    void clearLayout(QLayout *layout);

};

#endif // WELCOMEWIDGET_H
