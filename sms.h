#ifndef SMS_H
#define SMS_H

#include <QObject>
#include <QString>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>
#include <QSqlDatabase>
#include "mainwindow.h"
#include "ui_mainwindow.h"

class SMS : public QObject
{
    Q_OBJECT

public:
    explicit SMS(QObject *parent = nullptr);
    ~SMS();

    bool envoyerStatutProjetAuClient(int idClient);

private:
    QString recupererStatutProjet(int idClient);
    QString recupererNumeroClient(int idClient);
    bool envoyerSMS(const QString &numero, const QString &message);
    Ui::MainWindow *ui;


    QNetworkAccessManager *manager;
};

#endif // SMS_H
