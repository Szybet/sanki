#include "global.h"
#include "griditemspacer.h"
#include "ui_griditemspacer.h"

#include <QDebug>

gridItemSpacer::gridItemSpacer(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::gridItemSpacer)
{
    ui->setupUi(this);
    this->setAttribute(Qt::WA_DeleteOnClose);
}

gridItemSpacer::~gridItemSpacer()
{
    delete ui;
}

void gridItemSpacer::selectPage(Page pageSel) {
    if(pageSel == Empty) {
        ui->stackedWidget->setCurrentWidget(ui->emptyPage_1);
    } else if(pageSel == Add) {
        ui->stackedWidget->setCurrentWidget(ui->addPage_2);
        if(ereader) {
            qDebug() << "Setting ereader sizes for grid item spacer";
            ui->addButton->setStyleSheet("font-size: 20pt");
            ui->addButton->setFixedSize(QSize(120, 120));
            ui->addButton->setStyleSheet("border-color: black; border-width: 3;");
        }
    }
}

void gridItemSpacer::on_addButton_clicked()
{
    emit addItem();
}

