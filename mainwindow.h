#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "clients.h"
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

    void on_addClientButton_clicked();
    void on_supprimerClient_clicked();
    void on_modifyClientButton_clicked();
    void on_annulerButton_clicked();
    void on_pushButtonRecherche_clicked();
    void on_trierClientButton_clicked();
    void on_pdfClientButton_clicked();
    void on_statButton_clicked();



private slots:
    void on_tableView_itemClicked(const QModelIndex &index);


private:
    Ui::MainWindow *ui;
    Clients currentClient;
    void on_tableWidget_itemClicked(QTableWidgetItem *item);
    void refreshTableWidget();
    void fillTableWidget();
};

#endif // MAINWINDOW_H
