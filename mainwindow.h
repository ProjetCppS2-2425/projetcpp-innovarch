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
    void on_addContracteurButton_clicked();
    void on_supprimerContracteur_clicked();
    void on_modifyContracteurButton_clicked();
    void on_annulerButton_clicked();
    void on_tableView_2_itemClicked(const QModelIndex &index);
    void on_comboBox_tri_2_currentIndexChanged(int index);
    void on_chercher_2_clicked();
    void on_pdf_2_clicked();
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