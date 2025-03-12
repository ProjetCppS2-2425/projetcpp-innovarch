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
    connect(ui->ajouter, &QPushButton::clicked, this, &MainWindow::on_addClientButton_clicked);
    connect(ui->annuler, &QPushButton::clicked, this, &MainWindow::on_annulerButton_clicked);
    connect(ui->supprimer, &QPushButton::clicked, this, &MainWindow::on_supprimerClient_clicked);
    connect(ui->modifier, &QPushButton::clicked, this, &MainWindow::on_modifyClientButton_clicked);

    qDebug() << "Calling fillTableWidget() at startup";
    fillTableWidget();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::fillTableWidget() {
    qDebug() << "Executing fillTableWidget()";
    QSqlQueryModel *model = currentClient.afficher();

    if (model) {
        ui->tableView->setModel(model);
        ui->tableView->resizeColumnsToContents();
        qDebug() << "Table widget filled successfully";
    } else {
        qDebug() << "Failed to fill table widget";
    }
}

void MainWindow::on_addClientButton_clicked()
{
    if (ui->lineEdit_2->text().isEmpty()) {
        QMessageBox::warning(this, "Input Error", "Nom vide !!");
        return;
    }

    if (ui->lineEdit_4->text().isEmpty()) {
        QMessageBox::warning(this, "Input Error", "Prénom vide !!");
        return;
    }

    QString email = ui->lineEdit_6->text();
    if (email.isEmpty()) {
        QMessageBox::warning(this, "Input Error", "Email vide !!");
        return;
    }

    QSqlQuery query;
    query.exec("SELECT MAX(ID_CLIENT) FROM clients");
    int id_client = 1;
    if (query.next()) {
        id_client = query.value(0).toInt() + 1;
    }

    QString nom = ui->lineEdit_2->text();
    QString prenom = ui->lineEdit_4->text();
    QString telephone = ui->lineEdit_7->text();
    QString adresse = ui->lineEdit_5->text();
    QString sexe = ui->comboBox->currentText();

    qDebug() << "Adding Client with details:";
    qDebug() << "ID:" << id_client;
    qDebug() << "Nom:" << nom;
    qDebug() << "Prénom:" << prenom;
    qDebug() << "Email:" << email;
    qDebug() << "Telephone:" << telephone;
    qDebug() << "Adresse:" << adresse;
    qDebug() << "Sexe:" << sexe;

    currentClient = Clients(id_client, nom, prenom, email, telephone, adresse, sexe);

    if (currentClient.ajouter()) {
        QMessageBox::information(this, "Success", "Client ajouté avec succès.");
        fillTableWidget();

        ui->lineEdit_2->clear();
        ui->lineEdit_4->clear();
        ui->lineEdit_6->clear();
        ui->lineEdit_7->clear();
        ui->lineEdit_5->clear();
        ui->comboBox->setCurrentIndex(0);
    } else {
        QMessageBox::warning(this, "Error", "Échec de l'ajout du client.");
    }
}

void MainWindow::on_supprimerClient_clicked() {
    int id = ui->id_rech_2->text().toInt();

    if (id == 0) {
        QMessageBox::warning(this, "Input Error", "L'ID pour supprimer est vide.");
        return;
    }

    if (currentClient.supprimer(id)) {
        QMessageBox::information(this, "Success", "Client supprimé avec succès.");
        fillTableWidget();

        ui->id_rech_2->clear();
        ui->lineEdit_2->clear();
        ui->lineEdit_4->clear();
        ui->lineEdit_6->clear();
        ui->lineEdit_7->clear();
        ui->lineEdit_5->clear();
        ui->comboBox->setCurrentIndex(0);
    } else {
        QMessageBox::warning(this, "Error", "Échec de la suppression du client.");
    }
}

void MainWindow::on_modifyClientButton_clicked()
{
    int id = ui->id_rech_2->text().toInt();
    if (id == 0) {
        QMessageBox::warning(this, "Input Error", "L'ID pour modifier est vide.");
        return;
    }

    QString nom = ui->lineEdit_2->text();
    QString prenom = ui->lineEdit_4->text();
    QString email = ui->lineEdit_6->text();
    QString telephone = ui->lineEdit_7->text();
    QString adresse = ui->lineEdit_5->text();
    QString sexe = ui->comboBox->currentText();

    currentClient = Clients(id, nom, prenom, email, telephone, adresse, sexe);

    if (currentClient.modifier(id)) {
        QMessageBox::information(this, "Success", "Client modifié avec succès.");
        fillTableWidget();

        ui->id_rech_2->clear();
        ui->lineEdit_2->clear();
        ui->lineEdit_4->clear();
        ui->lineEdit_6->clear();
        ui->lineEdit_7->clear();
        ui->lineEdit_5->clear();
        ui->comboBox->setCurrentIndex(0);
    } else {
        QMessageBox::warning(this, "Failure", "Échec de la modification du client.");
    }
}

void MainWindow::on_tableView_itemClicked(const QModelIndex &index)
{
    int row = index.row();

    QString id = ui->tableView->model()->data(ui->tableView->model()->index(row, 0)).toString();
    QString nom = ui->tableView->model()->data(ui->tableView->model()->index(row, 1)).toString();
    QString prenom = ui->tableView->model()->data(ui->tableView->model()->index(row, 2)).toString();
    QString email = ui->tableView->model()->data(ui->tableView->model()->index(row, 3)).toString();
    QString telephone = ui->tableView->model()->data(ui->tableView->model()->index(row, 4)).toString();
    QString adresse = ui->tableView->model()->data(ui->tableView->model()->index(row, 5)).toString();
    QString sexe = ui->tableView->model()->data(ui->tableView->model()->index(row, 6)).toString();

    ui->id_rech_2->setText(id);
    ui->lineEdit_2->setText(nom);
    ui->lineEdit_4->setText(prenom);
    ui->lineEdit_6->setText(email);
    ui->lineEdit_7->setText(telephone);
    ui->lineEdit_5->setText(adresse);
    ui->comboBox->setCurrentText(sexe);
}

void MainWindow::refreshTableWidget() {
    QSqlQueryModel *model = currentClient.afficher();

    ui->tableView->setModel(model);
    ui->tableView->resizeColumnsToContents();
}

void MainWindow::on_annulerButton_clicked() {
    ui->lineEdit_2->clear();
    ui->lineEdit_4->clear();
    ui->lineEdit_6->clear();
    ui->lineEdit_7->clear();
    ui->lineEdit_5->clear();
    ui->comboBox->setCurrentIndex(0);
}
