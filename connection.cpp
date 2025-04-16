#include "connection.h"
#include <QDebug>

Connection::Connection() {}

bool Connection::createconnect() {
    bool test = false;
    QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
    db.setDatabaseName("InnovArch"); // Insert the name of the data source
    db.setUserName("maram"); // Insert the username
    db.setPassword("1234"); // Insert the password

    if (db.open()) {
        test = true;
        qDebug() << "Database connection established.";
    } else {
        qDebug() << "Database connection failed:" << db.lastError().text();
    }

    return test;
}