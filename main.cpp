#include "mainwindow.h"
#include "gestionressources.h"
#include <QApplication>
#include <QMessageBox>
#include "connection.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    Connection c;
    bool test = c.createconnect();
    if (test) {
        MainWindow w;
        w.show();
        QMessageBox::information(nullptr, QObject::tr("Database is open"),
                                 QObject::tr("Connection successful.\n"
                                             "Click Cancel to exit."),
                                 QMessageBox::Cancel);
    return a.exec();
    } else {
        QMessageBox::critical(nullptr, QObject::tr("Database is not open"),
                              QObject::tr("Connection failed.\n"
                                          "Click Cancel to exit."),
                              QMessageBox::Cancel);
        return -1;
    }
}
