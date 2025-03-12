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

    fillTableWidget();
    connect(ui->tableView_2, &QTableView::clicked, this, &MainWindow::on_tableView_2_itemClicked);

    connect(ui->ajouter, &QPushButton::clicked, this, &MainWindow::on_addContracteurButton_clicked);
    connect(ui->annuler, &QPushButton::clicked, this, &MainWindow::on_annulerButton_clicked);
    connect(ui->supprimer, &QPushButton::clicked, this, &MainWindow::on_supprimerContracteur_clicked);
    connect(ui->modifier, &QPushButton::clicked, this, &MainWindow::on_modifyContracteurButton_clicked);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::fillTableWidget() {
    QSqlQueryModel *model = currentContracteur.afficher();

    ui->tableView_2->setModel(model);
    ui->tableView_2->resizeColumnsToContents();
}

void MainWindow::on_addContracteurButton_clicked()
{
    if (ui->lineEdit_2->text().isEmpty()) {
        QMessageBox::warning(this, "Input Error", "Nom vide !!");
        return;
    }

    if (ui->lineEdit_13->text().isEmpty()) {
        QMessageBox::warning(this, "Input Error", "Prenom vide !!");
        return;
    }

    QString telephone = ui->lineEdit_7->text();
    if (telephone.isEmpty()) {
        QMessageBox::warning(this, "Input Error", "Telephone vide !!");
        return;
    }

    // Fetch the maximum ID from the database and increment it by one
    QSqlQuery query;
    query.exec("SELECT MAX(id_contracteur) FROM contracteurs");
    int id_contracteur = 1;
    if (query.next()) {
        id_contracteur = query.value(0).toInt() + 1;
    }

    QString nom = ui->lineEdit_2->text();
    QString prenom = ui->lineEdit_13->text();
    QString adresse = ui->lineEdit_3->text();
    QString email = ""; // Assuming this is not provided in the UI
    QString domaine = ui->comboBox->currentText();
    QString historique = ""; // Assuming this is not provided in the UI
    QString avisclients = ""; // Assuming this is not provided in the UI

    qDebug() << "Adding Contracteur with details:";
    qDebug() << "ID:" << id_contracteur;
    qDebug() << "Nom:" << nom;
    qDebug() << "Prenom:" << prenom;
    qDebug() << "Adresse:" << adresse;
    qDebug() << "Telephone:" << telephone;
    qDebug() << "Email:" << email;
    qDebug() << "Domaine:" << domaine;
    qDebug() << "Historique:" << historique;
    qDebug() << "AvisClients:" << avisclients;

    currentContracteur.setIdContracteur(id_contracteur);
    currentContracteur.setNom(nom);
    currentContracteur.setPrenom(prenom);
    currentContracteur.setTelephone(telephone);
    currentContracteur.setAdresse(adresse);
    currentContracteur.setEmail(email);
    currentContracteur.setDomaine(domaine);
    currentContracteur.setHistorique(historique);
    currentContracteur.setAvisClients(avisclients);

    if (currentContracteur.ajouter()) {
        QMessageBox::information(this, "Success", "Contracteur ajouté avec succès.");
        fillTableWidget();

        ui->lineEdit_2->clear();
        ui->lineEdit_13->clear();
        ui->lineEdit_3->clear();
        ui->lineEdit_7->clear();
        ui->comboBox->setCurrentIndex(0);
    } else {
        QMessageBox::warning(this, "Error", "Échec de l'ajout du contracteur.");
        qDebug() << "Error adding Contracteur:" << currentContracteur.getLastError().text();
    }
}

void MainWindow::on_supprimerContracteur_clicked() {
    int id = ui->id_rech_2->text().toInt();

    if (id == 0) {
        QMessageBox::warning(this, "Input Error", "L'ID pour supprimer est vide.");
        return;
    }

    if (currentContracteur.supprimer(id)) {
        QMessageBox::information(this, "Success", "Contracteur supprimé avec succès.");
        fillTableWidget();

        ui->id_rech_2->clear();
        ui->lineEdit_2->clear();
        ui->lineEdit_13->clear();
        ui->lineEdit_3->clear();
        ui->lineEdit_7->clear();
        ui->comboBox->setCurrentIndex(0);
    } else {
        QMessageBox::warning(this, "Error", "Échec de la suppression du contracteur.");
    }
}

void MainWindow::on_modifyContracteurButton_clicked()
{
    int id = ui->id_rech_2->text().toInt();
    if (id == 0) {
        QMessageBox::warning(this, "Input Error", "L'ID pour modifier est vide.");
        return;
    }

    QString nom = ui->lineEdit_2->text();
    QString prenom = ui->lineEdit_13->text();
    QString telephone = ui->lineEdit_7->text();
    QString adresse = ui->lineEdit_3->text();
    QString email = ""; // Assuming this is not provided in the UI
    QString domaine = ui->comboBox->currentText();
    QString historique = ""; // Assuming this is not provided in the UI
    QString avisclients = ""; // Assuming this is not provided in the UI

    currentContracteur.setNom(nom);
    currentContracteur.setPrenom(prenom);
    currentContracteur.setTelephone(telephone);
    currentContracteur.setAdresse(adresse);
    currentContracteur.setEmail(email);
    currentContracteur.setDomaine(domaine);
    currentContracteur.setHistorique(historique);
    currentContracteur.setAvisClients(avisclients);

    if (currentContracteur.modifier(id)) {
        QMessageBox::information(this, "Success", "Information du contracteur modifiée avec succès.");
        fillTableWidget();

        ui->id_rech_2->clear();
        ui->lineEdit_2->clear();
        ui->lineEdit_13->clear();
        ui->lineEdit_3->clear();
        ui->lineEdit_7->clear();
        ui->comboBox->setCurrentIndex(0);
    } else {
        QMessageBox::warning(this, "Failure", "Échec de la modification des informations du contracteur.");
    }
}

void MainWindow::on_tableView_2_itemClicked(const QModelIndex &index)
{
    int row = index.row();

    QString id = ui->tableView_2->model()->data(ui->tableView_2->model()->index(row, 0)).toString();
    QString nom = ui->tableView_2->model()->data(ui->tableView_2->model()->index(row, 1)).toString();
    QString prenom = ui->tableView_2->model()->data(ui->tableView_2->model()->index(row, 2)).toString();
    QString telephone = ui->tableView_2->model()->data(ui->tableView_2->model()->index(row, 3)).toString();
    QString adresse = ui->tableView_2->model()->data(ui->tableView_2->model()->index(row, 4)).toString();
    QString email = ui->tableView_2->model()->data(ui->tableView_2->model()->index(row, 5)).toString();
    QString domaine = ui->tableView_2->model()->data(ui->tableView_2->model()->index(row, 6)).toString();
    QString historique = ui->tableView_2->model()->data(ui->tableView_2->model()->index(row, 7)).toString();
    QString avisclients = ui->tableView_2->model()->data(ui->tableView_2->model()->index(row, 8)).toString();

    ui->id_rech_2->setText(id);
    ui->lineEdit_2->setText(nom);
    ui->lineEdit_13->setText(prenom);
    ui->lineEdit_7->setText(telephone);
    ui->lineEdit_3->setText(adresse);
    ui->comboBox->setCurrentText(domaine);
}

void MainWindow::refreshTableWidget() {
    QSqlQueryModel *model = currentContracteur.afficher();

    ui->tableView_2->setModel(model);
    ui->tableView_2->resizeColumnsToContents();
}

void MainWindow::on_annulerButton_clicked() {
    ui->lineEdit_2->clear();
    ui->lineEdit_13->clear();
    ui->lineEdit_3->clear();
    ui->lineEdit_7->clear();
    ui->comboBox->setCurrentIndex(0);
}