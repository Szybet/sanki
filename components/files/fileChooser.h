#ifndef fileChooserCustom_H
#define fileChooserCustom_H

#include <QDialog>
#include <QFileInfo>
#include <QVBoxLayout>
#include <QTimer>

namespace Ui {
class fileChooserCustom;
}

class fileChooserCustom : public QDialog
{
    Q_OBJECT

public:
    explicit fileChooserCustom(QDialog *parent = nullptr);
    ~fileChooserCustom();
    void start(QString fileExtensionProvided);

public slots:
    void updateFiles();
    void FileClicked(QString file);
    void enterDirectory();

signals:
    void removeBold();
    void provideFile(QString file);
    void removeButtons();

private slots:
    void on_ButtonConfirm_clicked();
    void on_ButtonCancel_clicked();
    void on_ButtonUpPath_clicked();

private:
    Ui::fileChooserCustom *ui;
    QString choosedFile;
    QString startPath;
    QString fileExtension;
    void manageKeyboards();
    QTimer* timer;

};

#endif // fileChooserCustom_H
