#ifndef GRIDITEMSPACER_H
#define GRIDITEMSPACER_H

#include <QWidget>

namespace Ui {
class gridItemSpacer;
}

class gridItemSpacer : public QWidget
{
    Q_OBJECT

public:
    explicit gridItemSpacer(QWidget *parent = nullptr);
    ~gridItemSpacer();
    enum Page {
        Empty,
        Add,
    };
    void selectPage(Page pageSel);

signals:
    void addItem();

private slots:
    void on_addButton_clicked();

private:
    Ui::gridItemSpacer *ui;
};

#endif // GRIDITEMSPACER_H
