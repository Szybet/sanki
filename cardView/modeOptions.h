#ifndef modeChooser_H
#define modeChooser_H

#include "global.h"
#include <QDialog>

namespace Ui {
class modeChooser;
}

class modeChooser : public QDialog
{
    Q_OBJECT

public:
    explicit modeChooser(QDialog *parent = nullptr);
    ~modeChooser();

signals:
    void setMode(DeckModes mode);

private slots:
    void on_ButtonConfirm_clicked();
    void on_ButtonRandomNR_clicked();
    void on_ButtonCRandom_clicked();

    void on_ButtonBoxes_clicked();

private:
    Ui::modeChooser *ui;
    DeckModes mode = None;
    void modeManager(DeckModes newMode);
};

#endif // modeChooser_H
