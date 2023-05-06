#include "statistics.h"
#include "ui_statistics.h"
#include "cardView/modes/boxes/boxes.h"

statistics::statistics(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::statistics)
{
    ui->setupUi(this);
    this->setAttribute(Qt::WA_DeleteOnClose);

    ui->titleLabel->setAlignment(Qt::AlignCenter);
    ui->sessionLabel->setAlignment(Qt::AlignCenter);

    setUpChart(ui->cardUsedChart, "How many times cards were shown");
}

statistics::~statistics()
{
    delete ui;
}

void statistics::setUpChart(QtCharts::QChartView* chart, QString title) {
    chart->chart()->setBackgroundVisible(false);
    chart->chart()->setTitle(title);
    chart->setRenderHint(QPainter::Antialiasing);
    chart->rubberBand().setFlag(QChartView::RectangleRubberBand);
    chart->chart()->setAnimationOptions(QChart::NoAnimation);
    if(pc) {
        QBrush whiteBrush(Qt::white);
        chart->chart()->setTitleBrush(whiteBrush);
        chart->chart()->legend()->setLabelBrush(whiteBrush);
    }
}

void statistics::start(sessionStr session) {
    ui->sessionLabel->setText(session.core.name);

    qDebug() << "Statistics for session:" << session;

    ui->textBrowser->setHtml(getStatsForSession(&session, false));

    // https://stackoverflow.com/questions/48362864/how-to-insert-qchartview-in-form-with-qt-designer

    QMap<uint, uint> countMap;
    foreach(card acard, session.cardList) {
        if(countMap.contains(acard.count)) {
            countMap[acard.count] += 1;
        } else {
            countMap[acard.count] = 1;
        }
    }
    qDebug() << "countMap:" << countMap;


    QPieSeries *series = new QPieSeries(this);

    QMapIterator<uint, uint> i(countMap);
    QBrush whiteBrush(Qt::white);
    while (i.hasNext()) {
        i.next();
        QPieSlice *slice = series->append(QString::number(i.key()), i.value());
        slice->setLabelBrush(whiteBrush);
        slice->setLabel(QString::number(i.key()));
    }
    series->setLabelsVisible(false);

    ui->cardUsedChart->chart()->addSeries(series);

    if(session.core.mode != Boxes) {
        ui->cardBoxesChart->hide();
    } else {
        setUpChart(ui->cardBoxesChart, "How much cards in which boxes");
        QSettings settings(directories::sessionSaves.filePath(session.core.name), QSettings::IniFormat);
        settings.sync();
        box abox = settings.value("boxMode/box").value<box>();
        qDebug() << "Count boxes:" << abox.howMuchBoxes;

        QBarSeries* seriesBar = new QBarSeries(this);
        for(int i = 0; i < abox.boxes.count() - 1; i++) {
            if(abox.boxes[i].count() != 0) {
                QBarSet *set = new QBarSet(QString::number(i));
                *set << abox.boxes[i].count();
                seriesBar->append(set);
                //set->setLabel(QString::number(abox.boxes[i].count()));
            }
        }
        seriesBar->setLabelsVisible(true);
        seriesBar->setLabelsPosition(QAbstractBarSeries::LabelsOutsideEnd);
        ui->cardBoxesChart->chart()->addSeries(seriesBar);
    }

    if(pc) {
        this->resize(this->width() * 1.4, this->height() * 1.4);
        this->setMaximumSize(QSize(99999, 99999));
        this->setMinimumSize(QSize(0, 0));
    }
}

QString statistics::getStatsForSession(sessionStr* session, bool lastUsed) {
    QString returnStr;

    QString mode;
    // No better no problematic way
    if(session->core.mode == CompletlyRandomised) {
        mode = "Completly Randomised";
    } else if(session->core.mode == Boxes) {
        mode = "Boxes";
    }

    returnStr = returnStr + "<b>Mode:</b> " + mode + "<br>";
    returnStr = returnStr + "<b>Decks:</b> " + session->core.deckPathList.join(",") + "<br>";
    returnStr = returnStr + "<b>Created:</b> " + session->time.created.toString("dd.MM.yyyy - hh:mm") + "<br>";
    if(lastUsed) {
        returnStr = returnStr + "<b>Last used:</b> " + session->time.lastUsed.toString("dd.MM.yyyy - hh:mm") + "<br>";
    }

    QString hours = QString::number(session->time.played / (1000 * 60 * 60)); // Calculate hours
    QString minutes = QString::number(session->time.played / (1000 * 60)); // Calculate minutes

    if(hours.count() == 1) {
        hours = "0" + hours;
    }
    if(minutes.count() == 1) {
        minutes = "0" + minutes;
    }

    qDebug() << "Played time:" << session->time.played << "hours:" << hours << "minutes:" << minutes;

    returnStr = returnStr + "<b>Time spend:</b> " + hours + ":" + minutes + "<br>";

    returnStr = returnStr + "<b>How many times used:</b> " + QString::number(session->time.playedCount) + "<br>";
    returnStr = returnStr + "<b>Total cards:</b> " + QString::number(session->cardList.count()) + "<br>";

    return returnStr;
}
