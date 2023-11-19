#include "subSession.h"
#include "ui_subSession.h"

#include "mainMenu/sessions/sessionStruct.h"
#include "components/other/askText.h"

#include <QSettings>

subSession::subSession(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::subSession)
{
    ui->setupUi(this);
    this->setAttribute(Qt::WA_DeleteOnClose);
}

subSession::~subSession()
{
    delete ui;
}

void subSession::start(sessionStr sess) {
    // Bubble sort, I'm lazy
    newSession = sess;
    cardsSorted = newSession.cardList;
    countCards = cardsSorted.count();

    if(countCards == 0) {
        QTimer::singleShot(200, this, [this]() {
            QApplication::processEvents();
            qInfo() << "This session is propably not initialized";
            this->close();
        });
        return void();
    }
    bool swapped = true;
    while(swapped == true) {
        swapped = false;
        for(int i = 0; i < cardsSorted.count() - 1; i++) {
            if(cardsSorted[i].count > cardsSorted[i + 1].count) {
                cardsSorted.swapItemsAt(i, i + 1);
                swapped = true;
            }
        }
    }
    qDebug() << "cardsSorted:" << cardsSorted;
    calculatePercantage();
}

void subSession::on_selectingScrollBar_valueChanged(int value)
{
    calculatePercantage();
}

void subSession::calculatePercantage() {
    int value = ui->selectingScrollBar->value();
    howManyCards = countCards * (float(value) / 100);
    ui->infoLabel->setText("New session will have " + QString::number(howManyCards) + " cards");
}

void subSession::on_cancelButton_clicked()
{
    this->close();
}

void subSession::on_okButton_clicked()
{
    newSession.cardList = cardsSorted.mid(0, howManyCards);
    for(int i = 0; i < newSession.cardList.count(); i++) {
        card* oneCard = &newSession.cardList[i];
        oneCard->count = 0;
        oneCard->easyCount = 0;
        oneCard->goodCount = 0;
        oneCard->hardCount = 0;
        oneCard->againCount = 0;
    }
    newSession.time.created = QDateTime::currentDateTime();
    newSession.time.lastUsed = QDateTime::currentDateTime();
    newSession.time.played = 0;
    newSession.time.playedCount = 0;
    askText* textDialog = new askText();
    QString name;
    textDialog->textToSet = &name;
    textDialog->setTittle("Set the name for the new session");
    textDialog->exec();
    newSession.core.name = name;

    QSettings settings(directories::sessionSaves.filePath(name), QSettings::IniFormat);
    settings.setParent(this);
    QVariant variant = QVariant::fromValue(newSession);
    settings.setValue("session", variant);
    settings.sync();
    settings.deleteLater();

    this->close();
}

