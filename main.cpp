#include "mainwindow.h"
#include "dialog.h"
#include "connection.h"
#include "gestionressources.h"
#include <QApplication>
#include <QMessageBox>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Connection c;
    bool test = c.createconnect();

    if (test) {
        QMessageBox::information(nullptr, QObject::tr("Database Status"),
                                 QObject::tr("Connexion à la base réussie."),
                                 QMessageBox::Ok);

        Dialog loginDialog;
        loginDialog.show();

        return a.exec();
    } else {
        QMessageBox::critical(nullptr, QObject::tr("Database Status"),
                              QObject::tr("Échec de la connexion à la base."),
                              QMessageBox::Ok);
        return -1;
    }
}
