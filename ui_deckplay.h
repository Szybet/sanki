/********************************************************************************
** Form generated from reading UI file 'deckplay.ui'
**
** Created by: Qt User Interface Compiler version 5.15.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DECKPLAY_H
#define UI_DECKPLAY_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_DeckPlay
{
public:
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    QGridLayout *gridCard;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    QGridLayout *gridLayout;
    QTextEdit *textFrontCard;
    QTextEdit *textBackCard;
    QFrame *line;
    QFrame *line_2;
    QGridLayout *gridManageCard;

    void setupUi(QMainWindow *DeckPlay)
    {
        if (DeckPlay->objectName().isEmpty())
            DeckPlay->setObjectName(QString::fromUtf8("DeckPlay"));
        DeckPlay->resize(800, 600);
        centralwidget = new QWidget(DeckPlay);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        gridCard = new QGridLayout();
        gridCard->setObjectName(QString::fromUtf8("gridCard"));
        scrollArea = new QScrollArea(centralwidget);
        scrollArea->setObjectName(QString::fromUtf8("scrollArea"));
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QString::fromUtf8("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 778, 561));
        gridLayout = new QGridLayout(scrollAreaWidgetContents);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        textFrontCard = new QTextEdit(scrollAreaWidgetContents);
        textFrontCard->setObjectName(QString::fromUtf8("textFrontCard"));
        textFrontCard->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        textFrontCard->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        textFrontCard->setTextInteractionFlags(Qt::NoTextInteraction);

        gridLayout->addWidget(textFrontCard, 0, 0, 1, 1);

        textBackCard = new QTextEdit(scrollAreaWidgetContents);
        textBackCard->setObjectName(QString::fromUtf8("textBackCard"));
        textBackCard->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        textBackCard->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        textBackCard->setTextInteractionFlags(Qt::NoTextInteraction);

        gridLayout->addWidget(textBackCard, 2, 0, 1, 1);

        line = new QFrame(scrollAreaWidgetContents);
        line->setObjectName(QString::fromUtf8("line"));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

        gridLayout->addWidget(line, 1, 0, 1, 1);

        scrollArea->setWidget(scrollAreaWidgetContents);

        gridCard->addWidget(scrollArea, 0, 0, 1, 1);


        verticalLayout->addLayout(gridCard);

        line_2 = new QFrame(centralwidget);
        line_2->setObjectName(QString::fromUtf8("line_2"));
        line_2->setFrameShape(QFrame::HLine);
        line_2->setFrameShadow(QFrame::Sunken);

        verticalLayout->addWidget(line_2);

        gridManageCard = new QGridLayout();
        gridManageCard->setObjectName(QString::fromUtf8("gridManageCard"));

        verticalLayout->addLayout(gridManageCard);

        DeckPlay->setCentralWidget(centralwidget);

        retranslateUi(DeckPlay);

        QMetaObject::connectSlotsByName(DeckPlay);
    } // setupUi

    void retranslateUi(QMainWindow *DeckPlay)
    {
        DeckPlay->setWindowTitle(QCoreApplication::translate("DeckPlay", "MainWindow", nullptr));
    } // retranslateUi

};

namespace Ui {
    class DeckPlay: public Ui_DeckPlay {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DECKPLAY_H
