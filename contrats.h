#ifndef CONTRATS_H
#define CONTRATS_H

#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QMap>

class contrats
{
public:
    contrats();
    contrats(int id, double montant, QString dateDebut, QString dateFin, QString statut, int idProjet, int idClient);

    // CRUD Methods
    bool ajouter();
    QSqlQueryModel* afficher();
    bool supprimer(int id);
    bool modifier(int id);

    // Search and Sorting
    QSqlQueryModel* rechercher(const QString &critere);
    QSqlQueryModel* trier(const QString &critere, const QString &ordre);

    // Statistics
    QMap<QString, int> statistiques();

private:
    int id;
    double montantTotal;
    QString dateDebut;
    QString dateFin;
    QString statutPaiement;
    int idProjet;
    int idClient;
};

#endif // CONTRATS_H
