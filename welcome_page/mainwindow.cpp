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

    recentsWidget = new QScrollArea(mainWidget);

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
    mainLayout->addWidget(recentsWidget,1,1,1,3);
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
    connect(dialog,SIGNAL(fileSelected(QString)),this,SLOT(fileOpening(QString)));
    dialog->exec();
}

void MainWindow::fileOpening(QString fileName)
{
    prependToRecents(fileName);
    updateRecents();
}

/*the following code was inspired by an official QT SDI example*/

void MainWindow::updateRecents()
{
    qDeleteAll(recentsWidget->findChildren<QWidget*>("",Qt::FindDirectChildrenOnly));
    QSettings settings(QCoreApplication::organizationName(), QCoreApplication::applicationName());

    const QStringList recentFiles = readRecents(settings);
    const int count = qMin(int(recentsMaxNumber),recentFiles.size());

    qDebug() << recentFiles.size();

    for (int i = 0; i < count; ++i)
    {
        const QString fileName = strippedName(recentFiles.at(i));
        const QString filePath = QFileInfo(recentFiles.at(i)).canonicalFilePath();
        recentsButton[i] = new QPushButton(QString("%1. %2 \n %3").arg(i + 1).arg(fileName)
                                           .arg(filePath),recentsWidget);
        recentsButton[i]->setVisible(true);
        recentsButton[i]->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Fixed);
        recentsButton[i]->setStyleSheet("QPushButton"
                                        " {"
                                        "   background-color: rgb(240,240,240);"
                                        "   border: 1px solid rgb(240,240,240);"
                                        " }"
                                        "QPushButton:hover { background-color: white; }");
        recentsButton[i]->move(5, 5 + 35*i);
        connect(recentsButton[i],SIGNAL(clicked(bool)),this,SLOT(recentFileClicked()));
    }
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
    qDebug() << fullFileName;
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
    if (oldRecentFiles != recentFiles)
    {
        writeRecents(recentFiles, settings);
    }
}

void MainWindow::recentFileClicked()
{
    for (int i = 0; i < recentsMaxNumber; ++i)
    {
        if (sender() == recentsButton[i])
        {
            qDebug() << i;
        }
    }
}
