#ifndef WELCOMEWIDGET_H
#define WELCOMEWIDGET_H

#include <QtWidgets>
#include <custombutton.h>


class WelcomePage : public QWidget
{
    Q_OBJECT

public:
    WelcomePage(QWidget *parent = 0);
    ~WelcomePage();

    void setMaxRecentsNumber(int number)
    {
        recentsMaxNumber = number;
    }
    void setExtension(const QString &ext) {extension = ext;}
    void init();

signals:
    //void buttonNew_clicked();
    //void buttonOpen_clicked();

    void createNew();
    void openExisting(const QString &path);

private:
    QString extension = QString();

    void updateRecents();

    bool checkFile(const QString &path);
    void sanitize();


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
    void openFile(const QString &fileName);
    void createNewFile(const QString &fileName);
    void recentFileClicked();
    void clearLayout(QLayout *layout);

};

#endif // WELCOMEWIDGET_H
