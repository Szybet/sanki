#ifndef STATISTICS_H
#define STATISTICS_H

#include "mainMenu/sessions/sessionStruct.h"

#include <QChartView>
#include <QDialog>

namespace Ui {
class statistics;
}

class statistics : public QDialog
{
    Q_OBJECT

public:
    explicit statistics(QWidget *parent = nullptr);
    ~statistics();
    void start(sessionStr session);
    void setUpChart(QtCharts::QChartView* chart, QString title);

private slots:
    void on_exitButton_clicked();

private:
    Ui::statistics *ui;
};

#endif // STATISTICS_H
