#include "contracteur.h"

Contracteur::Contracteur() {
    id = 0;
    nom = prenom = telephone = adresse = email = domaine = historique = avisClients = "";
}

Contracteur::Contracteur(int id, QString nom, QString prenom, QString telephone, QString adresse, QString email, QString domaine, QString historique, QString avisClients) {
    this->id = id;
    this->nom = nom;
    this->prenom = prenom;
    this->telephone = telephone;
    this->adresse = adresse;
    this->email = email;
    this->domaine = domaine;
    this->historique = historique;
    this->avisClients = avisClients;
}

bool Contracteur::ajouter() {
    QSqlQuery query;
    query.prepare("INSERT INTO contracteurs (Nom, Prenom, Telephone, Adresse, Email, Domaine, Historique, AvisClients) "
                  "VALUES (:nom, :prenom, :telephone, :adresse, :email, :domaine, :historique, :avisClients)");

    query.bindValue(":nom", nom);
    query.bindValue(":prenom", prenom);
    query.bindValue(":telephone", telephone);
    query.bindValue(":adresse", adresse);
    query.bindValue(":email", email);
    query.bindValue(":domaine", domaine);
    query.bindValue(":historique", historique);
    query.bindValue(":avisClients", avisClients);

    return query.exec();
}

QSqlQueryModel* Contracteur::afficher() {
    QSqlQueryModel *model = new QSqlQueryModel();
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
    query.prepare("UPDATE contracteurs SET Nom=:nom, Prenom=:prenom, Telephone=:telephone, Adresse=:adresse, "
                  "Email=:email, Domaine=:domaine, Historique=:historique, AvisClients=:avisClients WHERE ID_contracteur=:id");

    query.bindValue(":id", id);
    query.bindValue(":nom", nom);
    query.bindValue(":prenom", prenom);
    query.bindValue(":telephone", telephone);
    query.bindValue(":adresse", adresse);
    query.bindValue(":email", email);
    query.bindValue(":domaine", domaine);
    query.bindValue(":historique", historique);
    query.bindValue(":avisClients", avisClients);

    return query.exec();
}

bool Contracteur::supprimer(int id) {
    QSqlQuery query;
    query.prepare("DELETE FROM contracteurs WHERE ID_contracteur = :id");
    query.bindValue(":id", id);
    return query.exec();
}
