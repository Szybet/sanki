#include "globals.h"
#include <QDir>

#include <QDebug>

// Get current dir + deck storage paths
QDir work_dir = QDir::current();
//qDebug() << "work_dir" << work_dir.path();

QDir deck_storage = work_dir.path() + "/deck_storage";
//qDebug() << "deck_storage" << deck_storage.path();

QString kobo_model;

bool running_on_kobo;
