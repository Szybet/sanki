/********************************************************************************
** Form generated from reading UI file 'widgget.ui'
**
** Created by: Qt User Interface Compiler version 5.15.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WIDGGET_H
#define UI_WIDGGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLCDNumber>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_widgget
{
public:
    QHBoxLayout *horizontalLayout;
    QLCDNumber *lcdNumber;

    void setupUi(QWidget *widgget)
    {
        if (widgget->objectName().isEmpty())
            widgget->setObjectName(QString::fromUtf8("widgget"));
        widgget->resize(400, 300);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(100);
        sizePolicy.setVerticalStretch(100);
        sizePolicy.setHeightForWidth(widgget->sizePolicy().hasHeightForWidth());
        widgget->setSizePolicy(sizePolicy);
        widgget->setMinimumSize(QSize(100, 100));
        horizontalLayout = new QHBoxLayout(widgget);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        lcdNumber = new QLCDNumber(widgget);
        lcdNumber->setObjectName(QString::fromUtf8("lcdNumber"));
        lcdNumber->setMinimumSize(QSize(100, 100));
        lcdNumber->setMaximumSize(QSize(100, 100));

        horizontalLayout->addWidget(lcdNumber);


        retranslateUi(widgget);

        QMetaObject::connectSlotsByName(widgget);
    } // setupUi

    void retranslateUi(QWidget *widgget)
    {
        widgget->setWindowTitle(QCoreApplication::translate("widgget", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class widgget: public Ui_widgget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGGET_H
