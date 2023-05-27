#include "statistics.h"
#include "ui_statistics.h"
#include "cardView/modes/boxes/boxes.h"

#ifdef EREADER
#include "einkenums.h"
#include "koboplatformfunctions.h"
#endif
#include <QTextEdit>

statistics::statistics(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::statistics)
{
    ui->setupUi(this);
    this->setAttribute(Qt::WA_DeleteOnClose);

    ui->titleLabel->setAlignment(Qt::AlignCenter);
    ui->sessionLabel->setAlignment(Qt::AlignCenter);

    setUpChart(ui->cardUsedChart, "How many times cards were shown");

#ifdef EREADER
    qDebug() << "Setting waveform mode";
    KoboPlatformFunctions::setFullScreenRefreshMode(WaveForm_GC16);
#endif
    if(ereader) {
        this->move(0, 0);
        this->setFixedSize(ereaderVars::screenX, ereaderVars::screenY);
        ui->cardUsedChart->setFixedHeight(800);
        ui->cardBoxesChart->setFixedHeight(800);

        // QTextBrowser has here some wierd problems
        //ui->cardBoxesChart->setFixedSize(600, 600);
        //ui->textBrowser->setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContents);
        ui->scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
        ui->scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

        this->adjustSize();
    }

    if(pc) {
        ui->exitButton->setVisible(true);
    }

    ui->textBrowser->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->textBrowser->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->textBrowser->setLineWrapMode(QTextEdit::WidgetWidth);
    ui->textBrowser->setWordWrapMode(QTextOption::WrapAtWordBoundaryOrAnywhere);

    ui->scrollArea->verticalScrollBar()->setStyleSheet(
        "QScrollBar:vertical { width: 50px; }");

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

    QString stats = getStatsForSession(session, true, true, true);

    qDebug() << "The stats are:" << stats;

    ui->textBrowser->setText(stats);
    QApplication::processEvents();
    // To make it fit...
    qDebug() << "ui->textBrowser->height()" << ui->textBrowser->height();
    qDebug() << "ui->textBrowser->document()->size().height()" << ui->textBrowser->document()->size().height();
    if(ui->textBrowser->height() < ui->textBrowser->document()->size().height()) {
        ui->textBrowser->setFixedHeight(ui->textBrowser->document()->size().height() + 20);
    }

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

void statistics::on_exitButton_clicked()
{
    this->close();
}

