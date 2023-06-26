#include "fileChooser.h"
#include "qdebug.h"
#include "ui_fileChooser.h"
#include "global.h"
#include "file.h"
#include "components/other/keyboard.h"

#include <QScrollBar>
#include <QTimer>

fileChooserCustom::fileChooserCustom(QDialog *parent) :
    QDialog(parent),
    ui(new Ui::fileChooserCustom)
{
    ui->setupUi(this);
    this->setAttribute(Qt::WA_DeleteOnClose);

    // This could be editable in settings
    ui->scrollArea->verticalScrollBar()->setStyleSheet(
        "QScrollBar:vertical { width: 50px; }");
    ui->scrollArea->horizontalScrollBar()->setStyleSheet(
        "QScrollBar:vertical { width: 50px; }");

    ui->ButtonUpPath->setStyleSheet("font-size: 9.5pt");

    // This is because the QDialog has borders
    this->setStyleSheet("QDialog {border: 0px solid black; border-radius: 0px; background: white;}");
    ui->lineEditPath->setCursorPosition(20);

    ui->layoutFiles->setAlignment(Qt::AlignTop);

    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &fileChooserCustom::manageKeyboards);
    timer->start(800);
}

fileChooserCustom::~fileChooserCustom()
{
    delete ui;
}

void fileChooserCustom::start(QString fileExtensionProvided) {
    fileExtension = fileExtensionProvided;
    startPath = directories::fileSelect.path();
    if(startPath.endsWith(QDir::separator()) == false) {
        startPath = startPath + "/";
    }
    ui->lineEditPath->setText(startPath);
    this->setFixedSize(ereaderVars::screenX, ereaderVars::screenY);
    this->move(0, 0);
    updateFiles();
}

void fileChooserCustom::updateFiles()
{
    emit removeButtons();
    ui->lineEditPath->setText(startPath);
    QDir dir = startPath;
    QFileInfoList dirList = dir.QDir::entryInfoList(QDir::Filters(QDir::AllDirs | QDir::Files), QDir::SortFlag(QDir::Type));

    qDebug() << "Gathered dirList:" << dirList;

    QVBoxLayout* fileLayout = ui->layoutFiles;

    foreach(QFileInfo fileInfo, dirList) {
        // Because of ".." and "."
        if(fileInfo.isSymLink() == true || fileInfo.isSymbolicLink() == true || fileInfo.baseName().isEmpty())
        {
            continue;
        }

        file* fileButton = new file(this);
        QIcon icon;
        if(fileInfo.isDir() == true) {
            icon = QIcon(":/icons/folder.svg");
        } else if(fileInfo.fileName().contains(".apkg")) {
            icon = QIcon(":/icons/apkgFile.png");
        }  else if(fileInfo.fileName().contains(".zip")) {
            icon = QIcon(":/icons/folderZip.svg");
        } else {
            icon = QIcon("NONE");
        }
        fileButton->start(fileInfo.isDir(), fileInfo.fileName(), icon);

        connect(this, &fileChooserCustom::removeButtons, fileButton, &file::close);
        connect(fileButton, &file::fileClicked, this, &fileChooserCustom::FileClicked);
        connect(this, &fileChooserCustom::removeBold, fileButton, &file::removeBold);
        connect(fileButton, &file::enterDirectory, this, &fileChooserCustom::enterDirectory);

        qDebug() << "Added widget:" << fileInfo.fileName();

        fileLayout->addWidget(fileButton);
    }
}

void fileChooserCustom::FileClicked(QString file)
{
    choosedFile = file;
    emit removeBold();
}

void fileChooserCustom::on_ButtonConfirm_clicked()
{
    if(choosedFile.contains(fileExtension) == true)
    {
        // Because if startPath is "/" it will be "//"
        if(startPath.endsWith(QDir::separator()) == true)
        {
            emit provideFile(startPath + choosedFile);
        } else {
            emit provideFile(startPath + QDir::separator() + choosedFile);
        }
        this->close();
    } else {
        qWarning() << "Choose a file with" << fileExtension << "extension";
    }
}

void fileChooserCustom::on_ButtonCancel_clicked()
{
    emit provideFile("");
    this->close();
}

void fileChooserCustom::enterDirectory()
{
    if(startPath == "/") {
        startPath = startPath + choosedFile;
    } else {
        startPath = startPath + QDir::separator() + choosedFile;
    }

    updateFiles();
}

void fileChooserCustom::on_ButtonUpPath_clicked()
{
    emit removeButtons();
    QDir newPath = startPath;
    newPath.cdUp();
    startPath = newPath.path();
    qDebug() << "Go up path:" << startPath;
    updateFiles();
}

void fileChooserCustom::manageKeyboards() {
    QLineEdit* textEditToCheck = ui->lineEditPath;
    if(textEditToCheck->underMouse() == true && textEditToCheck->hasFocus() == true) {
        QString old = textEditToCheck->text();

        keyboard* ereaderKeyboard = new keyboard(this);
        ereaderKeyboard->start(textEditToCheck);
        ereaderKeyboard->exec();
        textEditToCheck->clearFocus();

        if(QDir(textEditToCheck->text()).exists() == false) {
            qWarning() << "Such directory doesn't exist";
            textEditToCheck->setText(old);
        } else {
            startPath = textEditToCheck->text();
            updateFiles();
        }
        return void();
    }
}
