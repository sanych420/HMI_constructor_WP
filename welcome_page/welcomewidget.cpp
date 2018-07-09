#include "welcomewidget.h"
#include <QDebug>

WelcomePage::WelcomePage(QWidget *parent)
    : QWidget(parent)
{
    //init();
}

WelcomePage::~WelcomePage()
{

}

void WelcomePage::init()
{
    resize(800,600);
    setWindowTitle("Welcome page");

    recentsWidget = new QWidget(this);
    recentsWidget->setSizePolicy(QSizePolicy::Preferred,QSizePolicy::Minimum);

    recentsArea = new QScrollArea;

    mainLayout = new QGridLayout(this);
    mainLayout->setObjectName("mainLayout");
    SpecialButton* buttonNew = new SpecialButton(true, this);
    connect(buttonNew,SIGNAL(clicked(bool)),this,SIGNAL(createNew()));
    //connect(buttonNew,SIGNAL(clicked(bool)),this,SLOT(on_buttonNew_clicked()));
    SpecialButton* buttonOpen = new SpecialButton(false, this);
    //connect(buttonOpen,SIGNAL(clicked(bool)),this,SIGNAL(buttonOpen_clicked()));
    connect(buttonOpen,SIGNAL(clicked(bool)),this,SLOT(on_buttonOpen_clicked()));

    mainLayout->addWidget(buttonNew,0,0);
    mainLayout->addWidget(buttonOpen,0,1);
    mainLayout->addWidget(recentsArea,1,1,1,3);
    QWidget* dummyWidget = new QWidget(this);
    dummyWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    mainLayout->addWidget(dummyWidget,0,2);

    setLayout(mainLayout);

    layout = new QVBoxLayout(recentsWidget);
    layout->setObjectName("layout");

    updateRecents();
}

void WelcomePage::on_buttonNew_clicked()
{
    qDebug() << "buttonNew was clicked";
    createNewFile(QDir::currentPath() + "/NewProject.txt");
}

void WelcomePage::on_buttonOpen_clicked()
{
    qDebug() << "buttonOpen was clicked";
    /*QFileDialog* dialog = new QFileDialog(this);
    dialog->setAttribute(Qt::WA_DeleteOnClose);
    connect(dialog,SIGNAL(fileSelected(QString)),this,SLOT(openFile(QString)));
    dialog->exec();*/

    QString path = QFileDialog::getOpenFileName(this, tr("Open existing file"), "", tr("Project (*.%1)").arg(extension.isEmpty() ? "*" : extension));
    if (!checkFile(path)) return;
    emit openExisting(path);
}

void WelcomePage::updateRecents()
{
    recentsButtons.clear();
    filePaths.clear();
    clearLayout(layout);

    //        QList<CustomButton*> allRecentButtons = recentsWidget->findChildren<CustomButton*>("",Qt::FindDirectChildrenOnly);
    //        for (int i = 0; i < allRecentButtons.size(); ++i)
    //        {
    //            allRecentButtons.at(i)->deleteLater();
    //        }

    QLabel* recentsLabel = new QLabel(tr("Recent files"),recentsWidget);
    recentsLabel->setFont(QFont("MS Shell Dlg 2",12,-1,false));
    layout->addWidget(recentsLabel);

    QSettings settings("recentfiles.ini", QSettings::IniFormat);

    const QStringList recentFiles = readRecents(settings);
    const int count = qMin(int(recentsMaxNumber),recentFiles.size());

    for (int i = 0; i < count; ++i)
    {
        const QString fileName = strippedName(recentFiles.at(i));
        const QString filePath = QFileInfo(recentFiles.at(i)).canonicalFilePath();
        CustomButton* recentButton = new CustomButton((tr("%1. ").arg(i + 1) + fileName), filePath, recentsWidget);
        recentsButtons.append(recentButton);
        filePaths.append(filePath);
        layout->addWidget(recentsButtons.at(i));
        connect(recentButton, SIGNAL(clicked()), this, SLOT(recentFileClicked()));
    }

    layout->addStretch(1);
    recentsWidget->setLayout(layout);
    recentsArea->setWidget(recentsWidget);
}

QStringList WelcomePage::readRecents(QSettings &settings)
{
    QStringList result;
    const int count = settings.beginReadArray("recentFileList");
    for (int i = 0; i < count; ++i)
    {
        settings.setArrayIndex(i);
        if (fileExists(settings.value("file").toString()))
        {
            result.append(settings.value("file").toString());
        }
    }
    settings.endArray();
    return result;
}

void WelcomePage::writeRecents(const QStringList &files, QSettings &settings)
{
    const int count = files.size();
    settings.beginWriteArray("recentFileList");
    for (int i = 0; i < count; ++i)
    {
        settings.setArrayIndex(i);
        settings.setValue("file",files.at(i));
    }
    settings.endArray();
}

void WelcomePage::prependToRecents(const QString &fileName)
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

void WelcomePage::createNewFile(const QString &fileName)
{
    prependToRecents(fileName);
    updateRecents();
}

void WelcomePage::openFile(const QString &fileName)
{
    if (!checkFile(fileName)) return;

    prependToRecents(fileName);
    updateRecents();

    emit openExisting(fileName);
}

bool WelcomePage::checkFile(const QString &path) {
    if (!QFile(path).exists()) return false;
    if (!extension.isEmpty()) {
        if (QFileInfo(path).completeSuffix() != extension) return false;
    }
    return true;
}

void WelcomePage::sanitize() {
    //for ()
}

QString WelcomePage::strippedName(const QString &fullFileName)
{
    return QFileInfo(fullFileName).fileName();
}

void WelcomePage::recentFileClicked()
{
    for (int i = 0; i < qMin(recentsMaxNumber, recentsButtons.size()); ++i)
    {
        if (sender() == recentsButtons.at(i))
        {
            qDebug() << "File #" << i + 1 << ", path" << filePaths.at(i) <<"is opened";
            openFile(filePaths.at(i));
        }
    }
}

bool WelcomePage::fileExists(const QString &fullFileName)
{
    return QFileInfo::exists(fullFileName) && QFileInfo(fullFileName).isFile();;
}

void WelcomePage::clearLayout(QLayout *layout)
{
    QLayoutItem *item;
    while((item = layout->takeAt(0))) {
        if (item->layout()) {
            clearLayout(item->layout());
            item->layout()->deleteLater();
        }
        if (item->widget()) {
            item->widget()->deleteLater();
        }
        delete item;
    }
}
