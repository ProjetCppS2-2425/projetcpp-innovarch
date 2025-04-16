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
    ProjetCRUD(int id, QString nom, QString type, double budget, QString echeance, QString statut, int id_architecte, int id_contracteur);

    // CRUD
    bool ajouter();
    bool modifier(int id);
    bool supprimer(int id);
    QSqlQueryModel *afficher();
    QSqlQueryModel *trier(const QString &critere, const QString &ordre);
    QSqlQueryModel *rechercher(const QString &keyword);
    QSqlQueryModel *rechercherAvance(const QString &colonne, const QString &valeur);
    QSqlQueryModel *rechercherParCritere(const QString &colonne, const QString &valeur);
    bool exporterPDF(const QString &filePath);
    bool importerPDF(const QString &filePath); // Déclaration de la méthode importerPDF

    // Getters et setters
    int getId() const;
    void setId(int id);
    QString getNom() const;
    void setNom(const QString &nom);
    QString getType() const;
    void setType(const QString &type);
    double getBudget() const;
    void setBudget(double budget);
    QString getEcheance() const;
    void setEcheance(const QString &date);
    QString getStatut() const;
    void setStatut(const QString &statut);
    int getIdArchitecte() const;
    void setIdArchitecte(int id);
    int getIdContracteur() const;
    void setIdContracteur(int id);

private:
    int id_projet;
    QString nom;
    QString type;
    double budget;
    QString echeance;
    QString statut;
    int id_architecte;
    int id_contracteur;
};

#endif // PROJETCRUD_H
