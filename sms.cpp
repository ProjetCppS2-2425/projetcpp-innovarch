#include "sms.h"

#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QUrl>
#include <QUrlQuery>
#include <QtNetwork/QNetworkRequest>

SMS::SMS(QObject *parent)
    : QObject(parent),
    manager(new QNetworkAccessManager(this))
{
}

SMS::~SMS() {}

bool SMS::envoyerStatutProjetAuClient(int idClient)
{
    QString numero = recupererNumeroClient(idClient);
    QString statut = recupererStatutProjet(idClient);

    if (numero.isEmpty() || statut.isEmpty()) {
        qWarning() << "Numéro ou statut vide.";
        return false;
    }

    QString message = QString("Bonjour ! Le statut de votre projet est : %1").arg(statut);
    return envoyerSMS(numero, message);
}

QString SMS::recupererNumeroClient(int idClient)
{
    QSqlQuery query;

    query.prepare("SELECT telephone FROM clients WHERE id_client = :id");
    query.bindValue(":id", idClient);

    if (query.exec() && query.next()) {
        return query.value(0).toString();
    }

    qWarning() << "Erreur lors de la récupération du numéro:" << query.lastError().text();
    return QString();
}

QString SMS::recupererStatutProjet(int idClient)
{
    QSqlQuery query;
    query.prepare(R"(
    SELECT p.statut
    FROM "PROJETS" p
    JOIN "CLIENTS" c ON c.id_projet = p.id_projet
    WHERE c.id_client = :id
)");

    query.bindValue(":id", idClient);

    if (query.exec() && query.next()) {
        return query.value(0).toString();
    }

    qWarning() << "Erreur lors de la récupération du statut du projet:" << query.lastError().text();
    return QString();
}

bool SMS::envoyerSMS(const QString &numero, const QString &message)
{
    // 1. URL Twilio
    //QUrl url("https://api.twilio.com/2010-04-01/Accounts/ACf80b786d0a097e58100548c9a13a973e/Messages.json");
    QNetworkRequest request(url);

    // 2. Authentification Basic (SID + Token)
   // QString sid = "ACf80b786d0a097e58100548c9a13a973e";
  //  QString token = "3f6e22fc19b8c7b798d6cff2c114dd4b";  // Remplace par ton vrai Auth Token
    QString credentials = sid + ":" + token;
    QByteArray auth = "Basic " + credentials.toUtf8().toBase64();
    request.setRawHeader("Authorization", auth);

    // 3. Corps du message (en format x-www-form-urlencoded)
    QUrlQuery params;
    params.addQueryItem("From", "+19786935715");          // Ton numéro Twilio
    params.addQueryItem("To", numero);                    // Numéro du client (doit être vérifié dans Twilio si en mode trial)
    params.addQueryItem("Body", message);

    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");

    QByteArray postData = params.query(QUrl::FullyEncoded).toUtf8();
    QNetworkReply *reply = manager->post(request, postData);

    // 4. Gérer la réponse
    connect(reply, &QNetworkReply::finished, [reply]() {
        if (reply->error() == QNetworkReply::NoError) {
            qDebug() << "✅ SMS envoyé avec succès via Twilio.";
        } else {
            qWarning() << "❌ Erreur lors de l'envoi du SMS Twilio:" << reply->errorString();
            qDebug() << reply->readAll();
        }
        reply->deleteLater();
    });

    return true;
}

