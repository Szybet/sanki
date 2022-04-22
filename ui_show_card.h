/********************************************************************************
** Form generated from reading UI file 'show_card.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SHOW_CARD_H
#define UI_SHOW_CARD_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_show_card
{
public:
    QGridLayout *gridLayout;
    QPushButton *pushButton;

    void setupUi(QWidget *show_card)
    {
        if (show_card->objectName().isEmpty())
            show_card->setObjectName(QString::fromUtf8("show_card"));
        show_card->resize(400, 300);
        gridLayout = new QGridLayout(show_card);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        pushButton = new QPushButton(show_card);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(pushButton->sizePolicy().hasHeightForWidth());
        pushButton->setSizePolicy(sizePolicy);

        gridLayout->addWidget(pushButton, 0, 0, 1, 1);


        retranslateUi(show_card);

        QMetaObject::connectSlotsByName(show_card);
    } // setupUi

    void retranslateUi(QWidget *show_card)
    {
        show_card->setWindowTitle(QCoreApplication::translate("show_card", "Form", nullptr));
        pushButton->setText(QCoreApplication::translate("show_card", "Show card", nullptr));
    } // retranslateUi

};

namespace Ui {
    class show_card: public Ui_show_card {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SHOW_CARD_H
