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

void MainWindow::add_widget(QWidget* x, int i)
{
    QGridLayout* scrollbar_layout = ui->grid3;


            scrollbar_layout->addWidget(x,i,i,i,i);
}

void MainWindow::add_widgetleft(QWidget* x, int i)
{
    QGridLayout* scrollbar_layout = ui->grid3;



            scrollbar_layout->addWidget(x,1,1,i,i);

}
