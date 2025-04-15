#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTableWidget>
#include <QtCharts/QChartView>
#include <QtCharts/QPieSeries>
#include <QtCharts/QPieSlice>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QChart>
#include <QSqlQueryModel>
#include <QSortFilterProxyModel>
#include "gestionressources.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_ajouter_clicked();
    void on_annuler_clicked();
    void on_modifier_clicked();
    void on_chercher_clicked();
    void on_triButton_clicked();
    void on_exportPdf_clicked();
    void on_statpb_clicked();
    void on_triCb_currentIndexChanged();
    void on_refresh_clicked();
    void on_bellIcon_clicked();

private:
    Ui::MainWindow *ui;
    QSortFilterProxyModel *proxyModel;  // Proxy model for sorting and filtering
    bool isAscending = true;            // Sorting order toggle
    int m_currentResourceId = 0;        // Current selected resource ID
    int alertCount = 0;
    int popupOffset = 0;
    bool historyVisible = false;
    QWidget* historyWidget = nullptr;
    const int popupSpacing = 70;
    GestionRessources gestionRessources ; // Instance of GestionRessources
    void fillTab();                     // Populate the QTableView
    void clearFields();
    void handleIconClick(const QModelIndex &index);
    void handleAlertNotification(const QString &message, const QString &type);
    QStringList alertHistory; // stores alerts globally
    void showAllAlerts();     // function to show the popup
    QWidget* alertHistoryWidget = nullptr;
    void updateBellCount();

private slots:
    void onClearAlertsClicked();

};

#endif // MAINWINDOW_H
