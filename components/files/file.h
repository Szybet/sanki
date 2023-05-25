#ifndef FILE_H
#define FILE_H

#include <QIcon>
#include <QWidget>

namespace Ui {
class file;
}

class file : public QWidget
{
    Q_OBJECT

public:
    explicit file(QWidget *parent = nullptr);
    ~file();
    void start(bool isDirectoryProvided, QString fileName, QIcon icon);

signals:
    void fileClicked(QString);
    void enterDirectory();

public slots:
    void removeBold();

private slots:
    void on_pushButton_clicked();

private:
    Ui::file *ui;
    bool ignoreRemoveBoldSignal = false;
    bool isDirectory;
};

#endif // FILE_H
