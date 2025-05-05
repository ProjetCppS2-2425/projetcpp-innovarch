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

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr, const QString &userRole = "");
    ~MainWindow();

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
    void on_chercher_2_clicked();
    void on_refresh_3_clicked();
};

#endif // MAINWINDOW_H
