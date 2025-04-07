#include "contracteur.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QSqlDatabase>

Contracteur::Contracteur() {
    id_contracteur = 0;
    nom = "";
    prenom = "";
    telephone = "";
    adresse = "";
    email = "";
    domaine = "";
    historique = "";
    avisclients = "";
}

Contracteur::Contracteur(int id, QString n, QString p, QString t, QString a, QString e, QString d, QString h, QString ac) {
    id_contracteur = id;
    nom = n;
    prenom = p;
    telephone = t;
    adresse = a;
    email = e;
    domaine = d;
    historique = h;
    avisclients = ac;
}

bool Contracteur::ajouter() {
    // Ensure the database connection is open
    if (!QSqlDatabase::database().isOpen()) {
        qDebug() << "Database is not open!";
        return false;
    }

    QSqlQuery query;
    query.prepare("INSERT INTO contracteurs (id_contracteur, nom, prenom, telephone, adresse, email, domaine) "
                  "VALUES (:id_contracteur, :nom, :prenom, :telephone, :adresse, :email, :domaine)");
    query.bindValue(":id_contracteur", id_contracteur);
    query.bindValue(":nom", nom);
    query.bindValue(":prenom", prenom);
    query.bindValue(":telephone", telephone);
    query.bindValue(":adresse", adresse);
    query.bindValue(":email", email);
    query.bindValue(":domaine", domaine);

    if (!query.exec()) {
        qDebug() << "Error adding contracteur:" << query.lastError().text();
        qDebug() << "Query executed:" << query.lastQuery();
        qDebug() << "Bound values:" << query.boundValues();
        return false;
    }
    return true;
}

QSqlQueryModel* Contracteur::afficher() {
    QSqlQueryModel* model = new QSqlQueryModel();
    model->setQuery("SELECT * FROM contracteurs");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Prenom"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Telephone"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("Adresse"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("Email"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("Domaine"));
    model->setHeaderData(7, Qt::Horizontal, QObject::tr("Historique"));
    model->setHeaderData(8, Qt::Horizontal, QObject::tr("AvisClients"));
    return model;
}

bool Contracteur::modifier(int id) {
    QSqlQuery query;
    query.prepare("UPDATE contracteurs SET nom = :nom, prenom = :prenom, telephone = :telephone, adresse = :adresse, email = :email, domaine = :domaine WHERE id_contracteur = :id");
    query.bindValue(":id", id);
    query.bindValue(":nom", nom);
    query.bindValue(":prenom", prenom);
    query.bindValue(":telephone", telephone);
    query.bindValue(":adresse", adresse);
    query.bindValue(":email", email);
    query.bindValue(":domaine", domaine);

    if (!query.exec()) {
        qDebug() << "Error modifying contracteur:" << query.lastError().text();
        return false;
    }
    return true;
}

bool Contracteur::supprimer(int id) {
    QSqlQuery query;
    query.prepare("DELETE FROM contracteurs WHERE id_contracteur = :id");
    query.bindValue(":id", id);

    if (!query.exec()) {
        qDebug() << "Error deleting contracteur:" << query.lastError().text();
        return false;
    }

    reassignIds(); // Reassign IDs after deletion
    return true;
}

void Contracteur::reassignIds() {
    QSqlQuery selectQuery("SELECT id_contracteur FROM contracteurs ORDER BY id_contracteur ASC");
    QList<int> ids;

    // Fetch all IDs
    while (selectQuery.next()) {
        ids.append(selectQuery.value(0).toInt());
    }

    // Reassign IDs sequentially
    for (int i = 0; i < ids.size(); ++i) {
        QSqlQuery updateQuery;
        updateQuery.prepare("UPDATE contracteurs SET id_contracteur = :new_id WHERE id_contracteur = :old_id");
        updateQuery.bindValue(":new_id", i + 1);
        updateQuery.bindValue(":old_id", ids[i]);

        if (!updateQuery.exec()) {
            qDebug() << "Error reassigning ID from" << ids[i] << "to" << (i + 1) << ":" << updateQuery.lastError().text();
        }
    }
}

QSqlError Contracteur::getLastError() const {
    QSqlQuery query;
    return query.lastError();
}
