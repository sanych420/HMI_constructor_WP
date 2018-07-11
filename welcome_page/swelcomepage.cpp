#include "swelcomepage.h"
#include <QDebug>

SWelcomePage::SWelcomePage(QWidget *parent)
    : QWidget(parent)
{

}

SWelcomePage::~SWelcomePage()
{

}

void SWelcomePage::init()
{
    recentsWidget = new QWidget(this);
    recentsWidget->setSizePolicy(QSizePolicy::Preferred,QSizePolicy::Minimum);
    recentsArea = new QScrollArea;
    recentsArea->setObjectName("recentsArea");
    mainLayout = new QGridLayout(this);
    mainLayout->setObjectName("mainLayout");

    QPushButton* buttonNew = new QPushButton(this);
    QPixmap newPixmap = QPixmap(":/new.png");
    QFontMetrics fontMetrics = this->fontMetrics();
    buttonNew->setText(tr("&New..."));
    buttonNew->setObjectName("buttonNew");
    buttonNew->setIcon(QIcon(newPixmap));
    buttonNew->setIconSize(fontMetrics.size(Qt::TextShowMnemonic,buttonNew->text()));

    connect(buttonNew,SIGNAL(clicked(bool)),this,SIGNAL(createNew()));

    QPushButton* buttonOpen = new QPushButton(this);
    QPixmap openPixmap = QPixmap(":/open.png");
    buttonOpen->setText(tr("&Open..."));
    buttonOpen->setIcon(QIcon(openPixmap));
    buttonOpen->setObjectName("buttonOpen");
    buttonOpen->setIconSize(fontMetrics.size(Qt::TextShowMnemonic,buttonOpen->text()));
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

void SWelcomePage::on_buttonOpen_clicked()
{
    QString path = QFileDialog::getOpenFileName(this, tr("Open existing file"),
                                                "", tr("Project (*.%1)").arg(extension.isEmpty() ? "*" : extension));
    if (!checkFile(path))
    {
        return;
    }
    else
    {
        openFile(path);
    }
}

void SWelcomePage::updateRecents()
{
    recentsButtons.clear();
    filePaths.clear();
    clearLayout(layout);

    recentsLabel = new QLabel(tr("Recently opened files"), recentsWidget);
    recentsLabel->setObjectName("recentsLabel");
    layout->addWidget(recentsLabel);

    QSettings settings("recentfiles.ini", QSettings::IniFormat);

    const QStringList recentFiles = readRecents(settings);
    const int count = qMin(int(recentsMaxNumber), recentFiles.size());
    if (count == 0)
    {
        QLabel* emptyLabel = new QLabel(tr("No recently opened files. Press \"New...\" to add one, or \"Open...\" to open an existing project."), recentsWidget);
        emptyLabel->setObjectName("emptyLabel");
        layout->addWidget(emptyLabel);
    }
    else
    {
        for (int i = 0; i < count; ++i)
        {
            const QString fileName = strippedName(recentFiles.at(i));
            const QString filePath = QFileInfo(recentFiles.at(i)).canonicalFilePath();
            SCustomButton* recentButton = new SCustomButton((tr("%1. ").arg(i + 1) + fileName), filePath, recentsWidget);
            recentsButtons.append(recentButton);
            filePaths.append(filePath);
            layout->addWidget(recentsButtons.at(i));
            connect(recentButton, SIGNAL(clicked(QString)),this,SLOT(recentFileClicked(QString)));
        }
    }

    layout->addStretch(1);
    recentsWidget->setLayout(layout);
    recentsArea->setWidget(recentsWidget);
    recentsArea->setWidgetResizable(true);
}

QStringList SWelcomePage::readRecents(QSettings &settings)
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

void SWelcomePage::writeRecents(const QStringList &files, QSettings &settings)
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

void SWelcomePage::prependToRecents(const QString &fileName)
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

void SWelcomePage::openFile(const QString &fileName)
{
    prependToRecents(fileName);
    updateRecents();

    emit openExisting(fileName);
}

bool SWelcomePage::checkFile(const QString &path)
{
    if (!fileExists(path))
    {
        return false;
    }
    if (!extension.isEmpty())
    {
        if (QFileInfo(path).completeSuffix() != extension)
        {
            return false;
        }
    }
    return true;
}

QString SWelcomePage::strippedName(const QString &fullFileName)
{
    return QFileInfo(fullFileName).fileName();
}

void SWelcomePage::recentFileClicked(QString path)
{
    openFile(path);
}

bool SWelcomePage::fileExists(const QString &fullFileName)
{
    return QFileInfo::exists(fullFileName) && QFileInfo(fullFileName).isFile();;
}

void SWelcomePage::clearLayout(QLayout *layout)
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
