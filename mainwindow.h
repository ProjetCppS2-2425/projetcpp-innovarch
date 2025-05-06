#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTableWidget>
#include <QSortFilterProxyModel>
#include <QtCharts/QChartView>
#include <QtCharts/QPieSeries>
#include <QtCharts/QPieSlice>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QChart>
#include <QSqlQueryModel>
#include <QItemSelection>
#include <QGraphicsItem>

// Project-specific includes
#include "dialog.h"
#include "architechtes.h"
#include "gestionressources.h"
#include "arduino.h"
#include "rec.h"
#include "clients.h"
#include "contracteur.h"
#include "arduinocontracteur.h"
#include "arduinocl.h"
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr, const QString &userRole = "");
    ~MainWindow();
    void on_addClientButton_clicked();
    void on_supprimerClient_clicked();
    void on_modifyClientButton_clicked();
    void on_pushButtonRecherche_clicked();
    void on_trierClientButton_clicked();
    void on_pdfClientButton_clicked();
    void on_statButton_clicked();
    void on_btnEnvoyerSMS_clicked();

private:
    Ui::MainWindow *ui;

    // ==== Architecte Module ====
    Architecte emp;
    Architecte architecte;
    QString m_userRole;
    QSqlQueryModel* currentCongeModel;

    void setupTabsBasedOnRole();
    void fillTableWidget();
    void refreshTableWidget();
    void populateEmployeeInfo();
    void refreshCongeTableViewOnDateClick(const QDate &date);
    bool customTableWidgetItemCompare(QTableWidgetItem* item1, QTableWidgetItem* item2);
    void displayCongeStatistics();
    void refreshTableView();
    void handleRecommendationClick(int row);


    // ==== Ressource Module ====
    GestionRessources gestionRessources;
    Arduino *arduino;
    QSortFilterProxyModel *proxyModel;
    QStringList alertHistory;
    QWidget* alertHistoryWidget = nullptr;
    QWidget* historyWidget = nullptr;

    int m_currentResourceId = 0;
    int alertCount = 0;
    int popupOffset = 0;
    const int popupSpacing = 70;
    bool historyVisible = false;

    void fillTab();
    void clearFields();
    void handleIconClick(const QModelIndex &index);
    void handleAlertNotification(const QString &message, const QString &type);
    void showAllAlerts();
    void updateBellCount();
    void populateLowStockTable();
    void showProductCards(const QList<Product>& products, const QString& title);
    void handlePersonalizedRecommendation();

    bool isAscending = true; // Shared between modules

    // clients
    Clients currentClient;
    void refreshTableWidget1();
    void fillTableWidget1();
    ArduinoCL A;
    void updatePresence(QString id);
    bool isUpdatingPresence;

private slots:
    // ==== Architecte Slots ====
    void on_addEmployeeButton_clicked();
    void on_supprimerEmploye_clicked();
    void on_modifyEmployeeButton_clicked();
    void on_refreshButton_clicked();
    void on_refreshButton2_clicked();
    void on_rechercherButton_clicked();
    void on_comboBox_tri_3_currentIndexChanged(int index);
    void on_triCb_currentIndexChanged(int index);
    void on_triCb_2_currentIndexChanged(int index);

    void on_triButton_2_clicked();
    void on_tableWidget_itemClicked(QTableWidgetItem *item);
    void on_tableWidget_sortIndicatorChanged(int logicalIndex, Qt::SortOrder order);
    void on_soumettreButton_clicked();
    void onSelectionChanged(const QItemSelection &selected, const QItemSelection &deselected);
    void on_acceptation_clicked();
    void on_refuser_clicked();
    void on_statConge_clicked();
    void onCalendarDateClicked(const QDate &date);
    void onRowSelected();
    void onLoginClicked();

    // ==== Ressource Slots ====
    void on_ajouter_clicked();
    void on_annuler_clicked();
    void on_modifier_clicked();
    void on_chercher_clicked();
    void on_exportPdf_clicked();
    void on_statpb_clicked();
    void on_refresh_clicked();
    void on_bellIcon_clicked();
    void onClearAlertsClicked();
    void handleDecrement();
    void on_triButton_clicked();

    void on_voirlesStatistiques_clicked();
    void on_commandLinkButton_clicked();
    void on_pushButton_clicked();
    void on_pushButton_r_clicked();
    void on_ajouter_2_clicked();
    void on_modifier_2_clicked();
    void on_refresh_2_clicked();
    void on_annuler_2_clicked();
    void on_accepter_conge_clicked();
    void on_refuser_conge_clicked();
    void on_refresh_4_clicked();
    void on_statpb_2_clicked();
    void on_soumettre_clicked();
    void on_refresh_5_clicked();
    void on_refresh_3_clicked();

    void on_pushButton_cl_clicked();
    void on_tableView_itemClicked(const QModelIndex &index);
    void on_pushButton_openDoor_clicked();

    //Module Contracteur

    void on_addContracteurButton_clicked();
    void on_supprimerContracteur_clicked();
    void on_modifyContracteurButton_clicked();
    void on_tableView_2_itemClicked(const QModelIndex &index);
    void on_comboBox_tri_2_currentIndexChanged(int index);
    void on_generateStatisticsButton_clicked();
    void on_exportStatisticsPDFButton_clicked();
    void on_addtask_clicked();
    void on_completedtask_clicked();
    void on_rmtask_clicked();
    void on_testaffichertodo_clicked();
    void on_affichertree_clicked();
    void on_tabWidget_currentChanged(int index);
    void on_contractorlisttable_clicked(const QModelIndex &index);
    void on_assignCard_clicked();
    void on_togglePresence_clicked();
    void on_pushButton_6_clicked(); // Slot for the "Contracteurs" button

};

#endif // MAINWINDOW_H
