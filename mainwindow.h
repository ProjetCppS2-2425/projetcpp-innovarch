#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "contracteur.h"
#include <QMainWindow>
#include <QTableWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void on_addContracteurButton_clicked();
    void on_supprimerContracteur_clicked();
    void on_modifyContracteurButton_clicked();
    void on_annulerButton_clicked();

private slots:
    void on_tableView_2_itemClicked(const QModelIndex &index);

private:
    Ui::MainWindow *ui;
    Contracteur currentContracteur;
    void on_tableWidget_itemClicked(QTableWidgetItem *item);
    void refreshTableWidget();
    void fillTableWidget();
};

#endif // MAINWINDOW_H