#ifndef SESSION_H
#define SESSION_H

#include <QWidget>

namespace Ui {
class session;
}

class session : public QWidget
{
    Q_OBJECT

public:
    explicit session(QWidget *parent = nullptr);
    ~session();
    void start(QString path);

private:
    Ui::session *ui;
};

#endif // SESSION_H
