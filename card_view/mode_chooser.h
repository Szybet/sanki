#ifndef MODE_CHOOSER_H
#define MODE_CHOOSER_H

#include "globals.h"
#include <QDialog>

namespace Ui {
class mode_chooser;
}

class mode_chooser : public QDialog
{
    Q_OBJECT

public:
    explicit mode_chooser(QDialog *parent = nullptr);
    ~mode_chooser();

signals:
    void setMode(DeckModes mode);

private slots:
    void on_ButtonConfirm_clicked();
    void on_ButtonRandomNR_clicked();
    void on_ButtonCRandom_clicked();

private:
    Ui::mode_chooser *ui;
    DeckModes mode = None;
    void modeManager(DeckModes newMode);
};

#endif // MODE_CHOOSER_H
