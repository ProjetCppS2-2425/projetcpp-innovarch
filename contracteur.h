#ifndef CONTRACTEUR_H
#define CONTRACTEUR_H

#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QDate>
#include <QSqlError>

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
    QString historique;
    QString avisclients;

public:
    Contracteur();
    Contracteur(int, QString, QString, QString, QString, QString, QString, QString, QString);

    // Getters
    int getIdContracteur() { return id_contracteur; }
    QString getNom() { return nom; }
    QString getPrenom() { return prenom; }
    QString getTelephone() { return telephone; }
    QString getAdresse() { return adresse; }
    QString getEmail() { return email; }
    QString getDomaine() { return domaine; }
    QString getHistorique() { return historique; }
    QString getAvisClients() { return avisclients; }

    // Setters
    void setIdContracteur(int id) { id_contracteur = id; }
    void setNom(QString n) { nom = n; }
    void setPrenom(QString p) { prenom = p; }
    void setTelephone(QString t) { telephone = t; }
    void setAdresse(QString a) { adresse = a; }
    void setEmail(QString e) { email = e; }
    void setDomaine(QString d) { domaine = d; }
    void setHistorique(QString h) { historique = h; }
    void setAvisClients(QString ac) { avisclients = ac; }

    // Methods
    bool ajouter();
    QSqlQueryModel *afficher();
    bool modifier(int id);
    bool supprimer(int id);
    QSqlError getLastError() const;
};

#endif // CONTRACTEUR_H
