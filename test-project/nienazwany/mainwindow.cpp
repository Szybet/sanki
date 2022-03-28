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

            QLayout* scrollbar_layout = ui->scrollAreaWidgetContents->layout();
            scrollbar_layout->addWidget(x);

}

