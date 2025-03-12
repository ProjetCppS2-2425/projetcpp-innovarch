#include "projetcrud.h"
#include <QDebug>

// Constructeurs
ProjetCRUD::ProjetCRUD() {}

ProjetCRUD::ProjetCRUD(int id, QString nom, QString description, double budget, QString date_debut, QString date_fin) {
    this->id_projet = id;
    this->nom = nom;
    this->description = description;
    this->budget = budget;
    this->date_debut = date_debut;
    this->date_fin = date_fin;
}

// Ajouter un projet
bool ProjetCRUD::ajouter() {
    QSqlQuery query;
    query.prepare("INSERT INTO projets (ID_PROJET, NOM, DESCRIPTION, BUDGET, DATE_DEBUT, DATE_FIN) "
                  "VALUES (:id, :nom, :description, :budget, :date_debut, :date_fin)");
    query.bindValue(":id", id_projet);
    query.bindValue(":nom", nom);
    query.bindValue(":description", description);
    query.bindValue(":budget", budget);
    query.bindValue(":date_debut", date_debut);
    query.bindValue(":date_fin", date_fin);

    return query.exec();
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
    query.prepare("UPDATE projets SET NOM = :nom, DESCRIPTION = :description, BUDGET = :budget, "
                  "DATE_DEBUT = :date_debut, DATE_FIN = :date_fin WHERE ID_PROJET = :id");
    query.bindValue(":id", id);
    query.bindValue(":nom", nom);
    query.bindValue(":description", description);
    query.bindValue(":budget", budget);
    query.bindValue(":date_debut", date_debut);
    query.bindValue(":date_fin", date_fin);

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

QString ProjetCRUD::getDescription() const { return description; }
void ProjetCRUD::setDescription(const QString &description) { this->description = description; }

double ProjetCRUD::getBudget() const { return budget; }
void ProjetCRUD::setBudget(double budget) { this->budget = budget; }

QString ProjetCRUD::getDateDebut() const { return date_debut; }
void ProjetCRUD::setDateDebut(const QString &date) { this->date_debut = date; }

QString ProjetCRUD::getDateFin() const { return date_fin; }
void ProjetCRUD::setDateFin(const QString &date) { this->date_fin = date; }
