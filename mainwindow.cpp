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

void MainWindow::refreshTableWidget() {
    fillTableWidget();
}

void MainWindow::on_addProjectButton_clicked() {
    QString nom = ui->lineEdit_7->text();
    QString type = ui->comboBox->currentText();
    double budget = ui->lineEdit_5->text().toDouble();
    QString echeance = ui->dateEdit_2->date().toString("yyyy-MM-dd");
    QString statut = ui->comboBox_2->currentText();

    // Input validation
    if (nom.isEmpty() || type.isEmpty() || budget <= 0 || echeance.isEmpty() || statut.isEmpty()) {
        QMessageBox::warning(this, "Input Error", "Please fill in all fields correctly.");
        return;
    }

    qDebug() << "Adding project with values:" << nom << type << budget << echeance << statut;

    currentProject = ProjetCRUD(0, nom, type, budget, echeance, statut, 0, 0);
    if (currentProject.ajouter()) {
        QMessageBox::information(this, "Success", "Projet ajouté avec succès.");
        fillTableWidget();
    } else {
        QMessageBox::warning(this, "Error", "Échec de l'ajout du projet.");
    }
}

void MainWindow::on_modifyProjectButton_clicked() {
    int id = ui->id_rech_2->text().toInt();
    QString nom = ui->lineEdit_7->text();
    QString type = ui->comboBox->currentText();
    double budget = ui->lineEdit_5->text().toDouble();
    QString echeance = ui->dateEdit_2->date().toString("yyyy-MM-dd");
    QString statut = ui->comboBox_2->currentText();
    int id_architecte = ui->lineEdit_2->text().toInt();
    int id_contracteur = ui->lineEdit_3->text().toInt();

    // Input validation
    if (nom.isEmpty() || type.isEmpty() || budget <= 0 || echeance.isEmpty() || statut.isEmpty()) {
        QMessageBox::warning(this, "Input Error", "Please fill in all fields correctly.");
        return;
    }

    currentProject = ProjetCRUD(id, nom, type, budget, echeance, statut, id_architecte, id_contracteur);
    if (currentProject.modifier(id)) {
        QMessageBox::information(this, "Success", "Projet modifié avec succès.");
        fillTableWidget();
    } else {
        QMessageBox::warning(this, "Failure", "Échec de la modification du projet.");
    }
}

void MainWindow::on_deleteProjectButton_clicked() {
    int id = ui->id_rech_2->text().toInt();
    if (currentProject.supprimer(id)) {
        QMessageBox::information(this, "Success", "Projet supprimé avec succès.");
        fillTableWidget();
    } else {
        QMessageBox::warning(this, "Error", "Échec de la suppression du projet.");
    }
}

void MainWindow::on_tableView_itemClicked(const QModelIndex &index) {
    int row = index.row();

    ui->id_rech_2->setText(ui->tableView->model()->data(ui->tableView->model()->index(row, 0)).toString());
    ui->lineEdit_7->setText(ui->tableView->model()->data(ui->tableView->model()->index(row, 1)).toString());
    ui->comboBox->setCurrentText(ui->tableView->model()->data(ui->tableView->model()->index(row, 2)).toString());
    ui->lineEdit_5->setText(ui->tableView->model()->data(ui->tableView->model()->index(row, 3)).toString());
    ui->dateEdit->setDate(QDate::fromString(ui->tableView->model()->data(ui->tableView->model()->index(row, 4)).toString(), "yyyy-MM-dd"));
    ui->dateEdit_2->setDate(QDate::fromString(ui->tableView->model()->data(ui->tableView->model()->index(row, 5)).toString(), "yyyy-MM-dd"));
    ui->comboBox_2->setCurrentText(ui->tableView->model()->data(ui->tableView->model()->index(row, 6)).toString());
    ui->lineEdit_2->setText(ui->tableView->model()->data(ui->tableView->model()->index(row, 7)).toString());
    ui->lineEdit_3->setText(ui->tableView->model()->data(ui->tableView->model()->index(row, 8)).toString());
}

void MainWindow::on_cancelButton_clicked() {
    ui->lineEdit_7->clear();
    ui->comboBox->setCurrentIndex(0);
    ui->lineEdit_5->clear();
    ui->dateEdit->clear();
    ui->dateEdit_2->clear();
    ui->comboBox_2->setCurrentIndex(0);
    ui->lineEdit_2->clear();
    ui->lineEdit_3->clear();
}
