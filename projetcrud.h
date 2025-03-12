#ifndef PROJETCRUD_H
#define PROJETCRUD_H

#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>

class ProjetCRUD
{
public:
    // Constructeurs
    ProjetCRUD();
    ProjetCRUD(int id, QString nom, QString description, double budget, QString date_debut, QString date_fin);

    // CRUD
    bool ajouter();
    bool modifier(int id);
    bool supprimer(int id);
    QSqlQueryModel *afficher();

    // Getters et setters
    int getId() const;
    void setId(int id);
    QString getNom() const;
    void setNom(const QString &nom);
    QString getDescription() const;
    void setDescription(const QString &description);
    double getBudget() const;
    void setBudget(double budget);
    QString getDateDebut() const;
    void setDateDebut(const QString &date);
    QString getDateFin() const;
    void setDateFin(const QString &date);

private:
    int id_projet;
    QString nom;
    QString description;
    double budget;
    QString date_debut;
    QString date_fin;
};

#endif // PROJETCRUD_H
