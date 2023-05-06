#ifndef ASKFORBOXESOPTIONS_H
#define ASKFORBOXESOPTIONS_H

#include "cardView/modes/boxes/boxes.h"

#include <QWidget>
#include <QDialog>

namespace Ui {
class askForBoxesOptions;
}

class askForBoxesOptions : public QDialog
{
    Q_OBJECT

public:
    explicit askForBoxesOptions(QWidget *parent = nullptr);
    ~askForBoxesOptions();
    void start(boxes* parentArg);
    boxes* parent;
private slots:
    void on_acceptButton_clicked();

    void on_infoButton_clicked();

    void on_againSpinBox_valueChanged(int arg1);

    void on_hardSpinBox_2_valueChanged(int arg1);

    void on_goodSpinBox_3_valueChanged(int arg1);

    void on_easySpinBox_4_valueChanged(int arg1);

    void on_boxesSpinBox_valueChanged(int arg1);

    void on_skipSpinBox_valueChanged(int arg1);

private:
    Ui::askForBoxesOptions *ui;
};

#endif // ASKFORBOXESOPTIONS_H
