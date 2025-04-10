#ifndef CONTRACTEUR_H
#define CONTRACTEUR_H

#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QSqlError>
#include <QString>

class Contracteur
{
private:
    int id_contracteur;
    QString nom;
    QString prenom;
    QString telephone;
    QString adresse;
    QString email;
    QString domaine;

public:
    Contracteur();
    Contracteur(int, QString, QString, QString, QString, QString, QString);

    // Getters
    int getIdContracteur() const;
    QString getNom() const;
    QString getPrenom() const;
    QString getTelephone() const;
    QString getAdresse() const;
    QString getEmail() const;
    QString getDomaine() const;

    // Setters
    void setIdContracteur(int id);
    void setNom(const QString &n);
    void setPrenom(const QString &p);
    void setTelephone(const QString &t);
    void setAdresse(const QString &a);
    void setEmail(const QString &e);
    void setDomaine(const QString &d);

    // Methods
    bool ajouter();
    QSqlQueryModel *afficher();
    bool modifier(int id);
    bool supprimer(int id);
    void reassignIds();
    QSqlError getLastError() const;
};

#endif // CONTRACTEUR_H
