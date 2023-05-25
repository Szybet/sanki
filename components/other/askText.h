#ifndef ASKTEXT_H
#define ASKTEXT_H

#include <QDialog>
#include <QTimer>

namespace Ui {
class askText;
}

class askText : public QDialog
{
    Q_OBJECT

public:
    explicit askText(QWidget *parent = nullptr);
    ~askText();
    QString* textToSet;

private slots:
    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

private:
    Ui::askText *ui;
    QTimer* timer;
    void manageKeyboards();
    bool overwrite = false;

};

#endif // ASKTEXT_H
