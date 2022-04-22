/********************************************************************************
** Form generated from reading UI file 'status_bar.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_STATUS_BAR_H
#define UI_STATUS_BAR_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_status_bar
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *ButtonExit;
    QSpacerItem *horizontalSpacer_3;
    QFrame *line;
    QSpacerItem *horizontalSpacer_4;
    QPushButton *ButtonOption;
    QSpacerItem *horizontalSpacer;
    QLabel *LabelStatus;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *ButtonSettings;
    QSpacerItem *horizontalSpacer_5;
    QFrame *line_3;
    QSpacerItem *horizontalSpacer_6;
    QLabel *labelTime;
    QFrame *line_2;

    void setupUi(QWidget *status_bar)
    {
        if (status_bar->objectName().isEmpty())
            status_bar->setObjectName(QString::fromUtf8("status_bar"));
        status_bar->resize(706, 70);
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(status_bar->sizePolicy().hasHeightForWidth());
        status_bar->setSizePolicy(sizePolicy);
        status_bar->setMinimumSize(QSize(0, 60));
        status_bar->setMaximumSize(QSize(16777215, 70));
        verticalLayout = new QVBoxLayout(status_bar);
        verticalLayout->setSpacing(0);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 5, 0, 5);
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(0);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(-1, -1, -1, 5);
        ButtonExit = new QPushButton(status_bar);
        ButtonExit->setObjectName(QString::fromUtf8("ButtonExit"));
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(ButtonExit->sizePolicy().hasHeightForWidth());
        ButtonExit->setSizePolicy(sizePolicy1);
        ButtonExit->setMinimumSize(QSize(0, 0));
        ButtonExit->setMaximumSize(QSize(16777215, 16777215));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/icons/close.png"), QSize(), QIcon::Normal, QIcon::Off);
        ButtonExit->setIcon(icon);
        ButtonExit->setIconSize(QSize(45, 45));
        ButtonExit->setFlat(false);

        horizontalLayout_2->addWidget(ButtonExit);

        horizontalSpacer_3 = new QSpacerItem(20, 20, QSizePolicy::Minimum, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_3);

        line = new QFrame(status_bar);
        line->setObjectName(QString::fromUtf8("line"));
        line->setFrameShadow(QFrame::Plain);
        line->setLineWidth(5);
        line->setMidLineWidth(5);
        line->setFrameShape(QFrame::VLine);

        horizontalLayout_2->addWidget(line);

        horizontalSpacer_4 = new QSpacerItem(20, 20, QSizePolicy::Minimum, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_4);

        ButtonOption = new QPushButton(status_bar);
        ButtonOption->setObjectName(QString::fromUtf8("ButtonOption"));
        QSizePolicy sizePolicy2(QSizePolicy::Minimum, QSizePolicy::Expanding);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(ButtonOption->sizePolicy().hasHeightForWidth());
        ButtonOption->setSizePolicy(sizePolicy2);
        ButtonOption->setMinimumSize(QSize(0, 0));
        ButtonOption->setMaximumSize(QSize(16777215, 40));
        QFont font;
        font.setPointSize(9);
        ButtonOption->setFont(font);
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/icons/folder.png"), QSize(), QIcon::Normal, QIcon::Off);
        ButtonOption->setIcon(icon1);
        ButtonOption->setIconSize(QSize(40, 40));

        horizontalLayout_2->addWidget(ButtonOption);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);

        LabelStatus = new QLabel(status_bar);
        LabelStatus->setObjectName(QString::fromUtf8("LabelStatus"));
        LabelStatus->setFont(font);

        horizontalLayout_2->addWidget(LabelStatus);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);

        ButtonSettings = new QPushButton(status_bar);
        ButtonSettings->setObjectName(QString::fromUtf8("ButtonSettings"));
        sizePolicy1.setHeightForWidth(ButtonSettings->sizePolicy().hasHeightForWidth());
        ButtonSettings->setSizePolicy(sizePolicy1);
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/icons/settings.png"), QSize(), QIcon::Normal, QIcon::Off);
        ButtonSettings->setIcon(icon2);
        ButtonSettings->setIconSize(QSize(40, 40));

        horizontalLayout_2->addWidget(ButtonSettings);

        horizontalSpacer_5 = new QSpacerItem(10, 20, QSizePolicy::Minimum, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_5);

        line_3 = new QFrame(status_bar);
        line_3->setObjectName(QString::fromUtf8("line_3"));
        line_3->setFrameShadow(QFrame::Plain);
        line_3->setLineWidth(4);
        line_3->setFrameShape(QFrame::VLine);

        horizontalLayout_2->addWidget(line_3);

        horizontalSpacer_6 = new QSpacerItem(10, 20, QSizePolicy::Minimum, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_6);

        labelTime = new QLabel(status_bar);
        labelTime->setObjectName(QString::fromUtf8("labelTime"));
        QSizePolicy sizePolicy3(QSizePolicy::Preferred, QSizePolicy::Expanding);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(labelTime->sizePolicy().hasHeightForWidth());
        labelTime->setSizePolicy(sizePolicy3);
        labelTime->setFont(font);

        horizontalLayout_2->addWidget(labelTime);


        verticalLayout->addLayout(horizontalLayout_2);

        line_2 = new QFrame(status_bar);
        line_2->setObjectName(QString::fromUtf8("line_2"));
        QSizePolicy sizePolicy4(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy4.setHorizontalStretch(0);
        sizePolicy4.setVerticalStretch(0);
        sizePolicy4.setHeightForWidth(line_2->sizePolicy().hasHeightForWidth());
        line_2->setSizePolicy(sizePolicy4);
        line_2->setMinimumSize(QSize(0, 0));
        line_2->setLayoutDirection(Qt::LeftToRight);
        line_2->setFrameShadow(QFrame::Plain);
        line_2->setLineWidth(4);
        line_2->setMidLineWidth(0);
        line_2->setFrameShape(QFrame::HLine);

        verticalLayout->addWidget(line_2);


        retranslateUi(status_bar);

        QMetaObject::connectSlotsByName(status_bar);
    } // setupUi

    void retranslateUi(QWidget *status_bar)
    {
        status_bar->setWindowTitle(QCoreApplication::translate("status_bar", "Form", nullptr));
        ButtonExit->setText(QString());
        ButtonOption->setText(QCoreApplication::translate("status_bar", "Option", nullptr));
        LabelStatus->setText(QCoreApplication::translate("status_bar", "Sanki3", nullptr));
        ButtonSettings->setText(QString());
        labelTime->setText(QCoreApplication::translate("status_bar", "00:00", nullptr));
    } // retranslateUi

};

namespace Ui {
    class status_bar: public Ui_status_bar {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_STATUS_BAR_H
