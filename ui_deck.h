/********************************************************************************
** Form generated from reading UI file 'deck.ui'
**
** Created by: Qt User Interface Compiler version 5.15.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DECK_H
#define UI_DECK_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainQwidget
{
public:
    QGridLayout *gridLayout_3;
    QFrame *frame;
    QGridLayout *gridLayout;
    QGridLayout *gridLayout_2;
    QLabel *CardNumberLabel;
    QFrame *line;
    QSpacerItem *verticalSpacer;
    QPushButton *DeckNamePlayButton;
    QPushButton *EditDeckbutton;

    void setupUi(QWidget *MainQwidget)
    {
        if (MainQwidget->objectName().isEmpty())
            MainQwidget->setObjectName(QString::fromUtf8("MainQwidget"));
        MainQwidget->resize(400, 175);
        gridLayout_3 = new QGridLayout(MainQwidget);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        frame = new QFrame(MainQwidget);
        frame->setObjectName(QString::fromUtf8("frame"));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        gridLayout = new QGridLayout(frame);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout_2 = new QGridLayout();
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        CardNumberLabel = new QLabel(frame);
        CardNumberLabel->setObjectName(QString::fromUtf8("CardNumberLabel"));
        CardNumberLabel->setLayoutDirection(Qt::LeftToRight);
        CardNumberLabel->setAlignment(Qt::AlignCenter);

        gridLayout_2->addWidget(CardNumberLabel, 2, 0, 1, 1);

        line = new QFrame(frame);
        line->setObjectName(QString::fromUtf8("line"));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

        gridLayout_2->addWidget(line, 1, 0, 1, 1);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_2->addItem(verticalSpacer, 5, 0, 1, 1);

        DeckNamePlayButton = new QPushButton(frame);
        DeckNamePlayButton->setObjectName(QString::fromUtf8("DeckNamePlayButton"));
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(DeckNamePlayButton->sizePolicy().hasHeightForWidth());
        DeckNamePlayButton->setSizePolicy(sizePolicy);

        gridLayout_2->addWidget(DeckNamePlayButton, 0, 0, 1, 1);

        EditDeckbutton = new QPushButton(frame);
        EditDeckbutton->setObjectName(QString::fromUtf8("EditDeckbutton"));

        gridLayout_2->addWidget(EditDeckbutton, 6, 0, 1, 1);


        gridLayout->addLayout(gridLayout_2, 0, 0, 1, 1);


        gridLayout_3->addWidget(frame, 0, 0, 1, 1);


        retranslateUi(MainQwidget);

        QMetaObject::connectSlotsByName(MainQwidget);
    } // setupUi

    void retranslateUi(QWidget *MainQwidget)
    {
        MainQwidget->setWindowTitle(QCoreApplication::translate("MainQwidget", "Form", nullptr));
        CardNumberLabel->setText(QCoreApplication::translate("MainQwidget", "Deck Stats", nullptr));
        DeckNamePlayButton->setText(QCoreApplication::translate("MainQwidget", "Deck Name", nullptr));
        EditDeckbutton->setText(QCoreApplication::translate("MainQwidget", "Edit", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainQwidget: public Ui_MainQwidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DECK_H
