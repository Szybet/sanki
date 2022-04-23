/********************************************************************************
** Form generated from reading UI file 'edit_deck.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EDIT_DECK_H
#define UI_EDIT_DECK_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_edit_deck
{
public:
    QGridLayout *gridLayout;
    QFrame *frame;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *ButtonCancelEdit;
    QSpacerItem *horizontalSpacer;
    QPushButton *ButtonSaveExit;
    QLineEdit *lineEditDeckName;
    QHBoxLayout *horizontalLayout;
    QPushButton *ButtonReset;
    QSpacerItem *horizontalSpacer_4;
    QPushButton *ButtonRemoveDeck;

    void setupUi(QDialog *edit_deck)
    {
        if (edit_deck->objectName().isEmpty())
            edit_deck->setObjectName(QString::fromUtf8("edit_deck"));
        edit_deck->resize(400, 152);
        gridLayout = new QGridLayout(edit_deck);
        gridLayout->setSpacing(0);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        frame = new QFrame(edit_deck);
        frame->setObjectName(QString::fromUtf8("frame"));
        frame->setFrameShape(QFrame::Box);
        frame->setFrameShadow(QFrame::Plain);
        frame->setLineWidth(4);
        verticalLayout = new QVBoxLayout(frame);
        verticalLayout->setSpacing(5);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(10, 10, 10, 10);
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalLayout_2->setSizeConstraint(QLayout::SetMinimumSize);
        ButtonCancelEdit = new QPushButton(frame);
        ButtonCancelEdit->setObjectName(QString::fromUtf8("ButtonCancelEdit"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(ButtonCancelEdit->sizePolicy().hasHeightForWidth());
        ButtonCancelEdit->setSizePolicy(sizePolicy);

        horizontalLayout_2->addWidget(ButtonCancelEdit);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);

        ButtonSaveExit = new QPushButton(frame);
        ButtonSaveExit->setObjectName(QString::fromUtf8("ButtonSaveExit"));
        QSizePolicy sizePolicy1(QSizePolicy::MinimumExpanding, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(ButtonSaveExit->sizePolicy().hasHeightForWidth());
        ButtonSaveExit->setSizePolicy(sizePolicy1);

        horizontalLayout_2->addWidget(ButtonSaveExit);


        verticalLayout->addLayout(horizontalLayout_2);

        lineEditDeckName = new QLineEdit(frame);
        lineEditDeckName->setObjectName(QString::fromUtf8("lineEditDeckName"));
        lineEditDeckName->setTabletTracking(false);
        lineEditDeckName->setFocusPolicy(Qt::ClickFocus);

        verticalLayout->addWidget(lineEditDeckName);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setSizeConstraint(QLayout::SetMinimumSize);
        ButtonReset = new QPushButton(frame);
        ButtonReset->setObjectName(QString::fromUtf8("ButtonReset"));
        QSizePolicy sizePolicy2(QSizePolicy::Minimum, QSizePolicy::Minimum);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(ButtonReset->sizePolicy().hasHeightForWidth());
        ButtonReset->setSizePolicy(sizePolicy2);

        horizontalLayout->addWidget(ButtonReset);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_4);

        ButtonRemoveDeck = new QPushButton(frame);
        ButtonRemoveDeck->setObjectName(QString::fromUtf8("ButtonRemoveDeck"));
        sizePolicy2.setHeightForWidth(ButtonRemoveDeck->sizePolicy().hasHeightForWidth());
        ButtonRemoveDeck->setSizePolicy(sizePolicy2);

        horizontalLayout->addWidget(ButtonRemoveDeck);


        verticalLayout->addLayout(horizontalLayout);


        gridLayout->addWidget(frame, 1, 0, 1, 1);


        retranslateUi(edit_deck);

        QMetaObject::connectSlotsByName(edit_deck);
    } // setupUi

    void retranslateUi(QDialog *edit_deck)
    {
        edit_deck->setWindowTitle(QCoreApplication::translate("edit_deck", "Form", nullptr));
        ButtonCancelEdit->setText(QCoreApplication::translate("edit_deck", "Cancel", nullptr));
        ButtonSaveExit->setText(QCoreApplication::translate("edit_deck", "Save and Exit", nullptr));
        ButtonReset->setText(QCoreApplication::translate("edit_deck", "Reset deck", nullptr));
        ButtonRemoveDeck->setText(QCoreApplication::translate("edit_deck", "Remove deck", nullptr));
    } // retranslateUi

};

namespace Ui {
    class edit_deck: public Ui_edit_deck {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EDIT_DECK_H
