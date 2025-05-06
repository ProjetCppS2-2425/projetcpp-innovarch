#ifndef GESTIONRESSOURCES_H
#define GESTIONRESSOURCES_H

#include <QString>
#include <QDate>
#include <QSqlQueryModel>
#include <QSortFilterProxyModel>
#include <QtCharts/QChartView>
#include <QtCharts/QPieSeries>
#include <QTableView>

class GestionRessources
{
private:
    int id_ressource;
    int quantite;
    int fournisseur;
    double prix;
    QString nom;
    QString categorie;
    QString etat;
    QDate date_achat;
    QDate date_entretien;
public:
    GestionRessources();
    GestionRessources(int id, int quantite, int fournisseur, double prix, QString nom, QString categorie, QString etat, QDate date_achat, QDate date_entretien);
    bool ajouterRessource(QString nom, int quantite, QString categorie, int fournisseur, QDate date_achat, QString etat, double prix, QDate date_entretien);
    void supprimerRessource(int id);
    void afficher(QSortFilterProxyModel* proxyModel, QTableView* tableView);
    QSqlQueryModel* afficher();
    void rechercheRessource(const QString& searchText, const QString& searchCriteria, QSqlQueryModel* model);
    bool updateRessource(int id, const QString& nom, int quantite, const QString& categorie, int fournisseur, const QDate& dateAchat, const QString& etat, double prix, const QDate& dateEntretien);
    // Utility Methods
    QPixmap genererGraph();
    QPieSeries* stat();
    void load(int id, QString& nom, int& quantite, QString& categorie, int& fournisseur, QDate& dateAchat, QString& etat, double& prix, QDate& dateEntretien);
    QList<QPair<QString, QString>> checkAlerts(); // replaces signal-based alert system
    // Fixed resource (ID 9) operations
    bool decrementScannerQuantity();
    QString getScannerName();
    int getScannerQuantity();
    bool updateScannerQuantity(int newQuantity);
};

#endif // GESTIONRESSOURCES_H
