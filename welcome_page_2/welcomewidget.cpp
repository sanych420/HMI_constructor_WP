#include "welcomewidget.h"
#include <QDebug>

WelcomeWidget::WelcomeWidget(QWidget *parent)
    : QWidget(parent)
{
    init();
}

WelcomeWidget::~WelcomeWidget()
{

}

void WelcomeWidget::init()
{
    resize(800,600);

    recentsWidget = new QScrollArea(this);

    QGridLayout* mainLayout = new QGridLayout(this);
    QPushButton* buttonNew = new QPushButton(tr("New..."), this);
    buttonNew->setMaximumSize(100,20);
    buttonNew->setMinimumSize(100,20);
    connect(buttonNew,SIGNAL(clicked(bool)),this,SIGNAL(buttonNew_clicked()));
    //connect(buttonNew,SIGNAL(clicked(bool)),this,SLOT(on_buttonNew_clicked()));
    QPushButton* buttonOpen = new QPushButton(tr("Open..."), this);
    buttonOpen->setMaximumSize(100,20);
    buttonOpen->setMinimumSize(100,20);
    connect(buttonOpen,SIGNAL(clicked(bool)),this,SIGNAL(buttonOpen_clicked()));
    connect(buttonOpen,SIGNAL(clicked(bool)),this,SLOT(on_buttonOpen_clicked()));

    mainLayout->addWidget(buttonNew,0,0);
    mainLayout->addWidget(buttonOpen,0,1);
    mainLayout->addWidget(recentsWidget,1,1,1,3);
    QWidget* dummyWidget = new QWidget(this);
    dummyWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    mainLayout->addWidget(dummyWidget,0,2);

    setLayout(mainLayout);

    updateRecents();
}

void WelcomeWidget::on_buttonNew_clicked()
{
    qDebug() << "buttonNew was clicked";
    createNewFile(QDir::currentPath() + "/NewProject.txt");
}

void WelcomeWidget::on_buttonOpen_clicked()
{
    qDebug() << "buttonOpen was clicked";
    QFileDialog* dialog = new QFileDialog(this);
    dialog->setAttribute(Qt::WA_DeleteOnClose);
    connect(dialog,SIGNAL(fileSelected(QString)),this,SLOT(openFile(QString)));
    dialog->exec();
}

void WelcomeWidget::updateRecents()
{
    recentsButtons.clear();
    filePaths.clear();
    qDeleteAll(recentsWidget->findChildren<QWidget*>("",Qt::FindDirectChildrenOnly));
    QSettings settings("recentfiles.ini", QSettings::IniFormat);

    const QStringList recentFiles = readRecents(settings);
    const int count = qMin(int(recentsMaxNumber),recentFiles.size());

    //QVBoxLayout* layout;

    for (int i = 0; i < count; ++i)
    {
        //layout = new QVBoxLayout(recentsWidget);
        const QString fileName = strippedName(recentFiles.at(i));
        const QString filePath = QFileInfo(recentFiles.at(i)).canonicalFilePath();
        CustomButton* recentButton = new CustomButton((tr("%1. ").arg(i + 1) + fileName),filePath,recentsWidget);
        recentButton->move(5,5+50*i);
        recentsButtons.append(recentButton);
        filePaths.append(filePath);
        //layout->addWidget(recentsButtons.at(i));
        connect(recentButton,SIGNAL(clicked()),this,SLOT(recentFileClicked()));
    }
    //recentsWidget->setLayout(layout);
}

QStringList WelcomeWidget::readRecents(QSettings &settings)
{
    QStringList result;
    const int count = settings.beginReadArray(tr("recentFileList"));
    for (int i = 0; i < count; ++i)
    {
        settings.setArrayIndex(i);
        result.append(settings.value(tr("file")).toString());
    }
    settings.endArray();
    return result;
}

void WelcomeWidget::writeRecents(const QStringList &files, QSettings &settings)
{
    const int count = files.size();
    settings.beginWriteArray(tr("recentFileList"));
    for (int i = 0; i < count; ++i)
    {
        settings.setArrayIndex(i);
        settings.setValue(tr("file"),files.at(i));
    }
    settings.endArray();
}

void WelcomeWidget::prependToRecents(const QString &fileName)
{
    QSettings settings("recentfiles.ini", QSettings::IniFormat);

    const QStringList oldRecentFiles = readRecents(settings);
    QStringList recentFiles = oldRecentFiles;
    recentFiles.removeAll(fileName);
    recentFiles.prepend(fileName);
    if (oldRecentFiles != recentFiles)
    {
        writeRecents(recentFiles, settings);
    }
}

void WelcomeWidget::createNewFile(QString fileName)
{
    prependToRecents(fileName);
    updateRecents();
}

void WelcomeWidget::openFile(QString fileName)
{
    prependToRecents(fileName);
    updateRecents();
}

QString WelcomeWidget::strippedName(const QString &fullFileName)
{
    return QFileInfo(fullFileName).fileName();
}

void WelcomeWidget::recentFileClicked()
{
    for (int i = 0; i < qMin(recentsMaxNumber, recentsButtons.size()); ++i)
    {
        if (sender() == recentsButtons.at(i))
        {
            openFile(filePaths.at(i));
            qDebug() << "File #" << i + 1 << ", path" << filePaths.at(i) <<"is opened";
        }
    }
}
