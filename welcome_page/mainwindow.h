#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtWidgets>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);

    void init();

    QStringList readRecents(QSettings &settings);

    void writeRecents(const QStringList &files, QSettings &settings);

    void prependToRecents(const QString &fileName);

    QString recentFilesKey();
    QString fileKey();

    QString strippedName(const QString &fullFileName);

    ~MainWindow();
public slots:

    void buttonNew_clicked();

    void buttonOpen_clicked();

    void updateRecents();

    void fileOpening(QString fileName);

    void recentFileClicked();

    void createNewFile(QString fileName);

private:

    enum {recentsMaxNumber = 5};

    QString* stringName, stringPath;

    QScrollArea* recentsWidget;

    QWidget* recents[recentsMaxNumber];
    QVBoxLayout* labelLayout[recentsMaxNumber];
    QLabel* labelName[recentsMaxNumber];
    QLabel* labelPath[recentsMaxNumber];

    QPushButton* recentsButton[recentsMaxNumber];

    QString globalFilePath[recentsMaxNumber];

};

#endif // MAINWINDOW_H
