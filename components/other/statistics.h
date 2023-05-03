#ifndef STATISTICS_H
#define STATISTICS_H

#include "mainMenu/sessions/sessionStruct.h"

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
    QString getStatsForSession(sessionStr* session, bool lastUsed);

private:
    Ui::statistics *ui;
};

#endif // STATISTICS_H
