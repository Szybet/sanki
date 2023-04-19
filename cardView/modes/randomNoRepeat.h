#ifndef RANDOMNOREPEAT_H
#define RANDOMNOREPEAT_H

#include <QObject>

class randomNoRepeat: public QObject
{
    Q_OBJECT
public:
    explicit randomNoRepeat(QObject *parent = nullptr);
public:
    randomNoRepeat();
};

#endif // RANDOMNOREPEAT_H
