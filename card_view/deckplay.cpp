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
    // Everything is done in update(), this should be  fixed for the future

    // This could be editable in settings
    ui->scrollArea->verticalScrollBar()->setStyleSheet(
        "QScrollBar:vertical { width: 50px; }");

    // This could be editable in settings
    ui->horizontalScrollBar->setStyleSheet("QScrollBar:horizontal { height: 50px; }");
}

DeckPlay::~DeckPlay()
{
    delete ui;
}

void DeckPlay::update(QDir dir, int mode_new)
{
    // This is just provifing values and then updating
    deck_dir = dir;
    mode = mode_new;

    //media_file = QFile{deck_dir.path() + "/media"};
    media_file.setFileName(deck_dir.path() + "/media");

    QString message = "media file is: ";
    message.append(media_file.fileName());
    global_fun::log(message, log_file, "update");
    if(media_file.exists() == true)
    {
        global_fun::log("media file exists", log_file, "update");
    } else {
        global_fun::log("media file does not exists", log_file, "update");
    }

    QStringList string_list = {deck_dir.path()};

    // Pretty important
    ui->textBackCard->setSearchPaths(string_list);
    ui->textFrontCard->setSearchPaths(string_list);

    //connect(ui->textBackCard->horizontalScrollBar(), SIGNAL(isVisible()), this, SLOT(hor_scroll_back_showed()));
    //connect(ui->textFrontCard->horizontalScrollBar(), SIGNAL(isVisible()), this, SLOT(hor_scroll_front_showed()));

    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &DeckPlay::check_if_scrollbars_showe);
    timer->start(200);

    start();
}

void DeckPlay::start()
{
    // Support for this newer anki database... why did they break it
    if(QFile{deck_dir.path() + "/collection.anki21"}.exists() == true)
    {
        db_path_str = deck_dir.path() + "/collection.anki21";
    } else {
        db_path_str = deck_dir.path() + "/collection.anki2";
    }

    QFile db_path{db_path_str};

    if (db_path.exists() == true)
    {
        db = QSqlDatabase::addDatabase("QSQLITE");
        db.setDatabaseName(db_path_str);
        // http://katecpp.github.io/sqlite-with-qt/

        if (db.open() == true)
        {
           // Everything is good, start making the GUI, check mode
           if(mode == 1) // Completly random
           {
               mode_crandom_setup();
           }
        }
        else
        {
           global_fun::log("Database: connection with database failed", log_file, "start");
        }
    }
    else
    {
        global_fun::log("Database: doesn't exist", log_file, "start");
    }
}

void DeckPlay::mode_crandom_setup()
{
    // Setup show / next card button
    show_card* show_card_widget = new show_card;
    connect(show_card_widget, SIGNAL(clicked()), this, SLOT(show_back_next())); // Button slot
    connect(this, SIGNAL(show_button_text(QString)), show_card_widget, SLOT(set_text(QString)));
    connect(this, SIGNAL(next_card_call()), this, SLOT(mode_crandom_loop())); // a loop it is 1
    ui->gridManageCard->addWidget(show_card_widget);

    // a loop it is 2
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


    scroll_bar_setted_front = 0;
    // this is done in next card call
    // scroll_bar_setted_back = 0;
    ui->horizontalScrollBar->hide();
    hor_scroll_front_needed = false;
    ui->textFrontCard->horizontalScrollBar()->show();

    // Some magic: at the launch it shows height 0, and with this it is a bit bigger. not an ideal solution
    if(first_launch == true)
    {
        first_launch = false;
        mode_crandom_loop();
    }

    // This needs to be done after setText becouse it will Segment fault
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

        scroll_bar_setted_back = 0;
        hor_scroll_back_needed = false;
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
        for(QString item: split_dot)
        {
            media_contend = media_contend.replace("\"", "");

            QString message4 = "item is: ";
            message4.append(item);
            global_fun::log(message4, log_file, "media_contend");

            QStringList replace_items = item.split(":");
            if(main_card.contains(replace_items.last()))
            {
                global_fun::log("main_card contains items_last", log_file, "media_contend");
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
    QString message3 = "cards splitted are: ";
    for(QString card: cards)
    {
        message3.append(card);
        message3.append(",");
    }
    global_fun::log(message3, log_file, "parse_string");

    front_card = cards.first();
    back_card = cards.last();

    QString message2 = "front_card is: ";
    message2.append(front_card);
    global_fun::log(message2, log_file, "parse_string");

    QString message = "back_card is: ";
    message.append(back_card);
    global_fun::log(message, log_file, "parse_string");

}

void DeckPlay::on_textBackCard_textChanged()
{
    QString message = "back card document size is: ";
    int height = ui->textBackCard->document()->size().height();
    message.append(QString::number(height));
    global_fun::log(message, log_file, "on_textBackCard_textChanged");

    ui->textBackCard->setFixedHeight(height);
}

void DeckPlay::on_textFrontCard_textChanged()
{
        QString message = "front card document size is: ";
        int height = ui->textFrontCard->document()->size().height();
        message.append(QString::number(height));
        global_fun::log(message, log_file, "on_textFrontCard_textChanged");

        ui->textFrontCard->setFixedHeight(height);
}

void DeckPlay::on_horizontalScrollBar_valueChanged(int value)
{
    // value can be on minus range?
    if(hor_scroll_back_needed == true)
    {
        ui->textBackCard->horizontalScrollBar()->setSliderPosition(ui->horizontalScrollBar->sliderPosition() + value);
    }
    if(hor_scroll_front_needed == true)
    {
        ui->textFrontCard->horizontalScrollBar()->setSliderPosition(ui->horizontalScrollBar->sliderPosition() + value);
    }

    /*
    QString message = "slider salue changed: ";
    message.append(QString::number(value));
    global_fun::log(message, log_file, "on_horizontalScrollBar_valueChanged");
    */
}

// this one didn't worked
// void DeckPlay::on_horizontalScrollBar_sliderMoved(int position)

void DeckPlay::check_if_scrollbars_showe()
{
    if(scroll_bar_setted_front < 10)
    {
        scroll_bar_setted_front = scroll_bar_setted_front + 1;
        if(ui->textFrontCard->horizontalScrollBar()->isVisible() == true)
        {
                // its the only place in this code that this is showed too late
                //global_fun::log("textFrontCard horizontalScrollBar is visible", log_file, "mode_crandom_loop");
                ui->textFrontCard->horizontalScrollBar()->hide();
                // https://forum.qt.io/topic/45543/sethorizontalscrollbar-deletes-the-scrollbar-instead-of-the-former-scrollbar-and-has-no-effect-in-my-qgraphicsview
                // yea this didn't worked

                hor_scroll_front_needed = true;
                ui->horizontalScrollBar->setMinimum(ui->textFrontCard->horizontalScrollBar()->minimum());
                ui->horizontalScrollBar->setMaximum(ui->textFrontCard->horizontalScrollBar()->maximum());
                ui->horizontalScrollBar->setSingleStep(ui->textFrontCard->horizontalScrollBar()->singleStep());
                ui->horizontalScrollBar->setPageStep(ui->textFrontCard->horizontalScrollBar()->pageStep());
                ui->horizontalScrollBar->setSliderPosition(ui->textFrontCard->horizontalScrollBar()->sliderPosition());
                ui->horizontalScrollBar->show();
        } else {
            //global_fun::log("textFrontCard horizontalScrollBar is not visible", log_file, "mode_crandom_loop");
            //ui->textFrontCard->horizontalScrollBar()->show();
        }
    }



    if(scroll_bar_setted_back < 10)
    {
        scroll_bar_setted_back = scroll_bar_setted_back + 1;
        if(ui->textBackCard->horizontalScrollBar()->isVisible() == true)
        {
                // its the only place in this code that this is showed too late
                //global_fun::log("textBackCard horizontalScrollBar is visible", log_file, "show_back_next");
                ui->textBackCard->horizontalScrollBar()->hide();
                // https://forum.qt.io/topic/45543/sethorizontalscrollbar-deletes-the-scrollbar-instead-of-the-former-scrollbar-and-has-no-effect-in-my-qgraphicsview
                // yea this didn't worked

                hor_scroll_back_needed = true;
                ui->horizontalScrollBar->setMinimum(ui->textBackCard->horizontalScrollBar()->minimum());
                ui->horizontalScrollBar->setMaximum(ui->textBackCard->horizontalScrollBar()->maximum());
                ui->horizontalScrollBar->setSingleStep(ui->textBackCard->horizontalScrollBar()->singleStep());
                ui->horizontalScrollBar->setPageStep(ui->textBackCard->horizontalScrollBar()->pageStep());
                ui->horizontalScrollBar->setSliderPosition(ui->textBackCard->horizontalScrollBar()->sliderPosition());
                ui->horizontalScrollBar->show();
        } else {
            //global_fun::log("textBackCard horizontalScrollBar is not visible", log_file, "show_back_next");
            //ui->textBackCard->horizontalScrollBar()->show();
        }
    }

}
