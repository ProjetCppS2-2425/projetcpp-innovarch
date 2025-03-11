#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->ajouter, &QPushButton::clicked, this, &MainWindow::on_ajouter_clicked);
    connect(ui->modifier, &QPushButton::clicked, this, &MainWindow::on_modifier_clicked);
    connect(ui->supprimer, &QPushButton::clicked, this, &MainWindow::on_supprimer_clicked);
    connect(ui->pushButton, &QPushButton::clicked, this, &MainWindow::on_refreshButton_clicked);
    // Removed incorrect connect statement
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_ajouter_clicked()
{
    Contracteur c(0, ui->lineEdit_2->text(), ui->lineEdit_13->text(), ui->lineEdit_7->text(), "", "", "", "", ""); // Removed incorrect method
    if (c.ajouter()) {
        QMessageBox::information(this, "Success", "Contracteur added successfully.");
        on_refreshButton_clicked(); // Refresh the table view
    } else {
        QMessageBox::critical(this, "Error", "Failed to add contracteur.");
    }
}

void MainWindow::on_modifier_clicked()
{
    int id = ui->lineEdit_3->text().toInt();
    currentContracteur = Contracteur(id, ui->lineEdit_2->text(), ui->lineEdit_13->text(), ui->lineEdit_7->text(), "", "", "", "", ""); // Removed incorrect method
    if (currentContracteur.modifier(id)) {
        QMessageBox::information(this, "Success", "Contracteur modified successfully.");
        on_refreshButton_clicked(); // Refresh the table view
    } else {
        QMessageBox::critical(this, "Error", "Failed to modify contracteur.");
    }
}

void MainWindow::on_supprimer_clicked()
{
    int id = ui->lineEdit_3->text().toInt();
    if (currentContracteur.supprimer(id)) {
        QMessageBox::information(this, "Success", "Contracteur deleted successfully.");
        on_refreshButton_clicked(); // Refresh the table view
    } else {
        QMessageBox::critical(this, "Error", "Failed to delete contracteur.");
    }
}

void MainWindow::on_refreshButton_clicked()
{
    QSqlQueryModel *model = currentContracteur.afficher();
    ui->tableView_2->setModel(model);
}

void MainWindow::on_tableView_tri_2_currentIndexChanged(int index)
{
    QString sortColumn;
    switch (index) {
        case 1:
            sortColumn = "ID_contracteur DESC";
            break;
        case 2:
            sortColumn = "ID_contracteur ASC";
            break;
        case 3:
            sortColumn = "Date_ajout";
            break;
        case 4:
            sortColumn = "Type_projets";
            break;
        case 5:
            sortColumn = "Categorie";
            break;
        default:
            sortColumn = "ID_contracteur";
            break;
    }

    QSqlQueryModel *model = new QSqlQueryModel();
    model->setQuery("SELECT * FROM contracteurs ORDER BY " + sortColumn);
    ui->tableView_2->setModel(model);
}