#include "contrats.h"
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QVariant>
#include <QMap>

contrats::contrats() {}

contrats::contrats(int id, double montant, QString dateDebut, QString dateFin, QString statut, int idProjet, int idClient)
    : id(id), montantTotal(montant), dateDebut(dateDebut), dateFin(dateFin), statutPaiement(statut), idProjet(idProjet), idClient(idClient) {}

bool contrats::ajouter() {
    QSqlQuery query;
    query.prepare("INSERT INTO contrats (ID_CONTRAT, MONTANT_TOTAL, DATE_DEBUT, DATE_FIN, STATUT_PAIEMENT, ID_PROJET, ID_CLIENT) "
                  "VALUES (:id, :montant, TO_DATE(:dateDebut, 'YYYY-MM-DD'), TO_DATE(:dateFin, 'YYYY-MM-DD'), :statut, :idProjet, :idClient)");
    query.bindValue(":id", id);
    query.bindValue(":montant", montantTotal);
    query.bindValue(":dateDebut", dateDebut);
    query.bindValue(":dateFin", dateFin);
    query.bindValue(":statut", statutPaiement);
    query.bindValue(":idProjet", idProjet);
    query.bindValue(":idClient", idClient);
    return query.exec();
}

QSqlQueryModel* contrats::afficher() {
    QSqlQueryModel* model = new QSqlQueryModel();
    model->setQuery("SELECT * FROM contrats");
    return model;
}

bool contrats::supprimer(int id) {
    QSqlQuery query;
    query.prepare("DELETE FROM contrats WHERE ID_CONTRAT = :id");
    query.bindValue(":id", id);
    return query.exec();
}

bool contrats::modifier(int id) {
    QSqlQuery query;
    query.prepare("UPDATE contrats SET MONTANT_TOTAL = :montant, DATE_DEBUT = TO_DATE(:dateDebut, 'YYYY-MM-DD'), DATE_FIN = TO_DATE(:dateFin, 'YYYY-MM-DD'), "
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

QSqlQueryModel* contrats::rechercher(const QString &critere) {
    QSqlQueryModel* model = new QSqlQueryModel();
    model->setQuery("SELECT * FROM contrats WHERE ID_CONTRAT LIKE '%" + critere + "%' OR STATUT_PAIEMENT LIKE '%" + critere + "%'");
    return model;
}

QSqlQueryModel* contrats::trier(const QString &critere, const QString &ordre) {
    QSqlQueryModel* model = new QSqlQueryModel();
    model->setQuery("SELECT * FROM contrats ORDER BY " + critere + " " + ordre);
    return model;
}

QMap<QString, int> contrats::statistiques() {
    QMap<QString, int> stats;
    QSqlQuery query;
    query.exec("SELECT STATUT_PAIEMENT, COUNT(*) FROM contrats GROUP BY STATUT_PAIEMENT");
    while (query.next()) {
        stats.insert(query.value(0).toString(), query.value(1).toInt());
    }
    return stats;
}
