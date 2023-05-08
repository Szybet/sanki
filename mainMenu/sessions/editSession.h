#ifndef EDITSESSION_H
#define EDITSESSION_H

#include <QDialog>

namespace Ui {
class editSession;
}

class editSession : public QDialog
{
    Q_OBJECT

public:
    explicit editSession(QWidget *parent = nullptr);
    ~editSession();

private:
    Ui::editSession *ui;
};

#endif // EDITSESSION_H
