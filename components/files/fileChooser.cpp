#include "fileChooser.h"
#include "qdebug.h"
#include "ui_fileChooser.h"
#include "global.h"
#include "file.h"
#include "components/other/keyboard.h"

#include <QScrollBar>

fileChooserCustom::fileChooserCustom(QDialog *parent) :
    QDialog(parent),
    ui(new Ui::fileChooserCustom)
{
    ui->setupUi(this);

    // ("border: 0px solid black; border-radius: 0px;");

    // This could be editable in settings
    ui->scrollArea->verticalScrollBar()->setStyleSheet(
        "QScrollBar:vertical { width: 50px; }");
    ui->scrollArea->horizontalScrollBar()->setStyleSheet(
        "QScrollBar:vertical { width: 50px; }");

    ui->ButtonUpPath->setStyleSheet("font-size: 9.5pt");

    // This is becouse the QDialog has borders
    this->setStyleSheet("QDialog {border: 0px solid black; border-radius: 0px; background: white;}");
    ui->lineEditPath->setCursorPosition(20);
}

fileChooserCustom::~fileChooserCustom()
{
    delete ui;
}

void fileChooserCustom::updateFiles()
{
    keyboardOpened = true;
    ui->lineEditPath->setText(start_path);
    ui->lineEditPath->setCursorPosition(0);
    keyboardOpened = false;

    emit remove_buttons();
    QDir dir = start_path;
    QFileInfoList dir_list = dir.QDir::entryInfoList(QDir::Filters(QDir::AllDirs | QDir::Files), QDir::SortFlag(QDir::Type));

    qDebug() << "Gathered dir_list:" << dir_list;

    QVBoxLayout* file_layout = ui->layoutFiles;

    for (QFileInfo file_info: dir_list) {
        // Becouse of ".." and "."
        if (file_info.baseName() == "") {
            continue;
        }
        file* file_button = new file;

        if(file_info.isSymLink() == true or file_info.isSymbolicLink() == true)
        {
            continue;

        } if(file_info.isDir() == true)
        {
            file_button->is_directory = true;
            QIcon icon = QIcon(":/icons/folder.png");
            file_button->set_button_look(file_info.fileName() + "/", icon);
        } else if(file_info.fileName().contains(".apkg")) {
            QIcon icon = QIcon(":/icons/apkg_file.png");
            file_button->set_button_look(file_info.fileName(), icon);
        } else {
            QIcon icon = QIcon("NONE");
            file_button->set_button_look(file_info.fileName(), icon);
        }


        connect(this, SIGNAL(remove_buttons()), file_button, SLOT(close()));
        connect(file_button, SIGNAL(im_clicked(QString)), this, SLOT(file_clicked(QString)));
        connect(this, SIGNAL(remove_bold()), file_button, SLOT(remove_bold()));
        connect(file_button, SIGNAL(enter_dir()), this, SLOT(enter_dir()));

        qDebug() << "added widget:" << file_info.fileName();

        file_layout->addWidget(file_button);
    }
    // To align items to the top
    file_layout->setAlignment(Qt::AlignTop);

}

void fileChooserCustom::file_clicked(QString file)
{
    choosed_file = file;
    emit remove_bold();
}

void fileChooserCustom::on_ButtonConfirm_clicked()
{
    if(choosed_file.contains(file_extension) == true)
    {
        // becouse if start_path is "/" it will be "//"
        if(start_path.end() != QString("/"))
        {
            emit provideFile(start_path + choosed_file);
        } else {
            emit provideFile(start_path + "/" + choosed_file);
        }
        this->close();
    } else {
        qWarning() << "Choose a file with" << file_extension << " extension";
    }
}

void fileChooserCustom::on_ButtonCancel_clicked()
{
    emit provideFile("");
    this->close();
}

void fileChooserCustom::enter_dir()
{
    start_path = start_path + choosed_file;
    updateFiles();
}

void fileChooserCustom::on_ButtonUpPath_clicked()
{
    emit remove_buttons();
    QDir new_path = start_path;
    new_path.cdUp();
    start_path = new_path.path();

    qDebug() << "Go up path:" << start_path;

    updateFiles();
}

// Everything for keyboard:

void fileChooserCustom::on_lineEditPath_selectionChanged()
{
    ui->lineEditPath->setSelection(0, 0);
}

void fileChooserCustom::keyboardClosed(bool updateName)
{
    if(updateName == true)
    {
        updatedName = true;
    }
    ui->lineEditPath->setText(ui->lineEditPath->text().remove("|"));
    keyboardOpened = false;

    start_path = ui->lineEditPath->text();
    updateFiles();
}

void fileChooserCustom::on_lineEditPath_cursorPositionChanged(int oldpos, int newpos)
{
    if(firstOpen == false)
    {
        if(keyboardOpened == false)
        {
            if(newpos != 0)
            {

                keyboard* keyboard_nameedit = new keyboard;
                keyboard_nameedit->cursor_main = newpos;
                keyboard_nameedit->main_string = ui->lineEditPath->text();
                keyboard_nameedit->edited_string = ui->lineEditPath->text();
                connect(keyboard_nameedit, SIGNAL(update_data(QString, int)), this, SLOT(updateWidget(QString, int)));
                connect(keyboard_nameedit, SIGNAL(keyboardClosed(bool)), this, SLOT(keyboardClosed(bool)));
                keyboardOpened = true;
                updateWidget(ui->lineEditPath->text(), ui->lineEditPath->cursorPosition()); // to create the cursor
                keyboard_nameedit->exec();
            }
        }
    } else {
        ui->lineEditPath->setCursorPosition(0);
        firstOpen = false;
    }
}

void fileChooserCustom::updateDeck()
{
    QString deck_name = deckInfo.baseName();
    ui->lineEditPath->setText(deck_name);
}

void fileChooserCustom::updateWidget(QString string, int cursor)
{
         // Adding cursor, this is so stupid
         QString string_with_cursor = string;
         if(cursor == 0)
         {
             if(string == "")
             {
                 ui->lineEditPath->setText(" ");
             }
             string_with_cursor.insert(cursor, "|");
         } else {
             string_with_cursor.insert(cursor, "|");
         }

         ui->lineEditPath->setText(string_with_cursor);
         ui->lineEditPath->setCursorPosition(cursor);
}
