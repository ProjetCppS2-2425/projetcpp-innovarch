#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "contracteur.h"
#include "arduino.h"
#include <QMainWindow>
#include <QTableWidget>
#include <QPdfWriter>
#include <QPainter>
#include <QModelIndex>
#include <QStandardItemModel>

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
    void on_tabWidgetcontracteur_currentChanged(int index);
    void on_contractorlisttablecontracteur_clicked(const QModelIndex &index);
    void on_assignCardcontracteur_clicked();
    void on_togglePresencecontracteur_clicked();
    void on_pushButton_6contracteur_clicked(); // Slot for the "Contracteurs" button

private:
    Ui::MainWindow *ui;
    Contracteur currentContracteur;
    Arduino arduino; // Arduino instance
    QString lastScannedCardId; // Add this to store the last scanned card ID

    void refreshTableWidget();
    void fillTableWidget();
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
};

#endif // MAINWINDOW_H