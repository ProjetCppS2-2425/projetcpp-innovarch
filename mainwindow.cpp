#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QSqlError>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->tableView, &QTableView::clicked, this, &MainWindow::on_tableView_itemClicked);
    connect(ui->ajouter, &QPushButton::clicked, this, &MainWindow::on_addProjectButton_clicked);
    connect(ui->annuler, &QPushButton::clicked, this, &MainWindow::on_cancelButton_clicked);
    connect(ui->supprimer, &QPushButton::clicked, this, &MainWindow::on_deleteProjectButton_clicked);
    connect(ui->modifier, &QPushButton::clicked, this, &MainWindow::on_modifyProjectButton_clicked);

    fillTableWidget();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::fillTableWidget() {
    QSqlQueryModel *model = currentProject.afficher();
    if (model) {
        ui->tableView->setModel(model);
        ui->tableView->resizeColumnsToContents();
    }
}

void MainWindow::on_addProjectButton_clicked() {
    QString nom = ui->lineEdit_nom->text();
    QString description = ui->lineEdit_description->text();
    double budget = ui->lineEdit_budget->text().toDouble();
    QString date_debut = ui->lineEdit_dateDebut->text();
    QString date_fin = ui->lineEdit_dateFin->text();

    QSqlQuery query;
    query.exec("SELECT MAX(ID_PROJET) FROM projets");
    int id_projet = 1;
    if (query.next()) {
        id_projet = query.value(0).toInt() + 1;
    }

    currentProject = ProjetCRUD(id_projet, nom, description, budget, date_debut, date_fin);
    if (currentProject.ajouter()) {
        QMessageBox::information(this, "Success", "Projet ajouté avec succès.");
        fillTableWidget();
    } else {
        QMessageBox::warning(this, "Error", "Échec de l'ajout du projet.");
    }
}

void MainWindow::on_modifyProjectButton_clicked() {
    int id = ui->id_rech->text().toInt();
    QString nom = ui->lineEdit_nom->text();
    QString description = ui->lineEdit_description->text();
    double budget = ui->lineEdit_budget->text().toDouble();
    QString date_debut = ui->lineEdit_dateDebut->text();
    QString date_fin = ui->lineEdit_dateFin->text();

    currentProject = ProjetCRUD(id, nom, description, budget, date_debut, date_fin);
    if (currentProject.modifier(id)) {
        QMessageBox::information(this, "Success", "Projet modifié avec succès.");
        fillTableWidget();
    } else {
        QMessageBox::warning(this, "Failure", "Échec de la modification du projet.");
    }
}

void MainWindow::on_deleteProjectButton_clicked() {
    int id = ui->id_rech->text().toInt();
    if (currentProject.supprimer(id)) {
        QMessageBox::information(this, "Success", "Projet supprimé avec succès.");
        fillTableWidget();
    } else {
        QMessageBox::warning(this, "Error", "Échec de la suppression du projet.");
    }
}

void MainWindow::on_tableView_itemClicked(const QModelIndex &index) {
    int row = index.row();

    ui->id_rech->setText(ui->tableView->model()->data(ui->tableView->model()->index(row, 0)).toString());
    ui->lineEdit_nom->setText(ui->tableView->model()->data(ui->tableView->model()->index(row, 1)).toString());
    ui->lineEdit_description->setText(ui->tableView->model()->data(ui->tableView->model()->index(row, 2)).toString());
    ui->lineEdit_budget->setText(ui->tableView->model()->data(ui->tableView->model()->index(row, 3)).toString());
    ui->lineEdit_dateDebut->setText(ui->tableView->model()->data(ui->tableView->model()->index(row, 4)).toString());
    ui->lineEdit_dateFin->setText(ui->tableView->model()->data(ui->tableView->model()->index(row, 5)).toString());
}

void MainWindow::on_cancelButton_clicked() {
    ui->lineEdit_nom->clear();
    ui->lineEdit_description->clear();
    ui->lineEdit_budget->clear();
    ui->lineEdit_dateDebut->clear();
    ui->lineEdit_dateFin->clear();
}
