#ifndef CONTRACTEUR_H
#define CONTRACTEUR_H

#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>

class Contracteur {
private:
    int id;
    QString nom;
    QString prenom;
    QString telephone;
    QString adresse;
    QString email;
    QString domaine;
    QString historique;
    QString avisClients;

public:
    Contracteur();
    Contracteur(int, QString, QString, QString, QString, QString, QString, QString, QString);

    bool ajouter();
    QSqlQueryModel* afficher();
    bool modifier(int);
    bool supprimer(int);
};

#endif // CONTRACTEUR_H
