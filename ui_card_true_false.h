/********************************************************************************
** Form generated from reading UI file 'card_true_false.ui'
**
** Created by: Qt User Interface Compiler version 5.15.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CARD_TRUE_FALSE_H
#define UI_CARD_TRUE_FALSE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_card_true_false
{
public:
    QHBoxLayout *horizontalLayout_2;
    QHBoxLayout *horizontalLayout;
    QPushButton *pushButton_2;
    QPushButton *pushButton;

    void setupUi(QWidget *card_true_false)
    {
        if (card_true_false->objectName().isEmpty())
            card_true_false->setObjectName(QString::fromUtf8("card_true_false"));
        card_true_false->resize(400, 300);
        horizontalLayout_2 = new QHBoxLayout(card_true_false);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        pushButton_2 = new QPushButton(card_true_false);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(pushButton_2->sizePolicy().hasHeightForWidth());
        pushButton_2->setSizePolicy(sizePolicy);

        horizontalLayout->addWidget(pushButton_2);

        pushButton = new QPushButton(card_true_false);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        sizePolicy.setHeightForWidth(pushButton->sizePolicy().hasHeightForWidth());
        pushButton->setSizePolicy(sizePolicy);

        horizontalLayout->addWidget(pushButton);


        horizontalLayout_2->addLayout(horizontalLayout);


        retranslateUi(card_true_false);

        QMetaObject::connectSlotsByName(card_true_false);
    } // setupUi

    void retranslateUi(QWidget *card_true_false)
    {
        card_true_false->setWindowTitle(QCoreApplication::translate("card_true_false", "Form", nullptr));
        pushButton_2->setText(QCoreApplication::translate("card_true_false", "PushButton", nullptr));
        pushButton->setText(QCoreApplication::translate("card_true_false", "PushButton", nullptr));
    } // retranslateUi

};

namespace Ui {
    class card_true_false: public Ui_card_true_false {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CARD_TRUE_FALSE_H
