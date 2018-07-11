#ifndef SWELCOMEPAGE_H
#define SWELCOMEPAGE_H

#include <QtWidgets>
#include <scustombutton.h>

class SWelcomePage : public QWidget
{
    Q_OBJECT

public:
    SWelcomePage(QWidget *parent = 0);
    ~SWelcomePage();

    void setMaxRecentsNumber(int number) {recentsMaxNumber = number;}
    void setExtension(const QString &ext) {extension = ext;}
    void init();

signals:

    void createNew();
    void openExisting(const QString &path);

private:
    QString extension = QString();

    void updateRecents();
    bool checkFile(const QString &path);
    QStringList readRecents(QSettings &settings);
    void writeRecents(const QStringList &files, QSettings &settings);
    void prependToRecents(const QString &filename);
    bool fileExists(const QString &fullFileName);
    QString strippedName(const QString &fullFileName);

    int recentsMaxNumber = 5;
    QWidget* recentsWidget;
    QScrollArea* recentsArea;
    QVector<QWidget*> recents;
    QVector<SCustomButton*> recentsButtons;
    QStringList filePaths;
    QVBoxLayout* layout;
    QGridLayout* mainLayout;
    bool isFirstTimeUpdated = true;
    QLabel* recentsLabel;

private slots:

    void on_buttonOpen_clicked();
    void openFile(const QString &fileName);
    void recentFileClicked(QString path);
    void clearLayout(QLayout *layout);

};

#endif // SWELCOMEPAGE_H
