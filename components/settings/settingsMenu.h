#ifndef SETTINGSMENU_H
#define SETTINGSMENU_H

#include <QWidget>

namespace Ui {
class settingsMenu;
}

class settingsMenu : public QWidget
{
    Q_OBJECT

public:
    explicit settingsMenu(QWidget *parent = nullptr);
    ~settingsMenu();

private:
    Ui::settingsMenu *ui;
};

#endif // SETTINGSMENU_H
