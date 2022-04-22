/********************************************************************************
** Form generated from reading UI file 'decks_scroll_bar.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DECKS_SCROLL_BAR_H
#define UI_DECKS_SCROLL_BAR_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_decks_scroll_bar
{
public:
    QGridLayout *gridLayout_2;
    QScrollArea *DeckScrollArea;
    QWidget *scrollAreaWidgetContents;
    QGridLayout *gridLayout;
    QGridLayout *DeckGrid;

    void setupUi(QWidget *decks_scroll_bar)
    {
        if (decks_scroll_bar->objectName().isEmpty())
            decks_scroll_bar->setObjectName(QString::fromUtf8("decks_scroll_bar"));
        decks_scroll_bar->resize(400, 300);
        gridLayout_2 = new QGridLayout(decks_scroll_bar);
        gridLayout_2->setSpacing(0);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        gridLayout_2->setContentsMargins(0, 0, 0, 0);
        DeckScrollArea = new QScrollArea(decks_scroll_bar);
        DeckScrollArea->setObjectName(QString::fromUtf8("DeckScrollArea"));
        DeckScrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        DeckScrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        DeckScrollArea->setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContents);
        DeckScrollArea->setWidgetResizable(true);
        DeckScrollArea->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignTop);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QString::fromUtf8("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 398, 298));
        gridLayout = new QGridLayout(scrollAreaWidgetContents);
        gridLayout->setSpacing(0);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        DeckGrid = new QGridLayout();
        DeckGrid->setSpacing(0);
        DeckGrid->setObjectName(QString::fromUtf8("DeckGrid"));
        DeckGrid->setSizeConstraint(QLayout::SetMinimumSize);

        gridLayout->addLayout(DeckGrid, 0, 0, 1, 1);

        DeckScrollArea->setWidget(scrollAreaWidgetContents);

        gridLayout_2->addWidget(DeckScrollArea, 0, 0, 1, 1);


        retranslateUi(decks_scroll_bar);

        QMetaObject::connectSlotsByName(decks_scroll_bar);
    } // setupUi

    void retranslateUi(QWidget *decks_scroll_bar)
    {
        decks_scroll_bar->setWindowTitle(QCoreApplication::translate("decks_scroll_bar", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class decks_scroll_bar: public Ui_decks_scroll_bar {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DECKS_SCROLL_BAR_H
