#include "lineEditVirtualKeyboard.h"

#include <QGuiApplication>

LineEdit::LineEdit(QWidget *parent) :QLineEdit(parent) {
    setAttribute(Qt::WA_InputMethodEnabled, true);
    setInputMethodHints(inputMethodHints() | Qt::InputMethodHint::ImhDigitsOnly);
}

LineEdit::LineEdit(const QString& txt, QWidget *parent) : QLineEdit(txt, parent) {
    setAttribute(Qt::WA_InputMethodEnabled, true);
    setInputMethodHints(inputMethodHints() | Qt::InputMethodHint::ImhDigitsOnly);
}

bool LineEdit::event(QEvent* e) {
    const auto keyboard_rect = QGuiApplication::inputMethod()->keyboardRectangle();
    const auto keyboard_visible = QGuiApplication::inputMethod()->isVisible();
    const auto global_y = QWidget::mapToGlobal(rect().topLeft()).y() + height();
    const auto k_global_y = keyboard_rect.topLeft().y();
    const auto diff = k_global_y - global_y;
    const auto need_to_move = diff < 0;

    QGuiApplication::inputMethod()->show();

    /* move main widget */
    if (keyboard_visible && !_moved && need_to_move) {
        _moved = true;
        _lastDiff = diff;
        const auto g = parentWidget()->frameGeometry();
        parentWidget()->move(g.x(), g.y() - qAbs(_lastDiff));
    }
    /* roll back */
    if (!keyboard_visible && _moved) {
        _moved = false;
        const auto g = parentWidget()->frameGeometry();
        parentWidget()->move(g.x(), g.y() + qAbs(_lastDiff));
    }
    return QLineEdit::event(e);
}
