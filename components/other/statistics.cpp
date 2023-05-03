#include "statistics.h"
#include "ui_statistics.h"

statistics::statistics(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::statistics)
{
    ui->setupUi(this);

    ui->titleLabel->setAlignment(Qt::AlignCenter);
    ui->sessionLabel->setAlignment(Qt::AlignCenter);

    ui->cardUsedChart->chart()->setBackgroundVisible(false);
    ui->cardUsedChart->chart()->setTitle("How many times cards were shown");
    ui->cardUsedChart->setRenderHint(QPainter::Antialiasing);
    ui->cardUsedChart->rubberBand().setFlag(QChartView::RectangleRubberBand);
    ui->cardUsedChart->chart()->legend()->hide();
    if(pc) {
        ui->cardUsedChart->chart()->setAnimationOptions(QChart::AllAnimations);
        QBrush whiteBrush(Qt::white);
        ui->cardUsedChart->chart()->setTitleBrush(whiteBrush);
        ui->cardUsedChart->chart()->legend()->setLabelColor(QColor::fromRgb(0,0,0));
    }
}

statistics::~statistics()
{
    delete ui;
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


    QPieSeries *series = new QPieSeries();

    QMapIterator<uint, uint> i(countMap);
    QBrush whiteBrush(Qt::white);
    while (i.hasNext()) {
        i.next();
        QPieSlice *slice = series->append(QString::number(i.key()), i.value());
        slice->setLabelBrush(whiteBrush);
        slice->setLabel(QString::number(i.key()) + " : " + QString::number(i.value()));
    }
    series->setLabelsVisible(true);

    ui->cardUsedChart->chart()->addSeries(series);

    if(pc) {
        this->resize(this->width() * 1.4, this->height() * 2.2);
    }
}

QString statistics::getStatsForSession(sessionStr* session, bool lastUsed) {
    QString returnStr;

    QString mode;
    // No better no problematic way
    if(session->core.mode == CompletlyRandomised) {
        mode = "Completly Randomised";
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
