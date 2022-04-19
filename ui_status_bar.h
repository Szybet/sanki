/********************************************************************************
** Form generated from reading UI file 'status_bar.ui'
**
** Created by: Qt User Interface Compiler version 5.15.1
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
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_status_bar
{
public:
    QHBoxLayout *horizontalLayout_2;
    QPushButton *ButtonExit;
    QFrame *line;
    QPushButton *ButtonOption;
    QSpacerItem *horizontalSpacer;
    QLabel *LabelStatus;
    QSpacerItem *horizontalSpacer_2;
    QLabel *LabelBattery;
    QFrame *line_3;
    QLabel *labelTime;

    void setupUi(QWidget *status_bar)
    {
        if (status_bar->objectName().isEmpty())
            status_bar->setObjectName(QString::fromUtf8("status_bar"));
        status_bar->resize(400, 40);
        status_bar->setMaximumSize(QSize(16777215, 45));
        horizontalLayout_2 = new QHBoxLayout(status_bar);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(2, 0, 2, 0);
        ButtonExit = new QPushButton(status_bar);
        ButtonExit->setObjectName(QString::fromUtf8("ButtonExit"));
        ButtonExit->setMinimumSize(QSize(40, 40));
        ButtonExit->setMaximumSize(QSize(40, 40));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/icons/close.png"), QSize(), QIcon::Normal, QIcon::Off);
        ButtonExit->setIcon(icon);
        ButtonExit->setIconSize(QSize(40, 40));

        horizontalLayout_2->addWidget(ButtonExit);

        line = new QFrame(status_bar);
        line->setObjectName(QString::fromUtf8("line"));
        line->setFrameShape(QFrame::VLine);
        line->setFrameShadow(QFrame::Sunken);

        horizontalLayout_2->addWidget(line);

        ButtonOption = new QPushButton(status_bar);
        ButtonOption->setObjectName(QString::fromUtf8("ButtonOption"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(ButtonOption->sizePolicy().hasHeightForWidth());
        ButtonOption->setSizePolicy(sizePolicy);
        ButtonOption->setMaximumSize(QSize(16777215, 40));

        horizontalLayout_2->addWidget(ButtonOption);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);

        LabelStatus = new QLabel(status_bar);
        LabelStatus->setObjectName(QString::fromUtf8("LabelStatus"));
        QFont font;
        font.setPointSize(12);
        LabelStatus->setFont(font);

        horizontalLayout_2->addWidget(LabelStatus);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);

        LabelBattery = new QLabel(status_bar);
        LabelBattery->setObjectName(QString::fromUtf8("LabelBattery"));
        LabelBattery->setFont(font);

        horizontalLayout_2->addWidget(LabelBattery);

        line_3 = new QFrame(status_bar);
        line_3->setObjectName(QString::fromUtf8("line_3"));
        line_3->setFrameShape(QFrame::VLine);
        line_3->setFrameShadow(QFrame::Sunken);

        horizontalLayout_2->addWidget(line_3);

        labelTime = new QLabel(status_bar);
        labelTime->setObjectName(QString::fromUtf8("labelTime"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(labelTime->sizePolicy().hasHeightForWidth());
        labelTime->setSizePolicy(sizePolicy1);
        labelTime->setFont(font);

        horizontalLayout_2->addWidget(labelTime);


        retranslateUi(status_bar);

        QMetaObject::connectSlotsByName(status_bar);
    } // setupUi

    void retranslateUi(QWidget *status_bar)
    {
        status_bar->setWindowTitle(QCoreApplication::translate("status_bar", "Form", nullptr));
        ButtonExit->setText(QString());
        ButtonOption->setText(QCoreApplication::translate("status_bar", "Option", nullptr));
        LabelStatus->setText(QCoreApplication::translate("status_bar", "Status", nullptr));
        LabelBattery->setText(QCoreApplication::translate("status_bar", "0%", nullptr));
        labelTime->setText(QCoreApplication::translate("status_bar", "00:00", nullptr));
    } // retranslateUi

};

namespace Ui {
    class status_bar: public Ui_status_bar {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_STATUS_BAR_H
