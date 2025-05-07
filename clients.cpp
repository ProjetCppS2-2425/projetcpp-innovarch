#include "clients.h"
#include <QDebug>

// Constructeurs
Clients::Clients() {}

Clients::Clients(int id, QString nom, QString prenom, QString email, QString telephone, QString adresse, QString sexe, int id_projet) {
    this->id_client = id;
    this->nom = nom;
    this->prenom = prenom;
    this->email = email;
    this->telephone = telephone;
    this->adresse = adresse;
    this->sexe = sexe;
    this->id_projet = id_projet;
}

// 🔹 Ajouter un client
bool Clients::ajouter() {
    QSqlQuery query;
    query.prepare("INSERT INTO clients (ID_CLIENT, NOM, PRENOM, EMAIL, TELEPHONE, ADRESSE, SEXE, ID_PROJET) "
                  "VALUES (:id, :nom, :prenom, :email, :telephone, :adresse, :sexe, :id_projet)");
    query.bindValue(":id", id_client);
    query.bindValue(":nom", nom);
    query.bindValue(":prenom", prenom);
    query.bindValue(":email", email);
    query.bindValue(":telephone", telephone);
    query.bindValue(":adresse", adresse);
    query.bindValue(":sexe", sexe);
    query.bindValue(":id_projet", id_projet);

    return query.exec();
}

// 🔹 Afficher les clients
QSqlQueryModel * Clients::afficher() {
    QSqlQueryModel * model = new QSqlQueryModel();
    model->setQuery("SELECT * FROM clients");
    return model;
}

// 🔹 Modifier un client
bool Clients::modifier(int id) {
    QSqlQuery query;
    query.prepare("UPDATE clients SET NOM = :nom, PRENOM = :prenom, EMAIL = :email, TELEPHONE = :telephone, "
                  "ADRESSE = :adresse, SEXE = :sexe, ID_PROJET = :id_projet WHERE ID_CLIENT = :id");
    query.bindValue(":id", id);
    query.bindValue(":nom", nom);
    query.bindValue(":prenom", prenom);
    query.bindValue(":email", email);
    query.bindValue(":telephone", telephone);
    query.bindValue(":adresse", adresse);
    query.bindValue(":sexe", sexe);
    query.bindValue(":id_projet", id_projet);

    return query.exec();
}

// 🔹 Supprimer un client
bool Clients::supprimer(int id) {
    QSqlQuery query;
    query.prepare("DELETE FROM clients WHERE ID_CLIENT = :id");
    query.bindValue(":id", id);

    return query.exec();
}

// 🔹 Getters et Setters
int Clients::getId() const { return id_client; }
void Clients::setId(int id) { this->id_client = id; }

QString Clients::getNom() const { return nom; }
void Clients::setNom(const QString &nom) { this->nom = nom; }

QString Clients::getPrenom() const { return prenom; }
void Clients::setPrenom(const QString &prenom) { this->prenom = prenom; }

QString Clients::getEmail() const { return email; }
void Clients::setEmail(const QString &email) { this->email = email; }

QString Clients::getTelephone() const { return telephone; }
void Clients::setTelephone(const QString &telephone) { this->telephone = telephone; }

QString Clients::getAdresse() const { return adresse; }
void Clients::setAdresse(const QString &adresse) { this->adresse = adresse; }

QString Clients::getSexe() const { return sexe; }
void Clients::setSexe(const QString &sexe) { this->sexe = sexe; }

int Clients::getIdProjet() const { return id_projet; }
void Clients::setIdProjet(int id_projet) { this->id_projet = id_projet; }
