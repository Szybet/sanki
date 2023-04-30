#ifndef fancyGrid_H
#define fancyGrid_H

#include <QWidget>
#include <QDir>
#include <QLayout>

namespace Ui {
class fancyGrid;
}

class fancyGrid : public QWidget
{
    Q_OBJECT

public:
    explicit fancyGrid(QWidget *parent = nullptr);
    ~fancyGrid();
    void reset();
    void addWidget(QWidget* widget);
    QList<QWidget*> widgets;
    void show();

public slots:
    void addItemSlot();

signals:
    void selectedItem(QString path);
    void addItem();
    void clearItems();

private:
    Ui::fancyGrid *ui;
    int column = 0;
    int row = 0;
    void manageCells();
};

#endif // fancyGrid_H
