#include "projetcrud.h"
#include <QDebug>
#include <QSqlError>

// Constructeurs
ProjetCRUD::ProjetCRUD() {}

ProjetCRUD::ProjetCRUD(int id, QString nom, QString type, double budget, QString echeance, QString statut, int id_architecte, int id_contracteur) {
    this->id_projet = id;
    this->nom = nom;
    this->type = type;
    this->budget = budget;
    this->echeance = echeance;
    this->statut = statut;
    this->id_architecte = id_architecte;
    this->id_contracteur = id_contracteur;
}

// Ajouter un projet
bool ProjetCRUD::ajouter() {
    QSqlQuery query;
    query.exec("SELECT MAX(ID_PROJET) FROM projets");
    int new_id = 1;
    if (query.next()) {
        new_id = query.value(0).toInt() + 1;
    }

    query.prepare("INSERT INTO projets (ID_PROJET, NOM_PROJET, TYPE_PROJET, BUDGET, ECHEANCE, STATUT) "
                  "VALUES (:id, :nom, :type, :budget, TO_DATE(:echeance, 'YYYY-MM-DD'), :statut)");
    query.bindValue(":id", new_id);
    query.bindValue(":nom", nom);
    query.bindValue(":type", type);
    query.bindValue(":budget", budget);
    query.bindValue(":echeance", echeance);
    query.bindValue(":statut", statut);

    if (!query.exec()) {
        qDebug() << "Error adding project:" << query.lastError().text();
        return false;
    }
    return true;
}

// Afficher les projets
QSqlQueryModel * ProjetCRUD::afficher() {
    QSqlQueryModel * model = new QSqlQueryModel();
    model->setQuery("SELECT * FROM projets");
    return model;
}

// Modifier un projet
bool ProjetCRUD::modifier(int id) {
    QSqlQuery query;
    query.prepare("UPDATE projets SET NOM_PROJET = :nom, TYPE_PROJET = :type, BUDGET = :budget, "
                  "ECHEANCE = TO_DATE(:echeance, 'YYYY-MM-DD'), STATUT = :statut WHERE ID_PROJET = :id");
    query.bindValue(":id", id);
    query.bindValue(":nom", nom);
    query.bindValue(":type", type);
    query.bindValue(":budget", budget);
    query.bindValue(":echeance", echeance);
    query.bindValue(":statut", statut);

    return query.exec();
}

// Supprimer un projet
bool ProjetCRUD::supprimer(int id) {
    QSqlQuery query;
    query.prepare("DELETE FROM projets WHERE ID_PROJET = :id");
    query.bindValue(":id", id);

    return query.exec();
}

// Getters et Setters
int ProjetCRUD::getId() const { return id_projet; }
void ProjetCRUD::setId(int id) { this->id_projet = id; }

QString ProjetCRUD::getNom() const { return nom; }
void ProjetCRUD::setNom(const QString &nom) { this->nom = nom; }

QString ProjetCRUD::getType() const { return type; }
void ProjetCRUD::setType(const QString &type) { this->type = type; }

double ProjetCRUD::getBudget() const { return budget; }
void ProjetCRUD::setBudget(double budget) { this->budget = budget; }

QString ProjetCRUD::getEcheance() const { return echeance; }
void ProjetCRUD::setEcheance(const QString &date) { this->echeance = date; }

QString ProjetCRUD::getStatut() const { return statut; }
void ProjetCRUD::setStatut(const QString &statut) { this->statut = statut; }

int ProjetCRUD::getIdArchitecte() const { return id_architecte; }
void ProjetCRUD::setIdArchitecte(int id) { this->id_architecte = id; }

int ProjetCRUD::getIdContracteur() const { return id_contracteur; }
void ProjetCRUD::setIdContracteur(int id) { this->id_contracteur = id; }
