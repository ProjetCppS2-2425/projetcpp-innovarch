#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QSqlError>
#include <QDebug>
#include <QFileDialog>
#include <QPdfWriter>
#include <QPainter>
#include <QRegularExpression>

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
    connect(ui->comboBox_tri_2, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &MainWindow::on_comboBox_tri_2_currentIndexChanged);
    connect(ui->chercher_2, &QPushButton::clicked, this, &MainWindow::on_chercher_2_clicked);
    connect(ui->pdf_2, &QPushButton::clicked, this, &MainWindow::on_pdf_2_clicked);
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
    // Input validation
    if (ui->lineEdit_2->text().isEmpty()) {
        QMessageBox::warning(this, "Input Error", "Nom est vide !");
        return;
    }

    if (ui->lineEdit_13->text().isEmpty()) {
        QMessageBox::warning(this, "Input Error", "Prenom est vide !");
        return;
    }

    QString telephone = ui->lineEdit_7->text();
    if (telephone.isEmpty()) {
        QMessageBox::warning(this, "Input Error", "Telephone est vide !");
        return;
    }
    if (!QRegularExpression("^[0-9]{8}$").match(telephone).hasMatch()) {
        QMessageBox::warning(this, "Input Error", "Le numéro de téléphone doit contenir exactement 8 chiffres !");
        return;
    }

    QString adresse = ui->lineEdit_4->text(); // Correct field for address
    if (adresse.isEmpty()) {
        QMessageBox::warning(this, "Input Error", "Adresse est vide !");
        return;
    }

    QString email = ui->lineEdit_5->text(); // Correct field for email
    if (email.isEmpty()) {
        QMessageBox::warning(this, "Input Error", "Email est vide !");
        return;
    }
    if (!QRegularExpression("^[\\w.-]+@[\\w.-]+\\.[a-zA-Z]{2,}$").match(email).hasMatch()) {
        QMessageBox::warning(this, "Input Error", "L'email doit être au format something@something.something !");
        return;
    }

    if (ui->comboBox->currentText() == "Domaine") {
        QMessageBox::warning(this, "Input Error", "Veuillez sélectionner un domaine valide !");
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
    QString domaine = ui->comboBox->currentText();

    currentContracteur.setIdContracteur(id_contracteur);
    currentContracteur.setNom(nom);
    currentContracteur.setPrenom(prenom);
    currentContracteur.setTelephone(telephone);
    currentContracteur.setAdresse(adresse);
    currentContracteur.setEmail(email);
    currentContracteur.setDomaine(domaine);

    if (currentContracteur.ajouter()) {
        QMessageBox::information(this, "Success", "Contracteur ajouté avec succès.");
        fillTableWidget();

        // Clear input fields
        ui->lineEdit_2->clear();
        ui->lineEdit_13->clear();
        ui->lineEdit_7->clear();
        ui->lineEdit_4->clear();
        ui->lineEdit_5->clear();
        ui->comboBox->setCurrentIndex(0);
    } else {
        QMessageBox::warning(this, "Error", "Échec de l'ajout du contracteur.");
    }
}

void MainWindow::on_supprimerContracteur_clicked() {
    int id = ui->lineEdit_3->text().toInt(); // Read the ID from the actual ID field

    if (id == 0) {
        QMessageBox::warning(this, "Input Error", "L'ID pour supprimer est vide.");
        return;
    }

    if (currentContracteur.supprimer(id)) {
        currentContracteur.reassignIds(); // Reassign IDs after deletion
        QMessageBox::information(this, "Success", "Contracteur supprimé avec succès.");
        fillTableWidget();

        // Clear input fields
        ui->lineEdit_3->clear();
        ui->lineEdit_2->clear();
        ui->lineEdit_13->clear();
        ui->lineEdit_7->clear();
        ui->lineEdit_4->clear();
        ui->lineEdit_5->clear();
        ui->comboBox->setCurrentIndex(0);
    } else {
        QMessageBox::warning(this, "Error", "Échec de la suppression du contracteur.");
    }
}

void MainWindow::on_modifyContracteurButton_clicked()
{
    int id = ui->lineEdit_3->text().toInt(); // Use the actual ID field
    if (id == 0) {
        QMessageBox::warning(this, "Input Error", "L'ID pour modifier est vide.");
        return;
    }

    // Input validation
    if (ui->lineEdit_2->text().isEmpty()) {
        QMessageBox::warning(this, "Input Error", "Nom est vide !");
        return;
    }

    if (ui->lineEdit_13->text().isEmpty()) {
        QMessageBox::warning(this, "Input Error", "Prenom est vide !");
        return;
    }

    QString telephone = ui->lineEdit_7->text();
    if (telephone.isEmpty()) {
        QMessageBox::warning(this, "Input Error", "Telephone est vide !");
        return;
    }
    if (!QRegularExpression("^[0-9]{8}$").match(telephone).hasMatch()) {
        QMessageBox::warning(this, "Input Error", "Le numéro de téléphone doit contenir exactement 8 chiffres !");
        return;
    }

    QString adresse = ui->lineEdit_4->text(); // Correct field for address
    if (adresse.isEmpty()) {
        QMessageBox::warning(this, "Input Error", "Adresse est vide !");
        return;
    }

    QString email = ui->lineEdit_5->text(); // Correct field for email
    if (email.isEmpty()) {
        QMessageBox::warning(this, "Input Error", "Email est vide !");
        return;
    }
    if (!QRegularExpression("^[\\w.-]+@[\\w.-]+\\.[a-zA-Z]{2,}$").match(email).hasMatch()) {
        QMessageBox::warning(this, "Input Error", "L'email doit être au format something@something.something !");
        return;
    }

    if (ui->comboBox->currentText() == "Domaine") {
        QMessageBox::warning(this, "Input Error", "Veuillez sélectionner un domaine valide !");
        return;
    }

    QString nom = ui->lineEdit_2->text();
    QString prenom = ui->lineEdit_13->text();
    QString domaine = ui->comboBox->currentText();

    currentContracteur.setNom(nom);
    currentContracteur.setPrenom(prenom);
    currentContracteur.setTelephone(telephone);
    currentContracteur.setAdresse(adresse);
    currentContracteur.setEmail(email);
    currentContracteur.setDomaine(domaine);

    if (currentContracteur.modifier(id)) {
        QMessageBox::information(this, "Success", "Information du contracteur modifiée avec succès.");
        fillTableWidget();

        // Clear input fields
        ui->lineEdit_3->clear();
        ui->lineEdit_2->clear();
        ui->lineEdit_13->clear();
        ui->lineEdit_7->clear();
        ui->lineEdit_4->clear();
        ui->lineEdit_5->clear();
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

    // Populate the correct fields
    ui->lineEdit_3->setText(id); // ID field
    ui->lineEdit_2->setText(nom);
    ui->lineEdit_13->setText(prenom);
    ui->lineEdit_7->setText(telephone);
    ui->lineEdit_4->setText(adresse); // Correct field for address
    ui->lineEdit_5->setText(email);   // Correct field for email
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

void MainWindow::on_comboBox_tri_2_currentIndexChanged(int index) {
    QString queryStr;
    switch (index) {
        case 1: // Id décroissant
            queryStr = "SELECT * FROM contracteurs ORDER BY id_contracteur DESC";
            break;
        case 2: // Id croissant
            queryStr = "SELECT * FROM contracteurs ORDER BY id_contracteur ASC";
            break;
        case 3: // Date d'ajout
            queryStr = "SELECT * FROM contracteurs ORDER BY date_ajout"; // Assuming a `date_ajout` column exists
            break;
        case 4: // Type des projets
            queryStr = "SELECT * FROM contracteurs ORDER BY domaine";
            break;
        case 5: // Catégorie
            queryStr = "SELECT * FROM contracteurs ORDER BY categorie"; // Assuming a `categorie` column exists
            break;
        default:
            queryStr = "SELECT * FROM contracteurs";
            break;
    }

    QSqlQueryModel *model = new QSqlQueryModel();
    model->setQuery(queryStr);
    ui->tableView_2->setModel(model);
    ui->tableView_2->resizeColumnsToContents();
}

void MainWindow::on_chercher_2_clicked() {
    QString searchText = ui->id_rech_2->text();
    QString queryStr;

    if (searchText.toInt() > 0) {
        queryStr = QString("SELECT * FROM contracteurs WHERE id_contracteur = %1").arg(searchText.toInt());
    } else {
        queryStr = QString("SELECT * FROM contracteurs WHERE nom LIKE '%%1%' OR prenom LIKE '%%1%' OR telephone LIKE '%%1%'").arg(searchText);
    }

    QSqlQueryModel *model = new QSqlQueryModel();
    model->setQuery(queryStr);
    ui->tableView_2->setModel(model);
    ui->tableView_2->resizeColumnsToContents();
}

void MainWindow::on_pdf_2_clicked() {
    QString filePath = QFileDialog::getSaveFileName(this, "Save PDF", "", "*.pdf");
    if (filePath.isEmpty()) {
        return;
    }

    QPdfWriter pdfWriter(filePath);
    pdfWriter.setPageSize(QPageSize(QPageSize::A4));
    pdfWriter.setResolution(300); // Set high resolution for better quality
    QPainter painter(&pdfWriter);

    int margin = 50; // Margin for the PDF
    int y = margin;
    int lineHeight = 30; // Height between rows
    int columnWidth = 100; // Width for each column

    // Set font for the title
    painter.setFont(QFont("Arial", 16, QFont::Bold));
    painter.drawText(margin, y, "Liste des Contracteurs");

    // Move to the next line
    y += lineHeight * 2;

    // Set font for the table headers
    painter.setFont(QFont("Arial", 12, QFont::Bold));
    painter.drawText(margin, y, "ID");
    painter.drawText(margin + columnWidth, y, "Nom");
    painter.drawText(margin + 2 * columnWidth, y, "Prenom");
    painter.drawText(margin + 3 * columnWidth, y, "Telephone");
    painter.drawText(margin + 4 * columnWidth, y, "Adresse");
    painter.drawText(margin + 5 * columnWidth, y, "Domaine");

    // Draw a line under the headers
    y += lineHeight;
    painter.drawLine(margin, y, margin + 6 * columnWidth, y);

    // Set font for the table content
    painter.setFont(QFont("Arial", 10));

    // Fetch data from the database
    QSqlQuery query("SELECT id_contracteur, nom, prenom, telephone, adresse, domaine FROM contracteurs");
    while (query.next()) {
        y += lineHeight;

        // Check if the content exceeds the page height
        if (y > pdfWriter.height() - margin) {
            pdfWriter.newPage(); // Create a new page
            y = margin + lineHeight; // Reset y position
        }

        // Write data to the PDF
        painter.drawText(margin, y, query.value(0).toString());
        painter.drawText(margin + columnWidth, y, query.value(1).toString());
        painter.drawText(margin + 2 * columnWidth, y, query.value(2).toString());
        painter.drawText(margin + 3 * columnWidth, y, query.value(3).toString());
        painter.drawText(margin + 4 * columnWidth, y, query.value(4).toString());
        painter.drawText(margin + 5 * columnWidth, y, query.value(5).toString());
    }

    painter.end();
    QMessageBox::information(this, "Exportation PDF", "PDF exporté avec succès.");
}