#include "connection.h"
#include <QSqlError>
#include <QDebug>

Connection::Connection()
{
    // Constructor can be left empty
}

bool Connection::createconnect()
{
    bool test = false;
    QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
    db.setDatabaseName("InnovArch"); // Set the correct data source name
    db.setUserName("maram");         // Correct username
    db.setPassword("1234");          // Correct password

    if (db.open()) {
        qDebug() << "Database connected successfully.";
        test = true;
    } else {
        qDebug() << "Database connection failed: " << db.lastError().text();
    }

    return test;
}
