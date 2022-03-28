#ifndef WIDGGET_H
#define WIDGGET_H

#include <QWidget>

namespace Ui {
class widgget;
}

class widgget : public QWidget
{
    Q_OBJECT

public:
    explicit widgget(QWidget *parent = nullptr);
    ~widgget();
    QWidget returnit();

private:
    Ui::widgget *ui;
};

#endif // WIDGGET_H
