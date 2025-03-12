#ifndef GESTIONRESSOURCES_H
#define GESTIONRESSOURCES_H
#include <QMainWindow>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QMessageBox>
#include <QFileDialog>
#include <QPdfWriter>
#include <QPainter>
#include <QDate>
#include <QSortFilterProxyModel>
#include "ui_GestionRessources.h"
class GestionRessources : public QMainWindow
{
    Q_OBJECT
public:
    explicit GestionRessources(QWidget *parent = nullptr);
    ~GestionRessources();
private slots:
    void ajouterRessource();
    void annulerAjout ();
    void supprimerRessource(int id);
    void rechercheRessource();
    void trierRessources();
    //void exporterPDF();
    void handleTableClick(const QModelIndex &index);
    void updateRessource();
private:
    Ui::GestionRessources *ui;
    void afficherRessources();
    bool isAscending = true;
    QSortFilterProxyModel *proxyModel;
    int m_currentResourceId = 0;
    void load(int id);
    bool validateComboBoxes();
    bool validateDateFields();
    bool validateNumFields();
    bool validateTextFields();
};
#endif // GESTIONRESSOURCES_H
