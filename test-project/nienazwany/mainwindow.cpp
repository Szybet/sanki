#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QWidget>
#include <QPushButton>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::add_widget(QWidget* x)
{
    //ui->scrollArea->addScrollBarWidget(x, Qt::AlignLeft);
    for (int i = 0; i < 10; ++i) {
            QPushButton* button = new QPushButton();
            button->setText(QString::number(i));
            ui->scrollArea->addScrollBarWidget(button, Qt::AlignLeft);

    }

}

