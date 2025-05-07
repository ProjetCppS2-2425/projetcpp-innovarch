#include "contrats.h"
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QVariant>
#include <QMap>
#include <QSqlError>
#include <QDebug>

contrats::contrats() {}

contrats::contrats(int id, double montant, QString dateDebut, QString dateFin, QString statut, int idProjet, int idClient)
    : id(id), montantTotal(montant), dateDebut(dateDebut), dateFin(dateFin), statutPaiement(statut), idProjet(idProjet), idClient(idClient) {}

bool contrats::ajouter() {
    QSqlQuery query;
    query.prepare("INSERT INTO CONTRATS (ID_CONTRAT, MONTANT_TOTAL, DATE_DEBUT, DATE_FIN, STATUT_PAIEMENT, ID_PROJET, ID_CLIENT) "
                  "VALUES (:id, :montant, TO_DATE(:dateDebut, 'YYYY-MM-DD'), TO_DATE(:dateFin, 'YYYY-MM-DD'), :statut, :idProjet, :idClient)");
    query.bindValue(":id", id);
    query.bindValue(":montant", montantTotal);
    query.bindValue(":dateDebut", dateDebut);
    query.bindValue(":dateFin", dateFin);
    query.bindValue(":statut", statutPaiement);
    query.bindValue(":idProjet", idProjet);
    query.bindValue(":idClient", idClient);

    if (!query.exec()) {
        qDebug() << "Erreur ajout contrat:" << query.lastError().text();
        return false;
    }
    return true;
}

QSqlQueryModel * contrats::afficher() {
    QSqlQueryModel * model = new QSqlQueryModel();
    model->setQuery("SELECT * FROM CONTRATS");
    return model;
}

bool contrats::supprimer(int id) {
    QSqlQuery query;
    query.prepare("DELETE FROM CONTRATS WHERE ID_CONTRAT = :id");
    query.bindValue(":id", id);
    return query.exec();
}

bool contrats::modifier(int id) {
    QSqlQuery query;
    query.prepare("UPDATE CONTRATS SET MONTANT_TOTAL = :montant, DATE_DEBUT = TO_DATE(:dateDebut, 'YYYY-MM-DD'), DATE_FIN = TO_DATE(:dateFin, 'YYYY-MM-DD'), "
                  "STATUT_PAIEMENT = :statut, ID_PROJET = :idProjet, ID_CLIENT = :idClient WHERE ID_CONTRAT = :id");
    query.bindValue(":id", id);
    query.bindValue(":montant", montantTotal);
    query.bindValue(":dateDebut", dateDebut);
    query.bindValue(":dateFin", dateFin);
    query.bindValue(":statut", statutPaiement);
    query.bindValue(":idProjet", idProjet);
    query.bindValue(":idClient", idClient);
    return query.exec();
}
QSqlQueryModel *contrats::trier(QString critere) {
    QSqlQueryModel *model = new QSqlQueryModel();
    QString queryStr = "SELECT * FROM CONTRATS";

    if (critere == "montant dec") {
        queryStr += " ORDER BY MONTANT_TOTAL DESC";
    } else if (critere == "montant croi") {
        queryStr += " ORDER BY MONTANT_TOTAL ASC";
    } else if (critere == "date debut dec") {
        queryStr += " ORDER BY DATE_DEBUT DESC";
    } else if (critere == "date debut croi") {
        queryStr += " ORDER BY DATE_DEBUT ASC";
    }

    model->setQuery(queryStr);
    return model;
}
QSqlQueryModel* contrats::rechercher(int id) {
    QSqlQueryModel* model = new QSqlQueryModel();
    QSqlQuery query;
    query.prepare("SELECT * FROM CONTRATS WHERE ID_CONTRAT = :id");
    query.bindValue(":id", id);
    query.exec();
    model->setQuery(query);
    return model;
}
QMap<QString, int> contrats::statistiquesStatut() {
    QMap<QString, int> stats;
    QStringList statuts = {"payé", "en attente", "retard"};

    for (const QString &statut : statuts) {
        QSqlQuery query;
        query.prepare("SELECT COUNT(*) FROM CONTRATS WHERE STATUT_PAIEMENT = :statut");
        query.bindValue(":statut", statut);
        if (query.exec() && query.next()) {
            stats[statut] = query.value(0).toInt();
        } else {
            stats[statut] = 0;
        }
    }

    return stats;
}
