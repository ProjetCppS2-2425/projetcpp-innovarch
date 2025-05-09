#include "connection.h"
#include <QDebug>
#include <QSqlDatabase>
#include <QSqlError>

Connection::Connection(){}


bool Connection::createconnect()
{
    bool test = false;
    QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
    db.setDatabaseName("InnovArch"); // Insert the data source name (DSN)
    db.setUserName("maram");          // Insert username
    db.setPassword("1234");          // Insert password

    if (!db.open()) {  // Explicitly try to open the database
        qDebug() << "Database connection error:" << db.lastError().text();
    } else {
        qDebug() << "Connection successful!";
        test = true;
    }

    return test;
}

