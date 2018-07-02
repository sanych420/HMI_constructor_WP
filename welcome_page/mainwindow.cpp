#include "mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    init();
}

MainWindow::~MainWindow()
{

}

void MainWindow::init()
{
    resize(800, 600);
    QWidget* mainWidget = new QWidget(this);
    setCentralWidget(mainWidget);

    recentsWidget = new QWidget(mainWidget);

    QGridLayout* mainLayout = new QGridLayout(mainWidget);

    updateRecents();

    QPushButton* buttonNew = new QPushButton("New...", mainWidget);
    buttonNew->setMaximumSize(100,20);
    buttonNew->setMinimumSize(100,20);
    connect(buttonNew,SIGNAL(clicked(bool)),this,SLOT(buttonNew_clicked()));
    QPushButton* buttonOpen = new QPushButton("Open...", mainWidget);
    buttonOpen->setMaximumSize(100,20);
    buttonOpen->setMinimumSize(100,20);
    connect(buttonOpen,SIGNAL(clicked(bool)),this,SLOT(buttonOpen_clicked()));

    mainLayout->addWidget(buttonNew,0,0);
    mainLayout->addWidget(buttonOpen,0,1);
    mainLayout->addWidget(recentsWidget,1,1);
    QWidget* dummyWidget = new QWidget(mainWidget); //using a dummy widget because stretch doesn't work
    dummyWidget->setMaximumWidth(200);
    dummyWidget->setMinimumWidth(100);
    mainLayout->addWidget(dummyWidget,0,2);

    mainWidget->setLayout(mainLayout);
}

void MainWindow::buttonNew_clicked()
{
    qDebug() << "buttonNew was clicked";
}

void MainWindow::buttonOpen_clicked()
{
    qDebug() << "buttonOpen was clicked";
    QFileDialog* dialog = new QFileDialog(this);
    connect(dialog,SIGNAL(fileSelected(QString)),this,SLOT(simulateFileOpening(QString)));
    dialog->exec();
}


void MainWindow::simulateFileOpening(QString fileName)
{
    prependToRecents(fileName);
    updateRecents();
}

/*the following code was inspired by an official QT SDI example*/

void MainWindow::updateRecents()
{

    QVBoxLayout* VLayoutRecents = new QVBoxLayout(recentsWidget);

    QSettings settings(QCoreApplication::organizationName(), QCoreApplication::applicationName());

    const QStringList recentFiles = readRecents(settings);
    const int count = qMin(int(recentsMaxNumber),recentFiles.size());

    for (int i = 0; i < count; ++i)
    {
        const QString fileName = strippedName(recentFiles.at(i));
        qDebug() << "name" << fileName;
        recents[i] = new QWidget(recentsWidget);
        labelName[i] = new QLabel(recents[i]);
        labelName[i]->setText(QString("&%1. %2").arg(i + 1).arg(fileName));
        labelPath[i] = new QLabel(recents[i]);
        labelPath[i]->setText(QFileInfo(fileName).canonicalFilePath());
        QVBoxLayout* labelLayout = new QVBoxLayout(recents[i]);
        labelLayout->addWidget(labelName[i]);
        labelLayout->addWidget(labelPath[i]);
        VLayoutRecents->addWidget(recents[i]);
        // for some reason, labels don't appear, but i'm pretty sure they did before i put this loop in a separate function;
        // might want to move it back, or do something with the "recentsWidget" widget
    }
    recentsWidget->setLayout(VLayoutRecents);
    recentsWidget->update();
}

QStringList MainWindow::readRecents(QSettings &settings)
{
    QStringList result;
    const int count = settings.beginReadArray(recentFilesKey());
    qDebug() << count;
    for (int i = 0; i < count; ++i)
    {
        settings.setArrayIndex(i);
        result.append(settings.value(fileKey()).toString());
    }
    settings.endArray();
    return result;
}

QString MainWindow::recentFilesKey()
{
    return QStringLiteral("recentFileList"); // using QStringLiteral here for a better memory allocation
}

QString MainWindow::fileKey()
{
    return QStringLiteral("file");
}

QString MainWindow::strippedName(const QString &fullFileName)
{
    return QFileInfo(fullFileName).fileName();
}

void MainWindow::writeRecents(const QStringList &files, QSettings &settings)
{
    const int count = files.size();
    settings.beginWriteArray(recentFilesKey());
    for (int i = 0; i < count; ++i)
    {
        settings.setArrayIndex(i);
        settings.setValue(fileKey(),files.at(i));
    }
    settings.endArray();
}

void MainWindow::prependToRecents(const QString &fileName)
{
    QSettings settings(QCoreApplication::organizationName(), QCoreApplication::applicationName());

    const QStringList oldRecentFiles = readRecents(settings);
    QStringList recentFiles = oldRecentFiles;
    recentFiles.removeAll(fileName);
    recentFiles.prepend(fileName);
    //    if (oldRecentFiles != recentFiles)
    //    {
    writeRecents(recentFiles, settings);
    //    }
}
