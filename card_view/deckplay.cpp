#include "card_view/deckplay.h"
#include "ui_deckplay.h"
#include "card_view/show_card.h"
#include "globals.h"

#include <QDebug>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QSqlTableModel>
#include <QScrollBar>
#include <QTimer>

/*
 * Note about scroll bars: Qt is so buggy with those, there were needed many workaround and hacks... its a mess
*/

DeckPlay::DeckPlay(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::DeckPlay)
{
    ui->setupUi(this);

    if(ereader) {
        // This could be editable in settings
        ui->scrollArea->verticalScrollBar()->setStyleSheet(
            "QScrollBar:vertical { width: 50px; }");

        // This could be editable in settings
        ui->horizontalScrollBar->setStyleSheet("QScrollBar:horizontal { height: 50px; }");
    }
}

DeckPlay::~DeckPlay()
{
    delete ui;
}

void DeckPlay::update(QDir dir, DeckModes modeNew)
{
    // This is just providing values and then updating
    deckDir = dir;
    mode = modeNew;

    //media_file = QFile{deckDir.path() + "/media"};
    media_file.setFileName(deckDir.path() + "/media");

    qDebug() << "media file is: " << media_file.fileName();
    if (media_file.exists()) {
        qDebug() << "media file exists";
    } else {
        qDebug() << "media file does not exist";
    }

    QStringList string_list = {deckDir.path()};

    // Pretty important
    ui->textBackCard->setSearchPaths(string_list);
    ui->textFrontCard->setSearchPaths(string_list);

    //connect(ui->textBackCard->horizontalScrollBar(), SIGNAL(isVisible()), this, SLOT(hor_scroll_back_showed()));
    //connect(ui->textFrontCard->horizontalScrollBar(), SIGNAL(isVisible()), this, SLOT(hor_scroll_front_showed()));

    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &DeckPlay::checkIfScrollbarsToShow);
    timer->start(200);

    start();
}

void DeckPlay::start()
{
    // Support for this newer anki database... why did they break it
    if(QFile{deckDir.path() + "/collection.anki21"}.exists() == true)
    {
        db_path_str = deckDir.path() + "/collection.anki21";
    } else {
        db_path_str = deckDir.path() + "/collection.anki2";
    }

    QFile dbPath{db_path_str};

    if (dbPath.exists() == true)
    {
        db = QSqlDatabase::addDatabase("QSQLITE");
        db.setDatabaseName(db_path_str);
        // http://katecpp.github.io/sqlite-with-qt/

        if (db.open() == true)
        {
           // Everything is good, start making the GUI, check mode
           if(mode == CompletlyRandomised) // Completly random
           {
               modeCRandomSetup();
           }else if(mode == RandomisedNoRepeating) // Random - no repeat
           {
               modeRandomNoRepeatSetup();
           }
        }
        else
        {
           qDebug() << "Database: connection with database failed";
        }
    }
    else
    {
        qDebug() << "Database: doesn't exist";
    }
}

void DeckPlay::modeCRandomSetup()
{
    // Setup show / next card button
    show_card* show_card_widget = new show_card;
    connect(show_card_widget, SIGNAL(clicked()), this, SLOT(show_back_next())); // Button slot
    connect(this, SIGNAL(show_button_text(QString)), show_card_widget, SLOT(set_text(QString)));
    connect(this, SIGNAL(next_card_call()), this, SLOT(mode_crandom_loop())); // a loop it is 1
    ui->gridManageCard->addWidget(show_card_widget);

    mode_crandom_loop();
}

void DeckPlay::mode_crandom_loop()
{
    QSqlQuery query_id = db.exec("SELECT id FROM notes ORDER BY RANDOM() LIMIT 1");
    query_id.next();
    // its too big for int
    QString id_str = query_id.value(0).toString(); // random id

    // set variables
    QString main_std_sql = "SELECT flds FROM notes WHERE id=" + id_str;

    QSqlQuery main_query = db.exec(main_std_sql);
    main_query.next();
    main_card = main_query.value(0).toString();

    // Parse the text
    parse_string();

    ui->textFrontCard->setText(front_card);


    scrollBarSettedFront = 0;
    // this is done in next card call
    // scrollBarSettedBack = 0;
    ui->horizontalScrollBar->hide();
    HorizontalScrollOnFrontNeeded = false;
    ui->textFrontCard->horizontalScrollBar()->show();

    // Some magic: at the launch it shows height 0, and with this it is a bit bigger. not an ideal solution
    if(first_launch == true)
    {
        first_launch = false;
        mode_crandom_loop();
    }

    // This isEmpty() needs to be done after setText becouse it will Segment fault
    if(ui->textFrontCard->document()->isEmpty() == false)
    {
        ui->textFrontCard->selectAll();
        ui->textFrontCard->setAlignment(Qt::AlignCenter);

        // This removes selection
        QTextCursor cursor = ui->textFrontCard->textCursor();
        cursor.clearSelection();
        ui->textFrontCard->setTextCursor(cursor);
    }
}

void DeckPlay::modeRandomNoRepeatSetup()
{

    // Setup show / next card button
    show_card* show_card_widget = new show_card;
    connect(show_card_widget, SIGNAL(clicked()), this, SLOT(show_back_next())); // Button slot
    connect(this, SIGNAL(show_button_text(QString)), show_card_widget, SLOT(set_text(QString)));
    connect(this, SIGNAL(next_card_call()), this, SLOT(mode_random_norepeat_loop())); // a loop it is 1
    ui->gridManageCard->addWidget(show_card_widget);


    QSqlQuery query_count = db.exec("SELECT COUNT(id) FROM notes as whatthefuck");
    query_count.next();
    no_repeat_list = query_count.value(0).toInt();

    qDebug() << "column in notes: " << no_repeat_list;

    mode_random_norepeat_loop();
}

void DeckPlay::mode_random_norepeat_loop()
{
    if(no_repeat_ids.count() == no_repeat_list)
    {
        int remove_first = no_repeat_ids.count() - (no_repeat_ids.count() / 3);
        if(remove_first == 0)
        {
            // shouldnt happen
            no_repeat_ids.clear();
        }
        for(int i = 0; i <= remove_first; ++i)
        {
            no_repeat_ids.removeFirst();
        }
    }

    bool looping = true;
    QString id_str;
    while(looping == true)
    {
        QSqlQuery query_id = db.exec("SELECT id FROM notes ORDER BY RANDOM() LIMIT 1");
        query_id.next();
        QString id_str_unchecked = query_id.value(0).toString(); // random id
        if(no_repeat_ids.contains(id_str_unchecked) == false)
        {
            id_str = id_str_unchecked;
            no_repeat_ids.append(id_str_unchecked);
            looping = false;
        }
    }

    // set variables
    QString main_std_sql = "SELECT flds FROM notes WHERE id=" + id_str;

    QSqlQuery main_query = db.exec(main_std_sql);
    main_query.next();
    main_card = main_query.value(0).toString();

    // Parse the text
    parse_string();

    ui->textFrontCard->setText(front_card);
    // This fixes the issue with not showing the first line. it simply moved the scrollbar a bit and there were problems. the scrollbar was hided
    ui->textFrontCard->verticalScrollBar()->setValue(0);

    scrollBarSettedFront = 0;
    // this is done in next card call
    // scrollBarSettedBack = 0;
    ui->horizontalScrollBar->hide();
    HorizontalScrollOnFrontNeeded = false;
    ui->textFrontCard->horizontalScrollBar()->show();

    // Some magic: at the launch it shows height 0, and with this it is a bit bigger. not an ideal solution
    if(first_launch == true)
    {
        first_launch = false;
        mode_crandom_loop();
    }

    // This isEmpty() needs to be done after setText becouse it will Segment fault
    if(ui->textFrontCard->document()->isEmpty() == false)
    {
        ui->textFrontCard->selectAll();
        ui->textFrontCard->setAlignment(Qt::AlignCenter);

        // This removes selection
        QTextCursor cursor = ui->textFrontCard->textCursor();
        cursor.clearSelection();
        ui->textFrontCard->setTextCursor(cursor);
    }

    // This fixes the issue with not showing the first line. it simply moved the scrollbar a bit and there were problems. the scrollbar was hided
    // this needs to be here too...
    ui->textFrontCard->verticalScrollBar()->setValue(0);
}

void DeckPlay::show_back_next()
{
    if (showed_back == false)
    {
        showed_back = true;
        ui->textBackCard->setText(back_card);

        // This needs to be done after setText becouse it will Segment fault
        if(ui->textBackCard->document()->isEmpty() == false)
        {
            ui->textBackCard->selectAll();
            ui->textBackCard->setAlignment(Qt::AlignCenter);

            // This removes selection
            QTextCursor cursor = ui->textBackCard->textCursor();
            cursor.clearSelection();
            ui->textBackCard->setTextCursor(cursor);
        }

        scrollBarSettedBack = 0;
        HorizontalScrollOnBackNeeded = false;
        ui->textBackCard->horizontalScrollBar()->show();

        // This fixes the issue with not showing the first line. it simply moved the scrollbar a bit and there were problems. the scrollbar was hided
        ui->textBackCard->verticalScrollBar()->setValue(0);

        emit show_button_text("Next Card");
    }
    else
    {
        showed_back = false;
        emit show_button_text("Show");
        ui->textBackCard->setText("");

        emit next_card_call();
    }

}

void DeckPlay::parse_string()
{
    // turn those weird image id's to file names
    // this is a json file, but a weird one so...
    // TODO: In the future this needs to be done using json parsing.
    if(main_card.contains("<img src="))
    {
        media_file.open(QIODevice::ReadOnly);
        QString media_contend = media_file.readAll();
        media_file.close();

        media_contend = media_contend.replace("{", "");
        media_contend = media_contend.replace("}", "");

        // This is impossible becouse of:  "7": "rew-zasada lewej 1.png"
        // media_contend = media_contend.replace(" ", "");
        // for now this:
        media_contend = media_contend.replace(": ", ":");
        media_contend = media_contend.replace(", ", ",");

        QStringList split_dot = media_contend.split(",");
        for(const QString &item: split_dot)
        {
            media_contend = media_contend.replace("\"", "");

            qDebug() << "item is: " << item;

            QStringList replace_items = item.split(":");
            if(main_card.contains(replace_items.last()))
            {
               qDebug() << "main_card contains items_last";
               main_card = main_card.replace(replace_items.last(), replace_items.first());
            }
        }
    }

    // Weird: &nbsp; ( hard space in html ) sometimes doesn't get parsed
    main_card = main_card.replace("&nbsp;", " ");

    // Add a line at the end becouse one line is cutted out...
    main_card.append("<br>");

    // main_all is:
    // front_card + this character https://unicode-table.com/en/001F/ + back_card

    QStringList cards = main_card.split("\u001F");
    qDebug() << "cards splitted are: " << cards;

    front_card = cards.first();
    back_card = cards.last();

    qDebug() << "front_card is: " << front_card;
    qDebug() << "back_card is: " << back_card;
}

void DeckPlay::on_textBackCard_textChanged()
{
    int height = ui->textBackCard->document()->size().height();
    qDebug() << "back card document size is: " << height << "pixels";

    ui->textBackCard->setFixedHeight(height);
}

void DeckPlay::on_textFrontCard_textChanged()
{
    int height = ui->textFrontCard->document()->size().height();
    qDebug() << "front card document size is: " << height << "pixels";

    ui->textFrontCard->setFixedHeight(height);
}

void DeckPlay::on_horizontalScrollBar_valueChanged(int value)
{
    // value can be on minus range?
    if(HorizontalScrollOnBackNeeded == true)
    {
        ui->textBackCard->horizontalScrollBar()->setSliderPosition(ui->horizontalScrollBar->sliderPosition() + value);
    }
    if(HorizontalScrollOnFrontNeeded == true)
    {
        ui->textFrontCard->horizontalScrollBar()->setSliderPosition(ui->horizontalScrollBar->sliderPosition() + value);
    }

    qDebug() << "slider salue changed:" << value;
}

// this one didn't worked
// void DeckPlay::on_horizontalScrollBar_sliderMoved(int position)
void DeckPlay::checkIfScrollbarsToShow()
{
    qDebug() << "checkIfScrollbarsToShow launched";
    if(scrollBarSettedFront < 10)
    {
        scrollBarSettedFront = scrollBarSettedFront + 1;
        if(ui->textFrontCard->horizontalScrollBar()->isVisible() == true)
        {
                qDebug() << "textFrontCard horizontalScrollBar is visible";
                ui->textFrontCard->horizontalScrollBar()->hide();
                // https://forum.qt.io/topic/45543/sethorizontalscrollbar-deletes-the-scrollbar-instead-of-the-former-scrollbar-and-has-no-effect-in-my-qgraphicsview
                // yea this didn't worked

                HorizontalScrollOnFrontNeeded = true;
                ui->horizontalScrollBar->setMinimum(ui->textFrontCard->horizontalScrollBar()->minimum());
                ui->horizontalScrollBar->setMaximum(ui->textFrontCard->horizontalScrollBar()->maximum());
                ui->horizontalScrollBar->setSingleStep(ui->textFrontCard->horizontalScrollBar()->singleStep());
                ui->horizontalScrollBar->setPageStep(ui->textFrontCard->horizontalScrollBar()->pageStep());
                ui->horizontalScrollBar->setSliderPosition(ui->textFrontCard->horizontalScrollBar()->sliderPosition());
                ui->horizontalScrollBar->show();
        } else {
            qDebug() << "textFrontCard horizontalScrollBar is not visible";
        }
    }

    if(scrollBarSettedBack < 10)
    {
        scrollBarSettedBack = scrollBarSettedBack + 1;
        if(ui->textBackCard->horizontalScrollBar()->isVisible() == true)
        {
                qDebug() << "textBackCard horizontalScrollBar is visible";
                ui->textBackCard->horizontalScrollBar()->hide();

                HorizontalScrollOnBackNeeded = true;
                ui->horizontalScrollBar->setMinimum(ui->textBackCard->horizontalScrollBar()->minimum());
                ui->horizontalScrollBar->setMaximum(ui->textBackCard->horizontalScrollBar()->maximum());
                ui->horizontalScrollBar->setSingleStep(ui->textBackCard->horizontalScrollBar()->singleStep());
                ui->horizontalScrollBar->setPageStep(ui->textBackCard->horizontalScrollBar()->pageStep());
                ui->horizontalScrollBar->setSliderPosition(ui->textBackCard->horizontalScrollBar()->sliderPosition());
                ui->horizontalScrollBar->show();
        } else {
            qDebug() << "textBackCard horizontalScrollBar is not visible";
        }
    }

}
