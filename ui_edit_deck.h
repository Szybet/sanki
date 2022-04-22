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
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_edit_deck
{
public:
    QGridLayout *gridLayout;
    QHBoxLayout *horizontalLayout;
    QPushButton *ButtonReset;
    QFrame *line_3;
    QPushButton *ButtonRemoveDeck;
    QFrame *line_2;
    QTextEdit *textEditDeckName;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *ButtonCancelEdit;
    QSpacerItem *horizontalSpacer_2;
    QFrame *line;
    QSpacerItem *horizontalSpacer;
    QPushButton *ButtonSaveExit;

    void setupUi(QWidget *edit_deck)
    {
        if (edit_deck->objectName().isEmpty())
            edit_deck->setObjectName(QString::fromUtf8("edit_deck"));
        edit_deck->resize(400, 152);
        gridLayout = new QGridLayout(edit_deck);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setSizeConstraint(QLayout::SetMinimumSize);
        ButtonReset = new QPushButton(edit_deck);
        ButtonReset->setObjectName(QString::fromUtf8("ButtonReset"));
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(ButtonReset->sizePolicy().hasHeightForWidth());
        ButtonReset->setSizePolicy(sizePolicy);

        horizontalLayout->addWidget(ButtonReset);

        line_3 = new QFrame(edit_deck);
        line_3->setObjectName(QString::fromUtf8("line_3"));
        line_3->setFrameShape(QFrame::VLine);
        line_3->setFrameShadow(QFrame::Sunken);

        horizontalLayout->addWidget(line_3);

        ButtonRemoveDeck = new QPushButton(edit_deck);
        ButtonRemoveDeck->setObjectName(QString::fromUtf8("ButtonRemoveDeck"));
        sizePolicy.setHeightForWidth(ButtonRemoveDeck->sizePolicy().hasHeightForWidth());
        ButtonRemoveDeck->setSizePolicy(sizePolicy);

        horizontalLayout->addWidget(ButtonRemoveDeck);


        gridLayout->addLayout(horizontalLayout, 3, 0, 1, 1);

        line_2 = new QFrame(edit_deck);
        line_2->setObjectName(QString::fromUtf8("line_2"));
        line_2->setFrameShape(QFrame::HLine);
        line_2->setFrameShadow(QFrame::Sunken);

        gridLayout->addWidget(line_2, 2, 0, 1, 1);

        textEditDeckName = new QTextEdit(edit_deck);
        textEditDeckName->setObjectName(QString::fromUtf8("textEditDeckName"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Minimum);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(textEditDeckName->sizePolicy().hasHeightForWidth());
        textEditDeckName->setSizePolicy(sizePolicy1);
        textEditDeckName->setMinimumSize(QSize(0, 40));
        textEditDeckName->setMaximumSize(QSize(16777215, 50));
        QFont font;
        font.setPointSize(13);
        textEditDeckName->setFont(font);
        textEditDeckName->setLineWidth(1);
        textEditDeckName->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        textEditDeckName->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        textEditDeckName->setLineWrapColumnOrWidth(0);

        gridLayout->addWidget(textEditDeckName, 1, 0, 1, 1);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalLayout_2->setSizeConstraint(QLayout::SetMinimumSize);
        ButtonCancelEdit = new QPushButton(edit_deck);
        ButtonCancelEdit->setObjectName(QString::fromUtf8("ButtonCancelEdit"));
        QSizePolicy sizePolicy2(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(ButtonCancelEdit->sizePolicy().hasHeightForWidth());
        ButtonCancelEdit->setSizePolicy(sizePolicy2);

        horizontalLayout_2->addWidget(ButtonCancelEdit);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);

        line = new QFrame(edit_deck);
        line->setObjectName(QString::fromUtf8("line"));
        line->setFrameShape(QFrame::VLine);
        line->setFrameShadow(QFrame::Sunken);

        horizontalLayout_2->addWidget(line);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);

        ButtonSaveExit = new QPushButton(edit_deck);
        ButtonSaveExit->setObjectName(QString::fromUtf8("ButtonSaveExit"));
        QSizePolicy sizePolicy3(QSizePolicy::MinimumExpanding, QSizePolicy::Fixed);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(ButtonSaveExit->sizePolicy().hasHeightForWidth());
        ButtonSaveExit->setSizePolicy(sizePolicy3);

        horizontalLayout_2->addWidget(ButtonSaveExit);


        gridLayout->addLayout(horizontalLayout_2, 0, 0, 1, 1);


        retranslateUi(edit_deck);

        QMetaObject::connectSlotsByName(edit_deck);
    } // setupUi

    void retranslateUi(QWidget *edit_deck)
    {
        edit_deck->setWindowTitle(QCoreApplication::translate("edit_deck", "Form", nullptr));
        ButtonReset->setText(QCoreApplication::translate("edit_deck", "Reset deck", nullptr));
        ButtonRemoveDeck->setText(QCoreApplication::translate("edit_deck", "Remove deck", nullptr));
        ButtonCancelEdit->setText(QCoreApplication::translate("edit_deck", "Cancel", nullptr));
        ButtonSaveExit->setText(QCoreApplication::translate("edit_deck", "Save and Exit", nullptr));
    } // retranslateUi

};

namespace Ui {
    class edit_deck: public Ui_edit_deck {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EDIT_DECK_H
