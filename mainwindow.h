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
#include "projetcrud.h"
// Project-specific includes
#include "dialog.h"
#include "architechtes.h"
#include "gestionressources.h"
#include "arduino.h"
//#include "arduinocontracteur.h"
#include "rec.h"
#include "clients.h"
#include "arduinocl.h"
#include "contracteur.h"
#include "contrats.h"
#include "arduinocontrat.h"
#include <QNetworkAccessManager>  // For API calls
#include <QNetworkReply>          // Handle API responses
#include <QJsonDocument>          // Parse JSON from OpenAI
#include <QJsonObject>            // Construct JSON payloads
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr, const QString &userRole = "");
    ~MainWindow();
    ////selim////
    void on_addClientButton_clicked();
    void on_supprimerClient_clicked();
    void on_modifyClientButton_clicked();
    void on_annulerButton_clicked();
    void on_pushButtonRecherche_clicked();
    void on_trierClientButton_clicked();
    void on_pdfClientButton_clicked();
    void on_statButton1_clicked();
    void on_btnEnvoyerSMS_clicked();
    /////contrat////
    void populateTableWidget(QSqlQueryModel* model);



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

    // Ahmed
    ProjetCRUD currentProject;
    void fillTableWidgetAh();
    void on_statButton_clicked();
    void on_importPDFButton_clicked();
    void on_advancedSearchButton_clicked();
    void on_searchByCriteriaButton_clicked();
    QString getResponse(const QString &question); // Added missing declaration
    QNetworkAccessManager *networkManager; // For API requests
    const QString chatbotApiUrl = "https://generativelanguage.googleapis.com/v1/models/gemini-1.5-pro:generateContent";
    const QString chatbotApiKey = "AIzaSyAOoQot44v63-w_UejM2QGNQIan_Eoa6AI";
    void sendChatbotRequest(const QString &userMessage); // Send user input to API

    // clients
    Clients currentClient;
    //void on_tableWidget_itemClicked(QTableWidgetItem *item);
    void refreshTableWidget1();
    void fillTableWidget1();
    ArduinoCL A;
    void updatePresence(QString id);
    bool isUpdatingPresence;


    //contracteur


    void refreshTableWidget2();
    void fillTableWidget2();
    void generateStatistics();
    void exportStatisticsPDF();
    void loadContractorsToTable(QTableView *tableView);
    void loadArchitectsToListView();
    void updatePresenceView();
    void assignCardToArchitect(int architectId, const QString &cardId);
    void togglePresence(int architectId, bool isPresent);

    // Add missing declarations
    void readArduinoData();
    void loadTasksForContractor(int contractorId);
    void populateTreeView(int contractorId);
    void clearTreeView();
    void updateTaskStatus(int contractorId, const QString &task, const QString &status);
    Contracteur currentContracteur; // Fix undeclared variable error
    QString lastScannedCardId;      // Fix undeclared variable error
    ArduinoCL ArdCont;
    QTimer *arduinoTimer;
    //// contrat/////

    contrats currentContrat;
    Arduinocontrat AB;
    QTimer *timer;
        // Timer pour lecture série
    QString buffer;


private slots:
    // ==== Architecte Slots ====
    void on_addEmployeeButton_clicked();
    void on_supprimerEmploye_clicked();
    void on_modifyEmployeeButton_clicked();
    void on_refreshButton_clicked();
    void on_refreshButton2_clicked();
    void on_pdf_2_clicked();
    void on_rechercherButton_clicked();
    void on_comboBox_tri_3_currentIndexChanged(int index);
    void on_triCb_currentIndexChanged(int index);
    void on_triCb_2_currentIndexChanged(int index);

    void on_triButton_2_clicked();
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
    void on_chercher_2_clicked();
    void on_refresh_3_clicked();
    void handleEmployeeCellClicked(int row, int column);

    // Ahmed Slots

    void on_pushButton_ASK_clicked();
    void displayProjectStats();  // Pour afficher les statistiques
    void on_addProjectButton_clicked();
    void on_modifyProjectButton_clicked();
    void on_deleteProjectButton_clicked();
    void on_tableView_itemClicked(const QModelIndex &index);
    void refreshTableWidgetAh();
    void on_cancelButton_clicked();
    void on_sortButton_clicked();
    void on_searchButton_clicked();
    void on_exportPDFButton_clicked();
    void on_showStatsButton_clicked();
    void on_stat1_2_clicked();
    void handleChatbotResponse(); // Handle API responses
    void on_pushButton_proj_clicked();
    void on_pushButton_3_clicked();
    void on_pushButton_8_clicked();
    void on_pushButton_11_clicked();


    void on_pushButton_9_clicked();
    void on_pushButton_21_clicked();
    void on_pushButton_cl_3_clicked();
    void on_pushButton_contrats_3_clicked();
    void on_pushButton_ct_3_clicked();
    void on_pushButton_proj_3_clicked();
    void on_pushButton_r_3_clicked();
    void on_pushButton_cl_clicked();
    void on_pushButton_4_clicked();
    void on_pushButton_13_clicked();
    void on_pushButton_6_clicked();
    void on_pushButton_ct_clicked();
    void on_pushButton_24_clicked();
    void on_pushButton_cl_6_clicked();
    void on_pushButton_contrats_6_clicked();
    void on_pushButton_ct_6_clicked();
    void on_pushButton_proj_6_clicked();
    void on_pushButton_r_6_clicked();

    void on_pushButton_contrats_clicked();
    void on_pushButton_5_clicked();
    void on_pushButton_12_clicked();
    void on_pushButton_25_clicked();
    void on_pushButton_cl_7_clicked();
    void on_pushButton_contrats_7_clicked();
    void on_pushButton_ct_7_clicked();
    void on_pushButton_proj_7_clicked();
    void on_pushButton_r_7_clicked();










    void on_tableView_itemClicked1(const QModelIndex &index);
    void on_pushButton_openDoor_clicked();


    // slots contracteurs


    void on_addContracteurButtoncontracteur_clicked();
    void on_supprimerContracteurcontracteur_clicked();
    void on_modifyContracteurButtoncontracteur_clicked();
    void on_annulerButtoncontracteur_clicked();
    void on_tableView_2contracteur_itemClicked(const QModelIndex &index);
    void on_comboBox_tri_2contracteur_currentIndexChanged(int index);
    void on_chercher_2contracteur_clicked();
    void on_pdf_2contracteur_clicked();
    void on_generateStatisticsButtoncontracteur_clicked();
    void on_exportStatisticsPDFButtoncontracteur_clicked();
    void on_addtaskcontracteur_clicked();
    void on_completedtaskcontracteur_clicked();
    void on_rmtaskcontracteur_clicked();
    void on_testaffichertodocontracteur_clicked();
    void on_affichertreecontracteur_clicked();
    //void on_tabWidgetcontracteur_currentChanged(int index);
    void on_contractorlisttablecontracteur_clicked(const QModelIndex &index);
    //void on_assignCardcontracteur_clicked();
    //void on_togglePresencecontracteur_clicked();
    void on_pushButton_6contracteur_clicked();


    ///////contrat slots//////////////


    void on_ajoutercontrat_clicked();
    void afficherContrats();
    void on_modifiercontrat_clicked();
    void on_supprimercontrat_clicked();
    void on_tributtoncontrat_clicked();
    void on_cherchercontrat_clicked();
    void on_statscontrat_clicked();
    void on_pushButton_email_clicked();
    void on_exportercontrat_clicked();
    void handleKeypadInput();

    void on_tableWidgetcontrat_cellClicked(int row, int column);


};

#endif // MAINWINDOW_H
