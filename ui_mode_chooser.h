/********************************************************************************
** Form generated from reading UI file 'mode_chooser.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MODE_CHOOSER_H
#define UI_MODE_CHOOSER_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_mode_chooser
{
public:
    QGridLayout *gridLayout_2;
    QVBoxLayout *verticalLayout;
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout_2;
    QRadioButton *ButtonCRandom;
    QPushButton *ButtonConfirm;

    void setupUi(QDialog *mode_chooser)
    {
        if (mode_chooser->objectName().isEmpty())
            mode_chooser->setObjectName(QString::fromUtf8("mode_chooser"));
        mode_chooser->resize(300, 114);
        gridLayout_2 = new QGridLayout(mode_chooser);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        groupBox = new QGroupBox(mode_chooser);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setLayoutDirection(Qt::LeftToRight);
        groupBox->setAlignment(Qt::AlignCenter);
        groupBox->setFlat(false);
        verticalLayout_2 = new QVBoxLayout(groupBox);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        ButtonCRandom = new QRadioButton(groupBox);
        ButtonCRandom->setObjectName(QString::fromUtf8("ButtonCRandom"));

        verticalLayout_2->addWidget(ButtonCRandom);


        verticalLayout->addWidget(groupBox);


        gridLayout_2->addLayout(verticalLayout, 0, 0, 1, 1);

        ButtonConfirm = new QPushButton(mode_chooser);
        ButtonConfirm->setObjectName(QString::fromUtf8("ButtonConfirm"));

        gridLayout_2->addWidget(ButtonConfirm, 1, 0, 1, 1);


        retranslateUi(mode_chooser);

        QMetaObject::connectSlotsByName(mode_chooser);
    } // setupUi

    void retranslateUi(QDialog *mode_chooser)
    {
        mode_chooser->setWindowTitle(QCoreApplication::translate("mode_chooser", "Form", nullptr));
        groupBox->setTitle(QCoreApplication::translate("mode_chooser", "Choose your mode:", nullptr));
        ButtonCRandom->setText(QCoreApplication::translate("mode_chooser", "Completly randomised", nullptr));
        ButtonConfirm->setText(QCoreApplication::translate("mode_chooser", "Confirm", nullptr));
    } // retranslateUi

};

namespace Ui {
    class mode_chooser: public Ui_mode_chooser {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MODE_CHOOSER_H
