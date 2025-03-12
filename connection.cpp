#include "connection.h"
#include <QDebug>
#include <QSqlDatabase>
#include <QSqlError>

Connection::Connection(){}

bool Connection::createconnect()
{
    bool test=false;
    QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
    db.setDatabaseName("InnovArch");//inserer le nom de la source de données
    db.setUserName("maram");//inserer nom de l'utilisateur
    db.setPassword("1234");//inserer mot de passe de cet utilisateur
    if (db.open()) test=true;
    return test;
}
void Connection::closeConnection(){db.close();}
