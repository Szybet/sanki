#ifndef ASKFORTEXT_H
#define ASKFORTEXT_H

#include <QDialog>

namespace Ui {
class askForText;
}

class askForText : public QDialog
{
    Q_OBJECT

public:
    explicit askForText(QWidget *parent = nullptr);
    ~askForText();

private:
    Ui::askForText *ui;
};

#endif // ASKFORTEXT_H
