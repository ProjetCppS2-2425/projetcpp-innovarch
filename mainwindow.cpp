#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "contrats.h"
#include <QMessageBox>
#include <QPdfWriter>
#include <QPainter>
#include <QChart>
#include <QPieSeries>
#include <QChartView>
#include <QSqlDatabase>
#include <QSqlError>

void MainWindow::populateTableWidget(QSqlQueryModel* model) {
    ui->tableWidget->setRowCount(model->rowCount());
    ui->tableWidget->setColumnCount(model->columnCount());
    ui->tableWidget->setHorizontalHeaderLabels({
        "ID Contrat", "Montant Total", "Date Début", "Date Fin", "Statut Paiement", "ID Projet", "ID Client"
    });

    for (int row = 0; row < model->rowCount(); ++row) {
        for (int col = 0; col < model->columnCount(); ++col) {
            QTableWidgetItem* item = new QTableWidgetItem(model->data(model->index(row, col)).toString());
            ui->tableWidget->setItem(row, col, item);
        }
    }
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Correct signal-slot connections
    connect(ui->annuler, &QPushButton::clicked, this, &MainWindow::on_supprimer_clicked);
    connect(ui->chercher_2, &QPushButton::clicked, this, &MainWindow::on_rechercher_clicked);
    connect(ui->comboBox_tri_3, &QComboBox::currentIndexChanged, this, &MainWindow::on_trier_clicked);
    connect(ui->pdf_3, &QPushButton::clicked, this, &MainWindow::on_exporter_pdf_clicked); // Updated to pdf_3
    connect(ui->chercher_2, &QPushButton::clicked, this, &MainWindow::on_statistiques_clicked);

    if (!QSqlDatabase::database().isOpen()) {
        QMessageBox::critical(this, "Database Error", "Database is not open: " + QSqlDatabase::database().lastError().text());
    }
    populateTableWidget(currentContrat.afficher());
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_ajouter_clicked() {
    if (!QSqlDatabase::database().isOpen()) {
        QMessageBox::critical(this, "Database Error", "Database is not open.");
        return;
    }

    contrats c(ui->id->text().toInt(), ui->montant->text().toDouble(), 
               ui->date_debut->date().toString("yyyy-MM-dd"), 
               ui->date_fin->date().toString("yyyy-MM-dd"), 
               ui->status_2->currentText(), ui->iclient_2->text().toInt(), ui->iclient->text().toInt());
    if (c.ajouter()) {
        QMessageBox::information(this, "Success", "Contrat ajouté avec succès.");
        populateTableWidget(currentContrat.afficher());
    } else {
        QMessageBox::critical(this, "Error", "Erreur lors de l'ajout du contrat.");
    }
}

void MainWindow::on_modifier_clicked() {
    if (!QSqlDatabase::database().isOpen()) {
        QMessageBox::critical(this, "Database Error", "Database is not open.");
        return;
    }

    contrats c(ui->id->text().toInt(), ui->montant->text().toDouble(), 
               ui->date_debut->date().toString("yyyy-MM-dd"), 
               ui->date_fin->date().toString("yyyy-MM-dd"), 
               ui->status_2->currentText(), ui->iclient_2->text().toInt(), ui->iclient->text().toInt());
    if (c.modifier(ui->id->text().toInt())) {
        QMessageBox::information(this, "Success", "Contrat modifié avec succès.");
        populateTableWidget(currentContrat.afficher());
    } else {
        QMessageBox::critical(this, "Error", "Erreur lors de la modification du contrat.");
    }
}

void MainWindow::on_supprimer_clicked() {
    int id = ui->id->text().toInt();
    if (currentContrat.supprimer(id)) {
        QMessageBox::information(this, "Success", "Contrat supprimé avec succès.");
        populateTableWidget(currentContrat.afficher());
    } else {
        QMessageBox::critical(this, "Error", "Erreur lors de la suppression du contrat.");
    }
}

void MainWindow::on_rechercher_clicked() {
    QString critere = ui->id_rech->text();
    populateTableWidget(currentContrat.rechercher(critere));
}

void MainWindow::on_trier_clicked() {
    QString critere = ui->comboBox_tri_3->currentText();
    QString ordre = "ASC"; // Default order
    if (critere.contains("décroissant")) ordre = "DESC";
    populateTableWidget(currentContrat.trier("MONTANT_TOTAL", ordre));
}

void MainWindow::on_exporter_pdf_clicked() {
    QPdfWriter pdf("contrats.pdf");
    QPainter painter(&pdf);
    painter.drawText(100, 100, "Liste des Contrats");
    // Add more drawing logic here
    painter.end();
    QMessageBox::information(this, "PDF Export", "PDF exporté avec succès.");
}

void MainWindow::on_statistiques_clicked() {
    QMap<QString, int> stats = currentContrat.statistiques();
    QPieSeries *series = new QPieSeries();
    for (auto it = stats.begin(); it != stats.end(); ++it) {
        series->append(it.key(), it.value());
    }
    QChart *chart = new QChart();
    chart->addSeries(series);
    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    chartView->show();
}
