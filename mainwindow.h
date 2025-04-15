#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "contracteur.h"
#include <QMainWindow>
#include <QTableWidget>
#include <QPdfWriter>
#include <QPainter>
#include <QModelIndex>

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

private:
    Ui::MainWindow *ui;
    Contracteur currentContracteur;

    void refreshTableWidget();
    void fillTableWidget();
    void generateStatistics();
    void exportStatisticsPDF();
};

#endif // MAINWINDOW_H