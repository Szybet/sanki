#include "file_chooser.h"
#include "ui_file_chooser.h"
#include "globals.h"
#include "file.h"

#include <QScrollBar>

file_chooser::file_chooser(QDialog *parent) :
    QDialog(parent),
    ui(new Ui::file_chooser)
{
    ui->setupUi(this);
    this->move(0, 0);
    this->setMinimumSize(global_var::screen_x, global_var::screen_y);
    this->setMaximumSize(global_var::screen_x, global_var::screen_y);
    this->adjustSize();

    ui->frame->setStyleSheet(".QFrame{background-color: white; border: 4px solid black; border-radius: 10px;}");
    // This could be editable in settings
    ui->scrollArea->verticalScrollBar()->setStyleSheet(
        "QScrollBar:vertical { width: 50px; }");
    ui->scrollArea->horizontalScrollBar()->setStyleSheet(
        "QScrollBar:vertical { width: 50px; }");

    ui->ButtonUpPath->setStyleSheet("font-size: 8.5pt");
    ui->ButtonEnterPath->setStyleSheet("font-size: 8.5pt");


}

file_chooser::~file_chooser()
{
    delete ui;
}

void file_chooser::update_files()
{
    ui->lineEditPath->setText(start_path);

    QDir dir = start_path;
    QFileInfoList dir_list = dir.QDir::entryInfoList(QDir::Filters(QDir::AllDirs | QDir::Files), QDir::SortFlag(QDir::Type));
    QString message = "gathered dir_list: ";
    for (QFileInfo file_info: dir_list) {
        if (file_info.baseName() == "") {
            continue;
        }
        message.append(file_info.fileName());
        message.append(",");
    }
    message.append("in: ");
    message.append(start_path);

    global_fun::log(message, log_file, "update_files");

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

        QString message = "added widget: " + file_info.fileName();
        global_fun::log(message, log_file, "update_files");

        file_layout->addWidget(file_button);
    }
    // To align items to the top
    file_layout->setAlignment(Qt::AlignTop);

}

void file_chooser::file_clicked(QString file)
{
    choosed_file = file;
    emit remove_bold();
}

void file_chooser::on_ButtonConfirm_clicked()
{


}

void file_chooser::enter_dir()
{
    emit remove_buttons();
    start_path = start_path + choosed_file;
    update_files();
}

void file_chooser::on_ButtonUpPath_clicked()
{
    emit remove_buttons();
    QDir new_path = start_path;
    new_path.cdUp();
    start_path = new_path.path();

    QString message = "Go up path: ";
    message.append(start_path);
    global_fun::log(message, log_file, "on_ButtonUpPath_clicked");

    update_files();
}

