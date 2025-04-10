#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QSqlError>
#include <QDebug>
#include <QString>
#include <QFileDialog>
#include <QPdfWriter>
#include <QPainter>
#include <QRegularExpression>
#include <QtCharts/QChartView>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QBarCategoryAxis>
#include <QtCharts/QValueAxis>
#include <QRandomGenerator>
#include <QtCharts/QPieSeries>
#include <QtCharts/QPieSlice>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsProxyWidget>
#include <QtCharts/QLegendMarker>
#include <QtCharts/QChart>

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

    // Add a header for the new column
    model->setHeaderData(7, Qt::Horizontal, QObject::tr("Date d'Ajout"));
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

    QString domaine = ui->comboBox->currentText();
    if (domaine == "Categorie") { // Prevent "Categorie" from being accepted
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
    QDateTime currentDateTime = QDateTime::currentDateTime();
    QString dateAjout = currentDateTime.toString("yyyy-MM-dd HH:mm:ss");

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
    ui->lineEdit_4->clear(); // Clear Adresse
    ui->lineEdit_5->clear(); // Clear Email
    ui->comboBox->setCurrentIndex(0);
}

void MainWindow::on_comboBox_tri_2_currentIndexChanged(int index) {
    // Clear the current model to avoid residual data
    ui->tableView_2->setModel(nullptr);

    QSqlQueryModel *model = new QSqlQueryModel();
    QString queryStr;

    // Map combo box index to sorting criteria
    switch (index) {
        case 1: // Sort by Date d'ajout
            queryStr = "SELECT * FROM contracteurs ORDER BY dateajout ASC";
            break;
        case 2: // Sort by Domaine
            queryStr = "SELECT * FROM contracteurs ORDER BY LOWER(domaine) ASC";
            break;
        case 3: // Sort by Id décroissant
            queryStr = "SELECT * FROM contracteurs ORDER BY id_contracteur DESC";
            break;
        case 4: // Sort by Id croissant
            queryStr = "SELECT * FROM contracteurs ORDER BY id_contracteur ASC";
            break;
        case 5: // Sort by Avis clients croissant
            queryStr = "SELECT * FROM contracteurs ORDER BY avis_clients ASC";
            break;
        case 6: // Sort by Avis clients décroissant
            queryStr = "SELECT * FROM contracteurs ORDER BY avis_clients DESC";
            break;
        default: // Default: no sorting
            queryStr = "SELECT * FROM contracteurs";
            break;
    }

    model->setQuery(queryStr);

    if (model->lastError().isValid()) {
        qDebug() << "Error in sorting query:" << model->lastError().text();
    }

    // Set column headers
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Prenom"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Telephone"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("Adresse"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("Email"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("Domaine"));
    model->setHeaderData(7, Qt::Horizontal, QObject::tr("Date d'Ajout"));
    model->setHeaderData(8, Qt::Horizontal, QObject::tr("Avis Clients"));

    // Update the table view with the new model
    ui->tableView_2->setModel(model);
    ui->tableView_2->resizeColumnsToContents();
}

void MainWindow::on_chercher_2_clicked() {
    QString searchText = ui->id_rech_2->text().trimmed();
    QString searchCriteria = ui->comboBox_2->currentText();
    QSqlQueryModel *model = new QSqlQueryModel();
    QString queryStr;

    if (searchText.isEmpty()) {
        // If search text is empty, show all records
        queryStr = "SELECT * FROM contracteurs";
    } else {
        // Build the search query based on the selected criteria
        if (searchCriteria == "ID") {
            queryStr = QString("SELECT * FROM contracteurs WHERE id_contracteur = %1").arg(searchText.toInt());
        } else if (searchCriteria == "Nom") {
            queryStr = QString("SELECT * FROM contracteurs WHERE LOWER(nom) LIKE LOWER('%%1%')").arg(searchText);
        } else if (searchCriteria == "Prenom") {
            queryStr = QString("SELECT * FROM contracteurs WHERE LOWER(prenom) LIKE LOWER('%%1%')").arg(searchText);
        } else if (searchCriteria == "Telephone") {
            queryStr = QString("SELECT * FROM contracteurs WHERE telephone LIKE '%%1%'").arg(searchText);
        } else if (searchCriteria == "Adresse") {
            queryStr = QString("SELECT * FROM contracteurs WHERE LOWER(adresse) LIKE LOWER('%%1%')").arg(searchText);
        } else if (searchCriteria == "Email") {
            queryStr = QString("SELECT * FROM contracteurs WHERE LOWER(email) LIKE LOWER('%%1%')").arg(searchText);
        } else if (searchCriteria == "Domaine") {
            queryStr = QString("SELECT * FROM contracteurs WHERE LOWER(domaine) LIKE LOWER('%%1%')").arg(searchText);
        } else if (searchCriteria == "Date d'ajout") {
            queryStr = QString("SELECT * FROM contracteurs WHERE dateajout LIKE '%%1%'").arg(searchText);
        } else if (searchCriteria == "Avis clients") {
            queryStr = QString("SELECT * FROM contracteurs WHERE avis_clients LIKE '%%1%'").arg(searchText);
        } else {
            queryStr = "SELECT * FROM contracteurs"; // Default: show all records
        }
    }

    model->setQuery(queryStr);

    if (model->lastError().isValid()) {
        qDebug() << "Error in search query:" << model->lastError().text();
    }

    // Set column headers
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Prenom"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Telephone"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("Adresse"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("Email"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("Domaine"));
    model->setHeaderData(7, Qt::Horizontal, QObject::tr("Date d'Ajout"));
    model->setHeaderData(8, Qt::Horizontal, QObject::tr("Avis Clients"));

    // Update the table view
    ui->tableView_2->setModel(model);
    ui->tableView_2->resizeColumnsToContents();
}

void MainWindow::on_pdf_2_clicked() {
    static bool isExporting = false; // Prevent double execution
    if (isExporting) {
        return;
    }
    isExporting = true;

    QString filePath = QFileDialog::getSaveFileName(this, "Save PDF", "", "*.pdf");
    if (filePath.isEmpty()) {
        isExporting = false;
        return;
    }

    QPdfWriter pdfWriter(filePath);
    pdfWriter.setPageSize(QPageSize(QPageSize::A4));
    pdfWriter.setResolution(300); // High resolution for better quality
    QPainter painter(&pdfWriter);

    const int margin = 50; // Margin for the PDF
    const int lineHeight = 30; // Height between rows
    const int pageWidth = pdfWriter.width();
    const int pageHeight = pdfWriter.height();
    const int usableWidth = pageWidth - 2 * margin;
    const int usableHeight = pageHeight - 2 * margin;

    int y = margin; // Current y position
    int x = margin; // Current x position

    // Define column widths (proportional to the usable width)
    const int columnWidths[] = {
        usableWidth * 10 / 100, // ID
        usableWidth * 15 / 100, // Nom
        usableWidth * 15 / 100, // Prenom
        usableWidth * 15 / 100, // Telephone
        usableWidth * 25 / 100, // Adresse
        usableWidth * 20 / 100  // Domaine
    };

    // Title
    painter.setFont(QFont("Arial", 16, QFont::Bold));
    painter.drawText(x, y, "Liste des Contracteurs");
    y += lineHeight * 2;

    // Table Headers
    painter.setFont(QFont("Arial", 12, QFont::Bold));
    const QStringList headers = {"ID", "Nom", "Prenom", "Telephone", "Adresse", "Domaine"};
    for (int i = 0; i < headers.size(); ++i) {
        painter.drawText(x, y, headers[i]);
        x += columnWidths[i];
    }
    y += lineHeight;
    x = margin;

    // Draw a line under the headers
    painter.drawLine(margin, y, pageWidth - margin, y);
    y += lineHeight;

    // Table Content
    painter.setFont(QFont("Arial", 10));
    QSqlQuery query("SELECT id_contracteur, nom, prenom, telephone, adresse, domaine FROM contracteurs");
    while (query.next()) {
        // Check if the content exceeds the page height
        if (y + lineHeight > margin + usableHeight) {
            pdfWriter.newPage(); // Create a new page
            y = margin; // Reset y position
            x = margin;

            // Redraw headers on the new page
            painter.setFont(QFont("Arial", 12, QFont::Bold));
            for (int i = 0; i < headers.size(); ++i) {
                painter.drawText(x, y, headers[i]);
                x += columnWidths[i];
            }
            y += lineHeight;
            painter.drawLine(margin, y, pageWidth - margin, y);
            y += lineHeight;
            painter.setFont(QFont("Arial", 10));
        }

        // Write data to the PDF
        x = margin;
        for (int i = 0; i < headers.size(); ++i) {
            painter.drawText(x, y, query.value(i).toString());
            x += columnWidths[i];
        }
        y += lineHeight;
    }

    painter.end();

    // Use a modal message box to prevent further interaction
    QMessageBox msgBox;
    msgBox.setIcon(QMessageBox::Information);
    msgBox.setText("PDF exporté avec succès.");
    msgBox.setWindowTitle("Exportation PDF");
    msgBox.setStandardButtons(QMessageBox::Ok);
    msgBox.exec(); // Modal execution

    isExporting = false; // Reset the flag after the message box is closed
}

void MainWindow::generateStatistics() {
    QSqlQuery query("SELECT domaine, COUNT(*) FROM contracteurs GROUP BY domaine");
    QPieSeries *series = new QPieSeries();

    while (query.next()) {
        QString domaine = query.value(0).toString();
        int count = query.value(1).toInt();
        series->append(domaine, count); // Add data to the pie chart
    }

    if (series->slices().isEmpty()) {
        QMessageBox::information(this, "Statistiques", "Aucune donnée disponible pour les statistiques.");
        return;
    }

    for (QPieSlice *slice : series->slices()) {
        slice->setLabel(QString("%1 (%2)").arg(slice->label()).arg(slice->value()));
        slice->setLabelVisible(true); // Show labels on the pie chart
    }

    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Statistiques des domaines des contracteurs");
    chart->setAnimationOptions(QChart::SeriesAnimations);

    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    QGraphicsScene *scene = new QGraphicsScene(this);
    scene->addWidget(chartView);
    ui->graphicsView->setScene(scene); // Display the chart in the graphics view
    ui->graphicsView->show();
}

void MainWindow::exportStatisticsPDF() {
    QString filePath = QFileDialog::getSaveFileName(this, "Enregistrer les statistiques en PDF", "", "*.pdf");
    if (filePath.isEmpty()) {
        return;
    }

    QPdfWriter pdfWriter(filePath);
    pdfWriter.setPageSize(QPageSize(QPageSize::A4));
    pdfWriter.setResolution(300);
    QPainter painter(&pdfWriter);

    const int margin = 50;
    int y = margin;

    // Title
    painter.setFont(QFont("Arial", 16, QFont::Bold));
    painter.drawText(margin, y, "Statistiques des domaines des contracteurs");
    y += 50;

    // Fetch data for the statistics
    QSqlQuery query("SELECT domaine, COUNT(*) FROM contracteurs GROUP BY domaine");
    QStringList dataLines;
    while (query.next()) {
        QString domaine = query.value(0).toString();
        int count = query.value(1).toInt();
        dataLines.append(QString("%1: %2").arg(domaine).arg(count));
    }

    // Check if there is data to export
    if (dataLines.isEmpty()) {
        QMessageBox::information(this, "Exportation PDF", "Aucune donnée disponible pour l'exportation.");
        return;
    }

    // Write data lines to the PDF
    painter.setFont(QFont("Arial", 12));
    for (const QString &line : dataLines) {
        painter.drawText(margin, y, line);
        y += 30;
    }

    // Draw a pie chart
    QPieSeries *series = new QPieSeries();
    for (const QString &line : dataLines) {
        QStringList parts = line.split(": ");
        if (parts.size() == 2) {
            series->append(parts[0], parts[1].toInt());
        }
    }

    QChart chart;
    chart.addSeries(series);
    chart.setTitle("Répartition des domaines");
    chart.setAnimationOptions(QChart::SeriesAnimations);

    QChartView chartView(&chart);
    chartView.setRenderHint(QPainter::Antialiasing);

    // Render the chart directly onto the PDF
    QRect chartRect(margin, y, pdfWriter.width() - 2 * margin, 400);
    chartView.render(&painter, chartRect);

    painter.end();

    QMessageBox::information(this, "Exportation PDF", "Statistiques exportées avec succès en PDF.");
}

void MainWindow::on_generateStatisticsButton_clicked() {
    generateStatistics();
}

void MainWindow::on_exportStatisticsPDFButton_clicked() {
    exportStatisticsPDF();
}

void MainWindow::on_tabWidget_currentChanged(int index) {
    qDebug() << "Tab changed to index:" << index;

    // Add logic here if specific actions are needed when switching tabs
    switch (index) {
        case 0:
            qDebug() << "First tab selected.";
            break;
        case 1:
            qDebug() << "Second tab selected.";
            break;
        default:
            qDebug() << "Other tab selected.";
            break;
    }
}
