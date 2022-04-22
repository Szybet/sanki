/********************************************************************************
** Form generated from reading UI file 'deck.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DECK_H
#define UI_DECK_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainQwidget
{
public:
    QVBoxLayout *verticalLayout_2;
    QFrame *frame;
    QGridLayout *gridLayout;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLineEdit *deck;
    QFrame *line;
    QLabel *LabelStats;
    QSpacerItem *verticalSpacer;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer_3;
    QPushButton *ButtonDeckPlay;
    QSpacerItem *horizontalSpacer_5;
    QPushButton *ButtonEditDeck;
    QSpacerItem *horizontalSpacer_4;

    void setupUi(QWidget *MainQwidget)
    {
        if (MainQwidget->objectName().isEmpty())
            MainQwidget->setObjectName(QString::fromUtf8("MainQwidget"));
        MainQwidget->setEnabled(true);
        MainQwidget->resize(332, 305);
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(MainQwidget->sizePolicy().hasHeightForWidth());
        MainQwidget->setSizePolicy(sizePolicy);
        verticalLayout_2 = new QVBoxLayout(MainQwidget);
        verticalLayout_2->setSpacing(0);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_2->setSizeConstraint(QLayout::SetMaximumSize);
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        frame = new QFrame(MainQwidget);
        frame->setObjectName(QString::fromUtf8("frame"));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        gridLayout = new QGridLayout(frame);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setSizeConstraint(QLayout::SetMinimumSize);
        deck = new QLineEdit(frame);
        deck->setObjectName(QString::fromUtf8("deck"));
        sizePolicy.setHeightForWidth(deck->sizePolicy().hasHeightForWidth());
        deck->setSizePolicy(sizePolicy);
        deck->setMouseTracking(false);
        deck->setTabletTracking(true);
        deck->setAlignment(Qt::AlignCenter);
        deck->setReadOnly(true);
        deck->setCursorMoveStyle(Qt::VisualMoveStyle);

        horizontalLayout->addWidget(deck);


        verticalLayout->addLayout(horizontalLayout);

        line = new QFrame(frame);
        line->setObjectName(QString::fromUtf8("line"));
        QSizePolicy sizePolicy1(QSizePolicy::Minimum, QSizePolicy::Maximum);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(line->sizePolicy().hasHeightForWidth());
        line->setSizePolicy(sizePolicy1);
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

        verticalLayout->addWidget(line);

        LabelStats = new QLabel(frame);
        LabelStats->setObjectName(QString::fromUtf8("LabelStats"));
        LabelStats->setLayoutDirection(Qt::LeftToRight);
        LabelStats->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(LabelStats);

        verticalSpacer = new QSpacerItem(20, 20, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalSpacer_3 = new QSpacerItem(20, 20, QSizePolicy::MinimumExpanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_3);

        ButtonDeckPlay = new QPushButton(frame);
        ButtonDeckPlay->setObjectName(QString::fromUtf8("ButtonDeckPlay"));

        horizontalLayout_2->addWidget(ButtonDeckPlay);

        horizontalSpacer_5 = new QSpacerItem(20, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_5);

        ButtonEditDeck = new QPushButton(frame);
        ButtonEditDeck->setObjectName(QString::fromUtf8("ButtonEditDeck"));

        horizontalLayout_2->addWidget(ButtonEditDeck);

        horizontalSpacer_4 = new QSpacerItem(20, 20, QSizePolicy::MinimumExpanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_4);


        verticalLayout->addLayout(horizontalLayout_2);


        gridLayout->addLayout(verticalLayout, 2, 0, 1, 1);


        verticalLayout_2->addWidget(frame);


        retranslateUi(MainQwidget);

        QMetaObject::connectSlotsByName(MainQwidget);
    } // setupUi

    void retranslateUi(QWidget *MainQwidget)
    {
        MainQwidget->setWindowTitle(QCoreApplication::translate("MainQwidget", "Form", nullptr));
        deck->setPlaceholderText(QString());
        LabelStats->setText(QCoreApplication::translate("MainQwidget", "Deck Stats", nullptr));
        ButtonDeckPlay->setText(QCoreApplication::translate("MainQwidget", "Play", nullptr));
        ButtonEditDeck->setText(QCoreApplication::translate("MainQwidget", "Edit", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainQwidget: public Ui_MainQwidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DECK_H
