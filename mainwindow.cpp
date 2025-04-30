#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QSqlError>
#include <QDebug>
#include <QString>
#include <QFileDialog>
#include <QPdfWriter>
#include <QPainter>
#include <QtCharts/QChartView>
#include <QtCharts/QPieSeries>
#include <QtCharts/QPieSlice>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QStandardItemModel>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QTimer>

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

    // Connect statistics-related buttons to their slots
    connect(ui->stat1_2, &QPushButton::clicked, this, &MainWindow::on_generateStatisticsButton_clicked);
    connect(ui->stat2_2, &QPushButton::clicked, this, &MainWindow::on_generateStatisticsButton_clicked);
    connect(ui->statbutt, &QPushButton::clicked, this, &MainWindow::on_generateStatisticsButton_clicked);
    connect(ui->pdf_3, &QPushButton::clicked, this, &MainWindow::on_exportStatisticsPDFButton_clicked);
    connect(ui->contractorlisttable, &QTableView::clicked, this, &MainWindow::on_contractorlisttable_clicked);

    // Populate the architects table
    loadArchitectsToListView();

    // Connect to Arduino
    if (arduino.connect_arduino() == 0) {
        qDebug() << "✅ Arduino connected successfully.";
    } else {
        qDebug() << "❌ Failed to connect to Arduino.";
    }

    // Set up a timer to continuously read from Arduino
    QTimer *arduinoTimer = new QTimer(this);
    connect(arduinoTimer, &QTimer::timeout, this, &MainWindow::readArduinoData);
    arduinoTimer->start(100); // Check every 100ms
}

MainWindow::~MainWindow()
{
    delete ui;

    arduino.close_arduino(); // Ensure Arduino is disconnected on exit
}

void MainWindow::fillTableWidget() {
    QSqlQueryModel *model = currentContracteur.afficher();
    if (!model) {
        qDebug() << "Failed to fetch model for tableView_2.";
        return;
    }
    ui->tableView_2->setModel(model);
    ui->tableView_2->resizeColumnsToContents();
    model->setHeaderData(7, Qt::Horizontal, QObject::tr("Date d'Ajout"));
}

void MainWindow::on_addContracteurButton_clicked() {
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
    QString adresse = ui->lineEdit_4->text();
    if (adresse.isEmpty()) {
        QMessageBox::warning(this, "Input Error", "Adresse est vide !");
        return;
    }
    QString email = ui->lineEdit_5->text();
    if (email.isEmpty()) {
        QMessageBox::warning(this, "Input Error", "Email est vide !");
        return;
    }
    if (!QRegularExpression("^[\\w.-]+@[\\w.-]+\\.[a-zA-Z]{2,}$").match(email).hasMatch()) {
        QMessageBox::warning(this, "Input Error", "L'email doit être au format something@something.something !");
        return;
    }
    QString domaine = ui->comboBox->currentText();
    if (domaine == "Categorie") {
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
        // Update the historique column to start with 1
        QSqlQuery updateQuery;
        updateQuery.prepare("UPDATE contracteurs SET historique = :historique WHERE id_contracteur = :id");
        updateQuery.bindValue(":historique", 1);
        updateQuery.bindValue(":id", id_contracteur);
        if (!updateQuery.exec()) {
            qDebug() << "Failed to update historique:" << updateQuery.lastError().text();
        }
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
    int id = ui->lineEdit_3->text().toInt();
    if (id == 0) {
        QMessageBox::warning(this, "Input Error", "L'ID pour supprimer est vide.");
        return;
    }
    if (currentContracteur.supprimer(id)) {
        currentContracteur.reassignIds();
        QMessageBox::information(this, "Success", "Contracteur supprimé avec succès.");
        fillTableWidget();
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

void MainWindow::on_modifyContracteurButton_clicked() {
    int id = ui->lineEdit_3->text().toInt();
    if (id == 0) {
        QMessageBox::warning(this, "Input Error", "L'ID pour modifier est vide.");
        return;
    }
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
    QString adresse = ui->lineEdit_4->text();
    if (adresse.isEmpty()) {
        QMessageBox::warning(this, "Input Error", "Adresse est vide !");
        return;
    }
    QString email = ui->lineEdit_5->text();
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

void MainWindow::on_tableView_2_itemClicked(const QModelIndex &index) {
    int row = index.row();
    QAbstractItemModel *model = ui->tableView_2->model();

    // Ensure the model is valid
    if (!model) {
        qDebug() << "Model is null.";
        return;
    }

    // Populate the form fields with the selected row's data
    ui->lineEdit_3->setText(model->data(model->index(row, 0)).toString()); // ID
    ui->lineEdit_2->setText(model->data(model->index(row, 1)).toString()); // Nom
    ui->lineEdit_13->setText(model->data(model->index(row, 2)).toString()); // Prenom
    ui->lineEdit_7->setText(model->data(model->index(row, 3)).toString()); // Telephone
    ui->lineEdit_4->setText(model->data(model->index(row, 4)).toString()); // Adresse
    ui->lineEdit_5->setText(model->data(model->index(row, 5)).toString()); // Email
    ui->comboBox->setCurrentText(model->data(model->index(row, 6)).toString()); // Domaine

    // Highlight the selected row in black
    for (int i = 0; i < model->rowCount(); ++i) {
        for (int j = 0; j < model->columnCount(); ++j) {
            if (i == row) {
                ui->tableView_2->model()->setData(model->index(i, j), QBrush(Qt::black), Qt::BackgroundRole);
                ui->tableView_2->model()->setData(model->index(i, j), QBrush(Qt::white), Qt::ForegroundRole);
            } else {
                ui->tableView_2->model()->setData(model->index(i, j), QBrush(Qt::NoBrush), Qt::BackgroundRole);
                ui->tableView_2->model()->setData(model->index(i, j), QBrush(Qt::black), Qt::ForegroundRole);
            }
        }
    }
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
    ui->lineEdit_4->clear();
    ui->lineEdit_5->clear();
    ui->comboBox->setCurrentIndex(0);
}

void MainWindow::on_comboBox_tri_2_currentIndexChanged(int index) {
    ui->tableView_2->setModel(nullptr);
    QSqlQueryModel *model = new QSqlQueryModel();
    QString queryStr;

    switch (index) {
        case 1:
            queryStr = "SELECT * FROM contracteurs ORDER BY dateajout ASC";
            break;
        case 2:
            queryStr = "SELECT * FROM contracteurs ORDER BY LOWER(domaine) ASC";
            break;
        case 3:
            queryStr = "SELECT * FROM contracteurs ORDER BY id_contracteur DESC";
            break;
        case 4:
            queryStr = "SELECT * FROM contracteurs ORDER BY id_contracteur ASC";
            break;
        case 5:
            queryStr = "SELECT * FROM contracteurs ORDER BY avis_clients ASC";
            break;
        case 6:
            queryStr = "SELECT * FROM contracteurs ORDER BY avis_clients DESC";
            break;
        case 7: // Sort by name
            queryStr = "SELECT * FROM contracteurs ORDER BY LOWER(nom) ASC";
            break;
        default:
            queryStr = "SELECT * FROM contracteurs";
            break;
    }

    model->setQuery(queryStr);
    if (model->lastError().isValid()) {
        qDebug() << "Error in sorting query:" << model->lastError().text();
    }

    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Prenom"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Telephone"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("Adresse"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("Email"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("Domaine"));
    model->setHeaderData(7, Qt::Horizontal, QObject::tr("Date d'Ajout"));
    model->setHeaderData(8, Qt::Horizontal, QObject::tr("Avis Clients"));

    ui->tableView_2->setModel(model);
    ui->tableView_2->resizeColumnsToContents();
}

void MainWindow::on_chercher_2_clicked() {
    QString searchText = ui->id_rech_2->text().trimmed();
    QString searchCriteria = ui->comboBox_2->currentText();
    QSqlQueryModel *model = new QSqlQueryModel();
    QString queryStr;

    if (searchText.isEmpty()) {
        queryStr = "SELECT * FROM contracteurs";
    } else {
        if (searchCriteria == "ID") {
            queryStr = QString("SELECT * FROM contracteurs WHERE id_contracteur = %1").arg(searchText.toInt());
        } else if (searchCriteria == "Nom") {
            queryStr = QString("SELECT * FROM contracteurs WHERE LOWER(nom) LIKE LOWER('%%1%')").arg(searchText);
        } else if (searchCriteria == "Prenom") {
            queryStr = QString("SELECT * FROM contracteurs WHERE LOWER(prenom) LIKE LOWER('%%1%')").arg(searchText);
        } else {
            queryStr = "SELECT * FROM contracteurs";
        }
    }

    model->setQuery(queryStr);
    if (model->lastError().isValid()) {
        qDebug() << "Error in search query:" << model->lastError().text();
        QMessageBox::warning(this, "Search Error", "Failed to execute search query.");
        return;
    }

    ui->tableView_2->setModel(model);
    ui->tableView_2->resizeColumnsToContents();
}

void MainWindow::on_pdf_2_clicked() {
    static bool isExporting = false;
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
    pdfWriter.setResolution(300);
    QPainter painter(&pdfWriter);

    const int margin = 50;
    const int lineHeight = 50;
    const int pageWidth = pdfWriter.width();
    const int usableWidth = pageWidth - 2 * margin;
    int y = margin;

    painter.setFont(QFont("Helvetica", 16, QFont::Bold));
    painter.drawText(QRect(margin, y, usableWidth, lineHeight), Qt::AlignCenter, "Liste des Contracteurs");
    y += lineHeight * 2;

    painter.setFont(QFont("Helvetica", 12, QFont::Bold));
    const QStringList headers = {"ID", "Nom", "Prenom", "Telephone", "Adresse", "Domaine"};
    const int columnWidths[] = {10, 15, 15, 15, 25, 20};
    int x = margin;
    for (int i = 0; i < headers.size(); ++i) {
        int colWidth = usableWidth * columnWidths[i] / 100;
        painter.drawText(x, y, headers[i]);
        x += colWidth;
    }
    y += lineHeight;

    painter.drawLine(margin, y, pageWidth - margin, y);
    y += lineHeight;

    painter.setFont(QFont("Helvetica", 10));
    QSqlQuery query("SELECT id_contracteur, nom, prenom, telephone, adresse, domaine FROM contracteurs");
    while (query.next()) {
        x = margin;
        for (int i = 0; i < headers.size(); ++i) {
            int colWidth = usableWidth * columnWidths[i] / 100;
            painter.drawText(x, y, query.value(i).toString());
            x += colWidth;
        }
        y += lineHeight;
        if (y + lineHeight > pdfWriter.height() - margin) {
            pdfWriter.newPage();
            y = margin;
        }
    }

    painter.end();
    QMessageBox::information(this, "Exportation PDF", "PDF exporté avec succès.");
    isExporting = false;
}

void MainWindow::generateStatistics() {
    QPieSeries *series = new QPieSeries();

    // Ensure the database connection is open
    if (!QSqlDatabase::database().isOpen()) {
        QMessageBox::critical(this, "Database Error", "La connexion à la base de données est fermée.");
        return;
    }

    QSqlQuery query;
    if (!query.exec("SELECT domaine, COUNT(*) FROM contracteurs GROUP BY domaine")) {
        QMessageBox::critical(this, "Query Error", "Échec de l'exécution de la requête pour les statistiques.");
        qDebug() << "Query Error:" << query.lastError().text();
        return;
    }

    int total = 0;

    // Calculate the total count
    while (query.next()) {
        total += query.value(1).toInt();
    }

    // Check if total is zero
    if (total == 0) {
        QMessageBox::information(this, "Statistiques", "Aucune donnée disponible pour les statistiques.");
        return;
    }

    // Reset the query to iterate again
    query.exec("SELECT domaine, COUNT(*) FROM contracteurs GROUP BY domaine");

    // Add slices with percentages
    while (query.next()) {
        QString domaine = query.value(0).toString();
        int count = query.value(1).toInt();
        double percentage = (static_cast<double>(count) / total) * 100;
        series->append(QString("%1 (%2%)").arg(domaine).arg(QString::number(percentage, 'f', 2)), count);
    }

    for (QPieSlice *slice : series->slices()) {
        slice->setLabel(slice->label());
        slice->setLabelVisible(true);
        slice->setLabelFont(QFont("Helvetica", 8, QFont::Bold));
    }

    series->setHoleSize(0.5);
    series->setPieSize(0.7);

    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Répartition des domaines des contracteurs (en pourcentage)");
    chart->setTitleFont(QFont("Helvetica", 12, QFont::Bold));
    chart->legend()->setAlignment(Qt::AlignRight);
    chart->legend()->setFont(QFont("Helvetica", 8));
    chart->setAnimationOptions(QChart::SeriesAnimations);

    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    chartView->setMinimumSize(600, 400);

    QGraphicsScene *scene = new QGraphicsScene(this);
    scene->addWidget(chartView);
    ui->graphicsView->setScene(scene);
    ui->graphicsView->show();
}

void MainWindow::exportStatisticsPDF() {
    QString filePath = QFileDialog::getSaveFileName(this, "Enregistrer les statistiques en PDF", "", "*.pdf");
    if (filePath.isEmpty()) {
        return;
    }

    QPdfWriter pdf(filePath);
    pdf.setPageSize(QPageSize(QPageSize::A4));
    pdf.setResolution(300);

    QPainter painter(&pdf);
    const int margin = 50;
    int y = margin;

    QPixmap logo(":/ressources/images/Logo.png");
    if (!logo.isNull()) {
        painter.drawPixmap(margin, y, logo.scaledToHeight(100, Qt::SmoothTransformation));
    }

    QFont dateFont("Helvetica", 10, QFont::Normal);
    painter.setFont(dateFont);
    QString dateStr = QDate::currentDate().toString("dd/MM/yyyy");
    painter.drawText(pdf.width() - margin - 150, y + 30, "📅 " + dateStr);

    y += 120;
    QFont titleFont("Helvetica", 16, QFont::Bold);
    painter.setFont(titleFont);
    painter.drawText(QRect(margin, y, pdf.width() - 2 * margin, 50), Qt::AlignCenter, "Statistiques des domaines des contracteurs");
    y += 80;

    QPixmap chartPixmap = ui->graphicsView->grab();
    if (!chartPixmap.isNull()) {
        int chartWidth = pdf.width() - 2 * margin;
        QPixmap scaledChart = chartPixmap.scaledToWidth(chartWidth, Qt::SmoothTransformation);
        painter.drawPixmap(margin, y, scaledChart);
        y += scaledChart.height() + 50;
    } else {
        painter.setFont(QFont("Helvetica", 10));
        painter.drawText(margin, y, "⚠ Le graphique n'a pas pu être généré.");
        y += 50;
    }

    QSqlQuery query("SELECT domaine, COUNT(*) FROM contracteurs GROUP BY domaine");
    QStringList dataLines;
    while (query.next()) {
        QString domaine = query.value(0).toString();
        int count = query.value(1).toInt();
        dataLines.append(QString("%1: %2").arg(domaine).arg(count));
    }

    painter.setFont(QFont("Helvetica", 11));
    painter.setPen(Qt::black);
    for (const QString &line : dataLines) {
        painter.drawText(margin, y, line);
        y += 30;
    }

    y += 40;
    painter.setPen(Qt::gray);
    painter.drawLine(margin, y, pdf.width() - margin, y);
    y += 20;

    QFont footerFont("Helvetica", 9);
    footerFont.setItalic(true);
    painter.setFont(footerFont);
    painter.drawText(margin, y, "Exporté par l'application de gestion des contracteurs");

    painter.end();
    QMessageBox::information(this, "Exportation PDF", "Statistiques exportées avec succès en PDF.");
}

void MainWindow::on_generateStatisticsButton_clicked() {
    generateStatistics();
}

void MainWindow::on_exportStatisticsPDFButton_clicked() {
    exportStatisticsPDF();
}

void MainWindow::loadContractorsToTable(QTableView *tableView) {
    QSqlQueryModel *model = currentContracteur.afficher();
    tableView->setModel(model);
    tableView->resizeColumnsToContents();
}

void MainWindow::loadTasksForContractor(int contractorId) {
    QSqlQuery query;
    query.prepare("SELECT tasks FROM contracteurs WHERE id_contracteur = :id");
    query.bindValue(":id", contractorId);
    if (query.exec() && query.next()) {
        QString tasksJson = query.value(0).toString();
        QJsonDocument doc = QJsonDocument::fromJson(tasksJson.toUtf8());
        QJsonArray tasksArray = doc.array();

        QStandardItemModel *model = new QStandardItemModel(this);
        for (const QJsonValue &value : tasksArray) {
            QJsonObject taskObj = value.toObject();
            QString taskName = taskObj["name"].toString();
            QString status = taskObj["status"].toString();

            QStandardItem *item = new QStandardItem(taskName + " (" + status + ")");
            model->appendRow(item);
        }
        ui->taskslist->setModel(model);
    }
}

void MainWindow::populateTreeView(int contractorId) {
    clearTreeView();

    QSqlQuery query;
    query.prepare("SELECT nom, prenom, historique, tasks, email, telephone, adresse FROM contracteurs WHERE id_contracteur = :id");
    query.bindValue(":id", contractorId);
    if (query.exec() && query.next()) {
        QString contractorName = query.value(0).toString() + " " + query.value(1).toString();
        QString historique = query.value(2).toString();
        QString tasksJson = query.value(3).toString();
        QString email = query.value(4).toString();
        QString telephone = query.value(5).toString();
        QString adresse = query.value(6).toString();

        QJsonDocument doc = QJsonDocument::fromJson(tasksJson.toUtf8());
        QJsonArray tasksArray = doc.array();

        QStandardItemModel *model = new QStandardItemModel(this);
        QStandardItem *contractorItem = new QStandardItem(contractorName);

        // Add detailed information
        contractorItem->appendRow(new QStandardItem("Email: " + email));
        contractorItem->appendRow(new QStandardItem("Telephone: " + telephone));
        contractorItem->appendRow(new QStandardItem("Adresse: " + adresse));
        contractorItem->appendRow(new QStandardItem("Historique: " + historique));

        QStandardItem *tasksItem = new QStandardItem("Tasks");
        for (const QJsonValue &value : tasksArray) {
            QJsonObject taskObj = value.toObject();
            QString taskName = taskObj["name"].toString();
            QString status = taskObj["status"].toString();

            QStandardItem *taskItem = new QStandardItem(taskName + " (" + status + ")");
            tasksItem->appendRow(taskItem);
        }
        contractorItem->appendRow(tasksItem);

        model->appendRow(contractorItem);
        ui->treeView->setModel(model);
    }
}

void MainWindow::clearTreeView() {
    QStandardItemModel *model = new QStandardItemModel(this);
    ui->treeView->setModel(model);
}

void MainWindow::updateTaskStatus(int contractorId, const QString &task, const QString &status) {
    QSqlQuery query;
    query.prepare("SELECT tasks FROM contracteurs WHERE id_contracteur = :id");
    query.bindValue(":id", contractorId);
    if (query.exec() && query.next()) {
        QString tasksJson = query.value(0).toString();
        QJsonDocument doc = QJsonDocument::fromJson(tasksJson.toUtf8());
        QJsonArray tasksArray = doc.array();

        for (int i = 0; i < tasksArray.size(); ++i) {
            QJsonObject taskObj = tasksArray[i].toObject();
            if (taskObj["name"].toString() == task) {
                taskObj["status"] = status;
                tasksArray[i] = taskObj; // Update the array element
                break;
            }
        }

        QJsonDocument updatedDoc(tasksArray);
        query.prepare("UPDATE contracteurs SET tasks = :tasks WHERE id_contracteur = :id");
        query.bindValue(":tasks", QString(updatedDoc.toJson(QJsonDocument::Compact)));
        query.bindValue(":id", contractorId);
        query.exec();
    }
}

void MainWindow::on_addtask_clicked() {
    QString task = ui->tasktext->text().trimmed();
    if (task.isEmpty()) {
        QMessageBox::warning(this, "Input Error", "Task cannot be empty.");
        return;
    }

    QModelIndex index = ui->contractorlisttable->currentIndex();
    if (!index.isValid()) {
        QMessageBox::warning(this, "Selection Error", "Please select a contractor.");
        return;
    }

    int contractorId = index.sibling(index.row(), 0).data().toInt();
    QSqlQuery query;
    query.prepare("SELECT tasks FROM contracteurs WHERE id_contracteur = :id");
    query.bindValue(":id", contractorId);
    if (query.exec() && query.next()) {
        QString tasksJson = query.value(0).toString();
        QJsonDocument doc = QJsonDocument::fromJson(tasksJson.toUtf8());
        QJsonArray tasksArray = doc.array();

        QJsonObject newTask;
        newTask["name"] = task;
        newTask["status"] = "Pending";
        tasksArray.append(newTask);

        QJsonDocument updatedDoc(tasksArray);
        query.prepare("UPDATE contracteurs SET tasks = :tasks WHERE id_contracteur = :id");
        query.bindValue(":tasks", QString(updatedDoc.toJson(QJsonDocument::Compact)));
        query.bindValue(":id", contractorId);
        if (query.exec()) {
            QMessageBox::information(this, "Success", "Task added successfully.");
            loadTasksForContractor(contractorId);
            populateTreeView(contractorId);
        } else {
            QMessageBox::warning(this, "Error", "Failed to add task.");
        }
    }
}

void MainWindow::on_completedtask_clicked() {
    QModelIndex index = ui->taskslist->currentIndex();
    if (!index.isValid()) {
        QMessageBox::warning(this, "Selection Error", "Please select a task.");
        return;
    }

    QString task = index.data().toString().split(" (").first();
    QModelIndex contractorIndex = ui->contractorlisttable->currentIndex();
    if (!contractorIndex.isValid()) {
        QMessageBox::warning(this, "Selection Error", "Please select a contractor.");
        return;
    }

    int contractorId = contractorIndex.sibling(contractorIndex.row(), 0).data().toInt();
    updateTaskStatus(contractorId, task, "Completed");
    loadTasksForContractor(contractorId);
    populateTreeView(contractorId);
}

void MainWindow::on_rmtask_clicked() {
    QModelIndex index = ui->taskslist->currentIndex();
    if (!index.isValid()) {
        QMessageBox::warning(this, "Selection Error", "Please select a task.");
        return;
    }

    QString task = index.data().toString().split(" (").first();
    QModelIndex contractorIndex = ui->contractorlisttable->currentIndex();
    if (!contractorIndex.isValid()) {
        QMessageBox::warning(this, "Selection Error", "Please select a contractor.");
        return;
    }

    int contractorId = contractorIndex.sibling(contractorIndex.row(), 0).data().toInt();
    QSqlQuery query;
    query.prepare("SELECT tasks FROM contracteurs WHERE id_contracteur = :id");
    query.bindValue(":id", contractorId);
    if (query.exec() && query.next()) {
        QString tasksJson = query.value(0).toString();
        QJsonDocument doc = QJsonDocument::fromJson(tasksJson.toUtf8());
        QJsonArray tasksArray = doc.array();

        QJsonArray updatedTasksArray;
        for (const QJsonValue &value : tasksArray) {
            QJsonObject taskObj = value.toObject();
            if (taskObj["name"].toString() != task) {
                updatedTasksArray.append(taskObj);
            }
        }

        QJsonDocument updatedDoc(updatedTasksArray);
        query.prepare("UPDATE contracteurs SET tasks = :tasks WHERE id_contracteur = :id");
        query.bindValue(":tasks", QString(updatedDoc.toJson(QJsonDocument::Compact)));
        query.bindValue(":id", contractorId);
        if (query.exec()) {
            QMessageBox::information(this, "Success", "Task removed successfully.");
            loadTasksForContractor(contractorId);
            populateTreeView(contractorId);
        } else {
            QMessageBox::warning(this, "Error", "Failed to remove task.");
        }
    }
}

void MainWindow::on_testaffichertodo_clicked() {
    QModelIndex index = ui->contractorlisttable->currentIndex();
    if (!index.isValid()) {
        QMessageBox::warning(this, "Selection Error", "Please select a contractor.");
        return;
    }

    int contractorId = index.sibling(index.row(), 0).data().toInt();
    loadTasksForContractor(contractorId);
}

void MainWindow::on_affichertree_clicked() {
    QModelIndex index = ui->tableView->currentIndex();
    if (!index.isValid()) {
        QMessageBox::warning(this, "Selection Error", "Please select a contractor.");
        return;
    }

    int contractorId = index.sibling(index.row(), 0).data().toInt();
    populateTreeView(contractorId);
}

void MainWindow::on_contractorlisttable_clicked(const QModelIndex &index) {
    if (!index.isValid()) return;

    int contractorId = index.sibling(index.row(), 0).data().toInt();
    loadTasksForContractor(contractorId);
    populateTreeView(contractorId);
}

void MainWindow::on_tabWidget_currentChanged(int index) {
    if (index == 2) { // To-Do List tab
        loadContractorsToTable(ui->contractorlisttable);
    } else if (index == 3) { // Tree View tab
        loadContractorsToTable(ui->tableView);
    } else if (index == 4) { // Architect tab
        loadArchitectsToListView();
        updatePresenceView();
    }
}

void MainWindow::loadArchitectsToListView()
{
    QSqlQuery query("SELECT ID_ARCHITECTE, NOM, PRENOM FROM ARCHITECTES");
    QStandardItemModel *model = new QStandardItemModel(this);

    while (query.next()) {
        QString architectInfo = QString("%1 - %2 %3")
                                    .arg(query.value(0).toInt()) // ID
                                    .arg(query.value(1).toString()) // Nom
                                    .arg(query.value(2).toString()); // Prenom
        QStandardItem *item = new QStandardItem(architectInfo);
        model->appendRow(item);
    }

    ui->achitectview->setModel(model);
}

void MainWindow::readArduinoData()
{
    QByteArray data = arduino.read_from_arduino();
    if (!data.isEmpty()) {
        QString rawData = QString(data).trimmed(); // Raw data from the reader
        qDebug() << "Raw data from RFID reader:" << rawData;

        // Extract the card ID from the raw data
        QRegularExpression regex("([0-9A-F]{2}:[0-9A-F]{2}:[0-9A-F]{2}:[0-9A-F]{2})");
        QRegularExpressionMatch match = regex.match(rawData);

        if (match.hasMatch()) {
            QString cardId = match.captured(1).toUpper(); // Extracted card ID
            qDebug() << "Card ID extracted:" << cardId;

            // Query the database to find the matching poste in the architectes table
            QSqlQuery query;
            query.prepare("SELECT poste, nom, prenom, presence FROM architectes WHERE UPPER(TRIM(poste)) = :cardId");
            query.bindValue(":cardId", cardId);

            if (query.exec()) {
                if (query.next()) {
                    QString poste = query.value(0).toString().trimmed().toUpper();
                    QString nom = query.value(1).toString();
                    QString prenom = query.value(2).toString();
                    QString presence = query.value(3).toString().toLower(); // Normalize presence value

                    qDebug() << "Matching poste found:" << poste << "for architect:" << nom << prenom << "with presence:" << presence;

                    // Toggle the presence attribute
                    QString newPresence = (presence == "present") ? "absent" : "present";
                    QSqlQuery updateQuery;
                    updateQuery.prepare("UPDATE architectes SET presence = :newPresence WHERE UPPER(TRIM(poste)) = :cardId");
                    updateQuery.bindValue(":newPresence", newPresence);
                    updateQuery.bindValue(":cardId", cardId);

                    if (updateQuery.exec()) {
                        qDebug() << "Presence updated to:" << newPresence;
                        updatePresenceView(); // Refresh the presence view
                    } else {
                        qDebug() << "Failed to update presence:" << updateQuery.lastError().text();
                    }
                } else {
                    qDebug() << "No matching poste found for Card ID:" << cardId;
                }
            } else {
                qDebug() << "Database query failed:" << query.lastError().text();
            }
        } else {
            qDebug() << "No valid card ID found in the raw data.";
        }

        lastScannedCardId = rawData; // Store the last scanned raw data
    }
}

void MainWindow::updatePresenceView()
{
    // Clear the current model to avoid stale data
    QStandardItemModel *model = new QStandardItemModel(this);
    ui->presenceview->setModel(model);

    // Query the database for architects with "present" status
    QSqlQuery query;
    query.prepare("SELECT NOM, PRENOM FROM ARCHITECTES WHERE LOWER(PRESENCE) = 'present'");

    if (!query.exec()) {
        qDebug() << "Failed to fetch presence data:" << query.lastError().text();
        return;
    }

    // Populate the model with the results
    while (query.next()) {
        QString presentArchitect = QString("%1 %2")
                                       .arg(query.value(0).toString()) // NOM
                                       .arg(query.value(1).toString()); // PRENOM
        QStandardItem *item = new QStandardItem(presentArchitect);
        model->appendRow(item);
    }

    // Set the updated model to the presenceview widget
    ui->presenceview->setModel(model);

    // Debug log to confirm the number of entries
    qDebug() << "Presence view updated with" << model->rowCount() << "entries.";
}

void MainWindow::on_assignCard_clicked()
{
    QModelIndex index = ui->achitectview->currentIndex();
    if (!index.isValid()) {
        QMessageBox::warning(this, "Selection Error", "Please select an architect.");
        return;
    }

    QString selectedArchitect = index.data().toString();
    int architectId = selectedArchitect.split(" - ").first().toInt();

    QString cardId = arduino.read_from_arduino().trimmed(); // Read RFID card ID
    if (cardId.isEmpty()) {
        QMessageBox::warning(this, "RFID Error", "No card detected.");
        return;
    }

    // Assign the card ID to the selected architect
    QSqlQuery query;
    query.prepare("UPDATE ARCHITECTES SET RFID_CARD = :cardId WHERE ID_ARCHITECTE = :id");
    query.bindValue(":cardId", cardId);
    query.bindValue(":id", architectId);

    if (query.exec()) {
        QMessageBox::information(this, "Success", QString("Card ID '%1' assigned to Architect ID %2.").arg(cardId).arg(architectId));
    } else {
        QMessageBox::warning(this, "Error", "Failed to assign card.");
    }
}

void MainWindow::togglePresence(int architectId, bool isPresent)
{
    QSqlQuery query;
    query.prepare("UPDATE ARCHITECTES SET PRESENCE = :presence WHERE ID_ARCHITECTE = :id");
    query.bindValue(":presence", isPresent ? "Yes" : "No");
    query.bindValue(":id", architectId);

    if (query.exec()) {
        if (isPresent) {
            arduino.write_to_arduino("OPEN_DOOR"); // Send command to open the door
        }
        updatePresenceView();
    } else {
        QMessageBox::warning(this, "Error", "Failed to update presence.");
    }
}

void MainWindow::on_togglePresence_clicked()
{
    QModelIndex index = ui->achitectview->currentIndex();
    if (!index.isValid()) {
        QMessageBox::warning(this, "Selection Error", "Please select an architect.");
        return;
    }

    QString selectedArchitect = index.data().toString();
    int architectId = selectedArchitect.split(" - ").first().toInt();

    QSqlQuery query;
    query.prepare("SELECT PRESENCE FROM ARCHITECTES WHERE ID_ARCHITECTE = :id");
    query.bindValue(":id", architectId);

    if (query.exec() && query.next()) {
        QString currentPresence = query.value(0).toString();
        bool isPresent = (currentPresence == "present");
        togglePresence(architectId, !isPresent);
    } else {
        QMessageBox::warning(this, "Error", "Failed to toggle presence.");
    }
}