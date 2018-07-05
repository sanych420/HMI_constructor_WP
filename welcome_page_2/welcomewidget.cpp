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

    recentsWidget = new QWidget;

    mainLayout = new QGridLayout(this);
    SpecialButton* buttonNew = new SpecialButton(true, this);
    connect(buttonNew,SIGNAL(clicked(bool)),this,SIGNAL(buttonNew_clicked()));
    //connect(buttonNew,SIGNAL(clicked(bool)),this,SLOT(on_buttonNew_clicked()));
    SpecialButton* buttonOpen = new SpecialButton(false, this);
    connect(buttonOpen,SIGNAL(clicked(bool)),this,SIGNAL(buttonOpen_clicked()));
    connect(buttonOpen,SIGNAL(clicked(bool)),this,SLOT(on_buttonOpen_clicked()));

    mainLayout->addWidget(buttonNew,0,0);
    mainLayout->addWidget(buttonOpen,0,1);
    mainLayout->addWidget(recentsWidget,1,1,1,3);
    QWidget* dummyWidget = new QWidget(this);
    dummyWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    mainLayout->addWidget(dummyWidget,0,2);

    setLayout(mainLayout);

    layout = new QVBoxLayout(recentsWidget);
    //layout->setContentsMargins(0,0,0,200);

    updateRecents();

    qDebug() << buttonNew->size();
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
    clearLayout(layout);
//    QList<CustomButton*> allRecentButtons = recentsWidget->findChildren<CustomButton*>("",Qt::FindDirectChildrenOnly);

//    for (int i = 0; i < allRecentButtons.size(); ++i)
//    {
//        allRecentButtons.at(i)->deleteLater();
//    }

    QSettings settings("recentfiles.ini", QSettings::IniFormat);

    const QStringList recentFiles = readRecents(settings);
    const int count = qMin(int(recentsMaxNumber),recentFiles.size());

    CustomButton* recentButton;

    for (int i = 0; i < count; ++i)
    {
        const QString fileName = strippedName(recentFiles.at(i));
        const QString filePath = QFileInfo(recentFiles.at(i)).canonicalFilePath();
        recentButton = new CustomButton((tr("%1. ").arg(i + 1) + fileName),filePath,recentsWidget);
        recentButton->move(5,5+50*i);
        recentsButtons.append(recentButton);
        filePaths.append(filePath);
        layout->addWidget(recentsButtons.at(i));
        connect(recentButton,SIGNAL(clicked()),this,SLOT(recentFileClicked()));
    }
    recentsWidget->setLayout(layout);
    if (isFirstTimeUpdated)
    {
        isFirstTimeUpdated = false;
    }
}

QStringList WelcomeWidget::readRecents(QSettings &settings)
{
    QStringList result;
    const int count = settings.beginReadArray(tr("recentFileList"));
    for (int i = 0; i < count; ++i)
    {
        settings.setArrayIndex(i);
        if (fileExists(settings.value(tr("file")).toString()))
        {
            result.append(settings.value(tr("file")).toString());
        }
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

bool WelcomeWidget::fileExists(const QString &fullFileName)
{
    bool fileExists = QFileInfo::exists(fullFileName) && QFileInfo(fullFileName).isFile();

    return fileExists;
}

void WelcomeWidget::clearLayout(QLayout *layout)
{
    QLayoutItem *item;
    while((item = layout->takeAt(0))) {
        if (item->layout()) {
            clearLayout(item->layout());
            delete item->layout();
        }
        if (item->widget()) {
            delete item->widget();
        }
        delete item;
    }
}
