#ifndef CLIENTS_H
#define CLIENTS_H

#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>

class Clients
{
public:
    // Constructeurs
    Clients();
    Clients(int id, QString nom, QString prenom, QString email, QString telephone = "", QString adresse = "", QString sexe = "");

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
    QString getPrenom() const;
    void setPrenom(const QString &prenom);
    QString getEmail() const;
    void setEmail(const QString &email);
    QString getTelephone() const;
    void setTelephone(const QString &telephone);
    QString getAdresse() const;
    void setAdresse(const QString &adresse);
    QString getSexe() const;
    void setSexe(const QString &sexe);

private:
    int id_client;
    QString nom;
    QString prenom;
    QString email;
    QString telephone;
    QString adresse;
    QString sexe;
};

#endif // CLIENTS_H
