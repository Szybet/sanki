#ifndef QGRAPHICSSCENEEVENTS_H
#define QGRAPHICSSCENEEVENTS_H

#include <QGraphicsScene>
#include <QEvent>
#include <QKeyEvent>
#include <QMouseEvent>
#include <QWheelEvent>
#include <QDebug>
#include <QGestureEvent>

class qGraphicsSceneEvents : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit qGraphicsSceneEvents(QWidget* parent = nullptr);

signals:
    void eventSignal(QEvent* event);

protected:
    bool event(QEvent* event) override {
        //qDebug() << "event:" << event;

        if (event->type() == QEvent::Gesture || event->type() == QEvent::GestureOverride) {
            // Idk why but i need to transform it here?
            //qDebug() << "Sending gesture from qGraphicsViewEvents";
            //QGestureEvent *gestureEvent = static_cast<QGestureEvent*>(event);
            //qDebug() << "In scene gestureEvent" << gestureEvent;
            emit eventSignal(event);
            return true; // needed to track further gesture
        } else {
            //qDebug() << "It's not a gesture?" << event->type();
        }

        return QGraphicsScene::event(event);
    }
};

#endif // QGRAPHICSSCENEEVENTS_H
