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
    QSqlQueryModel *trier(QString critere);
    QSqlQueryModel* rechercher(int id);
    QMap<QString, int> statistiquesStatut();



    bool supprimer(int id);
    bool modifier(int id);

    // Search and Sorting


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
