#ifndef QGRAPHICSVIEWEVENTS_H
#define QGRAPHICSVIEWEVENTS_H

#include <QGraphicsView>
#include <QEvent>
#include <QKeyEvent>
#include <QMouseEvent>
#include <QWheelEvent>
#include <QDebug>
#include <QGestureEvent>

class qGraphicsViewEvents : public QGraphicsView
{
    Q_OBJECT
public:
    explicit qGraphicsViewEvents(QWidget* parent = nullptr);

signals:
    void eventSignal(QEvent* event);

protected:
    bool event(QEvent* event) override {
        //qDebug() << "event:" << event;

        if (event->type() == QEvent::Gesture || event->type() == QEvent::GestureOverride) {
            // Idk why but i need to transform it here?
            //qDebug() << "Sending gesture from qGraphicsViewEvents";
            //QGestureEvent *gestureEvent = static_cast<QGestureEvent*>(event);
            //qDebug() << "in view gestureEvent" << gestureEvent;
            emit eventSignal(event); // needed to track further gesture
            return true;
        } else {
            //qDebug() << "It's not a gesture?" << event->type();
        }

        return QGraphicsView::event(event);
    }

    /*
    virtual void keyPressEvent(QKeyEvent* event) override
    {
        // Display information about the key press event
        //qDebug() << event;

        // Call the base class implementation to handle the event
        QGraphicsView::keyPressEvent(event);
    }

    virtual void mousePressEvent(QMouseEvent* event) override
    {
        // Display information about the mouse press event
        //qDebug() << "mousePressEvent:" << event;

        // Call the base class implementation to handle the event
        QGraphicsView::mousePressEvent(event);
    }

    virtual void wheelEvent(QWheelEvent* event) override
    {
        // Display information about the wheel event
        //qDebug() << event;

        // Call the base class implementation to handle the event
        QGraphicsView::wheelEvent(event);
    }
*/
};


#endif // QGRAPHICSVIEWEVENTS_H
