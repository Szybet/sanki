#include "settings.h"
#include "ui_settings.h"
#include "global.h"
#include "zip.h"
#include "other/keyboard.h"

#include <QHostAddress>
#include <QNetworkInterface>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QProgressDialog>
#include <QTimer>
#include <QSettings>
#include <QFontDialog>

#ifdef EREADER
#include "einkenums.h"
#include "koboplatformfunctions.h"
#include "generalfunctions.h"
#include "audiodialog.h"
#endif

Settings::Settings(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Settings)
{
    ui->setupUi(this);
    this->setAttribute(Qt::WA_DeleteOnClose);

    // This is because the QDialog has borders
    // if(ereader) this->setStyleSheet("QDialog {border: 0px solid black; border-radius: 0px; background: white;}");

    if(ereader) {
        ui->labelPageName->setStyleSheet("font-size: 9pt;");
        ui->ButtonLeft->setStyleSheet("font-size: 9pt; border: 0px solid black;");
        ui->ButtonRight->setStyleSheet("font-size: 9pt; border: 0px solid black;");
        ui->ButtonOk->setStyleSheet("font-size: 8pt; border: 0px solid black;");

        timer = new QTimer(this);
        connect(timer, &QTimer::timeout, this, &Settings::manageKeyboards);
        timer->start(800);
        /*
        ui->textIP->setStyleSheet("border: 2px solid black;");
        ui->textIP->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        ui->textIP->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        ui->textIP->setFixedHeight(ui->checkBox->height() + 15);
        */

        ui->buttonSyncInfo->setStyleSheet("border: 3px solid black");
        ui->buttonSync->setStyleSheet("border: 3px solid black");
    }

    qDebug() << "Loading global settings";
    settingsGlobal = new QSettings(directories::globalSettings.fileName(), QSettings::IniFormat);
    qDebug() << "Keys:" << settingsGlobal->allKeys();
    settingsGlobal->setParent(this);

    if(ereader) {
       int waveform = settingsGlobal->value("deckPlayWaveForm").toInt();
       ui->comboBoxEinkMode->setCurrentText(waveFormNumbToString(waveform));
    }

    // Set the default page
    ui->stackedWidget->setCurrentIndex(1);
    requestMenuPage();

    if(ereader) {
       this->setFixedWidth(ereaderVars::screenX);
    }

    if(!ereaderVars::nickelApp) {
        ui->buttonDebuggingData->setDisabled(true);
    }
    if(!ereaderVars::inkboxUserApp) {
        ui->audioButton->setDisabled(true);
    }

#ifdef EREADER
    qDebug() << "Setting waveform mode";
    KoboPlatformFunctions::setFullScreenRefreshMode(WaveForm_GC16);
#endif
}

Settings::~Settings()
{
    delete ui;
}

void Settings::on_ButtonLeft_clicked()
{
    int index = ui->stackedWidget->currentIndex();
    index = index - 1;
    managePage(index, Left);
}


void Settings::on_ButtonRight_clicked()
{
    int index = ui->stackedWidget->currentIndex();
    index = index + 1;
    managePage(index, Right);
}


void Settings::requestEreaderPage()
{
    ui->labelPageName->setText("Device");

    checkBatteryLevel();
    QString bat_level = "Battery level: ";
    bat_level.append(QString::number(checkBatteryLevel()));
    bat_level.append("%");
    ui->labelBattery->setText(bat_level);

    int brightness = getWhiteBrightnessAlias();
    ui->ScrollBarBrightness->setSliderPosition(brightness);

    QString brightness_string = "Brightness: ";
    brightness_string.append(QString::number(brightness));
    brightness_string.append("%");
    ui->labelBrightness->setText(brightness_string);
}

void Settings::on_ScrollBarBrightness_valueChanged(int value)
{
    setWhiteBrightnessAlias(value);

    QString brightness_string = "Brightness: ";
    QString number = QString::number(value);


    brightness_string.append(QString::number(value));
    brightness_string.append("%");

    ui->labelBrightness->setText(brightness_string);
}


void Settings::on_ButtonOk_clicked()
{
    this->close();
}

void Settings::managePage(int newIndex, Direction fromWhere) {
    if(newIndex < 0) {
        newIndex = ui->stackedWidget->count() - 1;
    }
    if(newIndex > ui->stackedWidget->count() - 1) {
        newIndex = 0;
    }

    if(ereader != true && newIndex == 0) {
        if(fromWhere == Right) {
            managePage(newIndex + 1, fromWhere);
            return void();
        } else {
            managePage(newIndex - 1, fromWhere);
            return void();
        }
    }

    ui->stackedWidget->setCurrentIndex(newIndex);
    if(newIndex == 0) {
        requestEreaderPage();
    } else if(newIndex == 1) {
        requestMenuPage();
    } else if(newIndex == 2) {
        requestSyncPage();
    }
}

void Settings::requestMenuPage() {
    ui->labelPageName->setText("Menu");

    settingsGlobal->sync();

    QVariant variant = settingsGlobal->value("playFont");
    qDebug() << "variant:" << variant;
    qDebug() << variant.isValid() << variant.isNull();
    QFont font = variant.value<QFont>();
    ui->labelFontName->setText(font.family() + ", " + QString::number(font.pointSize()));
    currentFont = font;
}

void Settings::requestSyncPage() {
    ui->labelPageName->setText("Sync");

    QStringList addresses;

    const QHostAddress &localhost = QHostAddress(QHostAddress::LocalHost);
    foreach(const QHostAddress &address, QNetworkInterface::allAddresses()) {
        if (address.protocol() == QAbstractSocket::IPv4Protocol && address != localhost) {
            addresses << address.toString();
        }
    }

    ui->labelIp->setText(addresses.join(", "));
}

void Settings::on_buttonSyncInfo_clicked()
{
    qInfo() << "- Run anki-sync on the machine that has anki, and ankiconnect on it<br>- The default port is 8766<br>- After an error, restart the sync server<br>- As of now, your sessions will not be updated from new cards in overwrited decks<br>- For more informations, check the project github page README file";
}

void Settings::on_buttonSync_clicked()
{
    if(ui->labelIp->text().isEmpty() == true) {
        qWarning() << "Current device IP address is not available, so propably there is no internet connection?";
        return void();
    }
    QString address = ui->textIP->text();

    QProgressDialog progress("Downloading index file", "", 0, 100, this);
    progress.setWindowModality(Qt::WindowModal);
    progress.setCancelButton(nullptr); // Um?
    progress.show();

    if(ereader) {
        progress.setFixedWidth(ereaderVars::screenX);
        progress.move(0, progress.y());
    }

    QNetworkAccessManager manager(this);
    QNetworkRequest request(QUrl("http://" + address +  "/index.txt"));
    QNetworkReply *reply = manager.get(request);

    QEventLoop loop(this);
    QObject::connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);

    loop.exec();

    qDebug() << "The whole url is:" << request.url() << "address is:" << address;
    if (reply->error() == QNetworkReply::NoError)
    {
        QStringList data = QString(reply->readAll()).split("\n");
        qDebug() << "Index file data:" << data;
        progress.setMaximum(data.count() + 1);
        progress.setValue(1);
        foreach(QString file, data) {
            QString name = file;
            name = name.remove(".apkg");
            QString fullPath = directories::deckStorage.filePath(name);

            if(QDir{fullPath}.exists() == true) {
                if(overwriteDeck == true) {
                    qDebug() << "Removing deck because overwrite:" << name;
                    bool result = QDir{fullPath}.removeRecursively();
                    if(result == false) {
                        qWarning() << "Failed to remove deck to overwrite it:" << name;
                        return void();
                    }
                } else {
                    qDebug() << "Deck exists and skipping it:" << name;
                    progress.setValue(progress.value() + 1);
                    continue;
                }
            }
            progress.setLabelText("Downloading file: " + file);
            QUrl theUrl = QUrl("http://" + address.toUtf8() +  "/" + file.replace(" ", "%20")); // spaces problem
            qDebug() << "theUrl" << theUrl;
            QNetworkRequest request(theUrl);
            QNetworkReply *reply = manager.get(request);
            QEventLoop loop(this);
            QObject::connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
            qDebug() << "Downloading it...";
            loop.exec();
            qDebug() << "Downloaded finished?";

            if(reply->error() != QNetworkReply::NoError) {
                qWarning() << "Failed to download file:" << file << "error:" << reply->error();
                continue;
            }

            QByteArray zipData = reply->readAll();
            qDebug() << "Bytes received";

            const char* zipStream = zipData.constData();
            size_t zipSize = zipData.size();

            if(directories::deckStorage.mkpath(name) == false) {
                progress.close();
                qWarning() << "Failed to create directory" << fullPath;
                return void();
            }

            bool result = zip_stream_extract(zipStream, zipSize, fullPath.toUtf8().constData(), nullptr, nullptr);
            if(result == true) {
                progress.close();
                qWarning() << "Failed to extract deck" << name;
                return void();
            }

            if(QDir(fullPath).exists() == false) {
                qWarning() << "Failed create deck?:" << name;
                return void();
            }

            // For deck stats
            QFile creationTime(QDir(fullPath).filePath(deckAddedFileName));
            creationTime.open(QIODevice::WriteOnly);
            creationTime.write(QDateTime::currentDateTime().toString("dd.MM.yyyy - hh:mm").toStdString().c_str());
            creationTime.close();

            progress.setValue(progress.value() + 1);
        }

    } else {
        progress.close();
        qWarning() << "Download failed:" << reply->errorString();
        return void();
    }
    progress.close();
    qInfo() << "Succesfully downloaded all decks";
}

void Settings::on_checkBox_stateChanged(int arg1)
{
    qDebug() << "Checkbox value:" << arg1;
    // It's 2 and 0 for a reason
    if(arg1 > 1) {
        overwriteDeck = true;
    } else {
        overwriteDeck = false;
    }
}

void Settings::manageKeyboards() {
    QLineEdit* textEditToCheck = ui->textIP;
    if(textEditToCheck->underMouse() == true && textEditToCheck->hasFocus() == true) {
        keyboard* ereaderKeyboard = new keyboard(this);
        ereaderKeyboard->start(textEditToCheck);
        int y = this->pos().y();
        this->move(this->pos().x(), 0);
        ereaderKeyboard->exec();
        textEditToCheck->clearFocus();
        this->move(this->pos().x(), y);
        return void();
    }
}

void Settings::on_ButtonFontChange_clicked()
{
    QFontDialog* dialog = new QFontDialog(this);

    if(ereader) {
        dialog->show();
        dialog->move(0, 0);
        dialog->setFixedSize(ereaderVars::screenX, ereaderVars::screenY);
    }
    dialog->setFont(currentFont);
    int result = dialog->exec();

    if(result == QDialog::Accepted) {
        currentFont = dialog->selectedFont();
        qDebug() << "New current font:" << currentFont;
        settingsGlobal->setValue("playFont", currentFont);
        requestMenuPage();
    }
}

void Settings::on_buttonEinkInfo_clicked()
{
    QString info = "Those are eink screen modes, the set how things are shown:<br>"
                   "- WaveForm_A2 - Default, fastest, the most ghosting, a lot can damage your screen! ( propably )<br>"
                   "- WaveForm_GC4 - Fast, refreshes too much of the screen, but never goes white - black - white. Propably safe<br>"
                   "- WaveForm_GC16 - The default used in all other dialogs - no or a bit ghosting, slow<br>"
                   "- WaveForm_AUTO - Fast, experimental, ugly :)";
    qInfo() << info;
}

void Settings::on_comboBoxEinkMode_currentTextChanged(const QString &arg1) {
    int newWaveForm = waveFormStringToInt(arg1);
    settingsGlobal->setValue("deckPlayWaveForm", newWaveForm);
    settingsGlobal->sync();
}

QString Settings::waveFormNumbToString(int numb) {
    switch (numb) {
        case 4: return "WaveForm_A2";
        case 2: return "WaveForm_GC16";
        case 3: return "WaveForm_GC4";
        case 257: return "WaveForm_AUTO";
    }
    return "error";
}

int Settings::waveFormStringToInt(QString name) {
    if (name == "WaveForm_A2")
        return 4;
    else if (name == "WaveForm_GC16")
        return 2;
    else if (name == "WaveForm_GC4")
        return 3;
    else if (name == "WaveForm_AUTO")
        return 257;
    else
        return -1;
}

void Settings::on_buttonDebuggingData_clicked()
{
    if(ereaderVars::nickelApp) {
#ifdef EREADER
        execShell("find /sys > /mnt/onboard/sanki_debug_export.txt");
        execShell("printf \"\n\n\nDevice code:\n\" >> /mnt/onboard/sanki_debug_export.txt");
        execShell("/bin/kobo_config.sh >> /mnt/onboard/sanki_debug_export.txt");
        execShell("printf \"\n\n\nDevice version:\n\" >> /mnt/onboard/sanki_debug_export.txt");
        execShell("cat /mnt/onboard/.kobo/version >> /mnt/onboard/sanki_debug_export.txt");
        qInfo() << "Finished exporting debug informations. The file is named: sanki_debug_export.txt";
#endif
    }
}

void Settings::on_audioButton_clicked()
{
#ifdef EREADER
    QDialog* newAudioDialog = new audioDialog(this);
    newAudioDialog->exec();
#endif
}

