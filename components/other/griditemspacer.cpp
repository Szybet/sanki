#include "griditemspacer.h"
#include "ui_griditemspacer.h"

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
    }
}

void gridItemSpacer::on_addButton_clicked()
{
    emit addItem();
}

