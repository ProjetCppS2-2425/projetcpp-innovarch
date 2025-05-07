#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSqlQueryModel>
#include "contrats.h"
#include "arduino.h"
#include <QTimer>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void populateTableWidget(QSqlQueryModel* model);


private slots:
    void on_ajouter_clicked();
    void afficherContrats();
    void on_modifier_clicked();
    void on_supprimer_clicked();
    void on_tributton_clicked();
    void on_chercher_clicked();
    void on_stats_clicked();
    void on_pushButton_email_clicked();
    void on_exporter_clicked();
    void handleKeypadInput();

    void on_tableWidget_cellClicked(int row, int column);




private:
    Ui::MainWindow *ui;
<<<<<<< Updated upstream
    contrats currentContrat;
    Arduino A;
    QTimer *timer;
      // Timer pour lecture série
    QString buffer;
=======

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
    void on_pushButton_contrats_clicked();
>>>>>>> Stashed changes
};

#endif // MAINWINDOW_H
