#include "mainwindow.h"
#include <QApplication>
#include <QMessageBox>
#include "connection.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    Connection c;
    if (c.createconnect()) {
        w.show();
        QMessageBox::information(nullptr, QObject::tr("Database Connection"), QObject::tr("Connection successful."));
    } else {
        QMessageBox::critical(nullptr, QObject::tr("Database Connection"), QObject::tr("Connection failed."));
        return -1; // Exit if the database connection fails
    }
    return a.exec();
}
