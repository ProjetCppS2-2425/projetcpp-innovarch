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
#include <QJsonDocument>
#include <QJsonObject>

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
    connect(ui->soumettre, &QPushButton::clicked, this, &MainWindow::on_submitEvaluationButton_clicked);

    // Connect table widgets for matching functionality
    connect(ui->tableWidget, &QTableWidget::itemClicked, this, &MainWindow::on_tableWidget_itemClicked);
    connect(ui->tableWidget_2, &QTableWidget::itemClicked, this, &MainWindow::on_tableWidget_2_itemClicked);

    // Connect new buttons for showing evaluation and matching
    connect(ui->evalbutt, &QPushButton::clicked, this, &MainWindow::on_evalbutt_clicked);
    connect(ui->matchinbutt, &QPushButton::clicked, this, &MainWindow::on_matchinbutt_clicked);
}

MainWindow::~MainWindow()
{
    delete ui;
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
    QString contractorId = ui->evatab->model()->data(ui->evatab->model()->index(row, 0)).toString();
    QSqlQuery query;
    query.prepare("SELECT evaluation FROM contracteurs WHERE id_contracteur = :id");
    query.bindValue(":id", contractorId);
    if (!query.exec() || !query.next()) {
        qDebug() << "Error fetching contractor evaluation:" << query.lastError().text();
        return;
    }
    QString evaluationJson = query.value(0).toString();
    QJsonDocument jsonDoc = QJsonDocument::fromJson(evaluationJson.toUtf8());
    QJsonObject jsonObj = jsonDoc.object();

    QPieSeries *series = new QPieSeries();
    for (const QString &key : jsonObj.keys()) {
        series->append(key, jsonObj[key].toDouble());
    }

    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Répartition des domaines évalués");
    chart->setAnimationOptions(QChart::SeriesAnimations);

    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    QGraphicsScene *scene = new QGraphicsScene(this);
    scene->addWidget(chartView);
    ui->graphicsView_2->setScene(scene);
    ui->graphicsView_2->show();
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
    QSqlQuery query("SELECT domaine, COUNT(*) FROM contracteurs GROUP BY domaine");
    int total = 0;
    while (query.next()) {
        QString domaine = query.value(0).toString();
        int count = query.value(1).toInt();
        if (count > 0) {
            total += count;
            series->append(domaine, count);
        }
    }

    if (series->slices().isEmpty()) {
        QMessageBox::information(this, "Statistiques", "Aucune donnée disponible pour les statistiques.");
        return;
    }

    for (QPieSlice *slice : series->slices()) {
        slice->setLabel(QString("%1 (%2)").arg(slice->label()).arg(slice->value()));
        slice->setLabelVisible(true);
        slice->setLabelFont(QFont("Helvetica", 8, QFont::Bold));
    }

    series->setHoleSize(0.5);
    series->setPieSize(0.7);

    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Répartition des domaines des contracteurs");
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

void MainWindow::on_tabWidget_currentChanged(int index) {
    qDebug() << "Tab changed to index:" << index;
    switch (index) {
        case 0:
            qDebug() << "First tab selected.";
            break;
        case 1:
            qDebug() << "Second tab selected.";
            break;
        case 2:
            qDebug() << "Evaluation tab selected.";
            break;
        case 3:
            qDebug() << "Matching tab selected.";
            break;
        default:
            qDebug() << "Other tab selected.";
            break;
    }
}

void MainWindow::on_submitEvaluationButton_clicked() {
    int contractorId = ui->lineEdit_8->text().toInt();
    QString projectType = ui->comboBox_6->currentText();
    double rating = ui->spinBox_2->value();

    if (contractorId == 0 || projectType.isEmpty()) {
        QMessageBox::warning(this, "Input Error", "Veuillez remplir tous les champs !");
        return;
    }

    QSqlQuery query;
    query.prepare("SELECT evaluation FROM contracteurs WHERE id_contracteur = :id");
    query.bindValue(":id", contractorId);
    if (!query.exec() || !query.next()) {
        QMessageBox::warning(this, "Error", "Contractor not found.");
        return;
    }

    QString evaluationJson = query.value(0).toString();
    QJsonDocument jsonDoc = QJsonDocument::fromJson(evaluationJson.toUtf8());
    QJsonObject jsonObj = jsonDoc.object();

    jsonObj[projectType] = rating;

    QString updatedJson = QString(QJsonDocument(jsonObj).toJson(QJsonDocument::Compact));

    query.prepare("UPDATE contracteurs SET evaluation = :evaluation WHERE id_contracteur = :id");
    query.bindValue(":evaluation", updatedJson);
    query.bindValue(":id", contractorId);

    if (query.exec()) {
        QMessageBox::information(this, "Success", "Évaluation soumise avec succès.");
        fillTableWidget();
    } else {
        QMessageBox::warning(this, "Error", "Échec de la mise à jour de l'évaluation.");
    }
}

void MainWindow::on_tableWidget_itemClicked(QTableWidgetItem *item) {
    int row = item->row();
    QString projectDomain = ui->tableWidget->item(row, 2)->text();
    QSqlQuery query;
    query.prepare("SELECT id_contracteur, nom, domaine, historique FROM contracteurs");
    if (!query.exec()) {
        qDebug() << "Error fetching contractors:" << query.lastError().text();
        return;
    }

    ui->tableWidget_2->setRowCount(0);

    while (query.next()) {
        int id = query.value(0).toInt();
        QString name = query.value(1).toString();
        QString domain = query.value(2).toString();
        int completedProjects = query.value(3).toInt();

        int matchPercentage = 0;
        if (domain == projectDomain) {
            matchPercentage += 70;
        }
        matchPercentage += qMin(completedProjects / 10, 30);

        int rowCount = ui->tableWidget_2->rowCount();
        ui->tableWidget_2->insertRow(rowCount);
        ui->tableWidget_2->setItem(rowCount, 0, new QTableWidgetItem(QString::number(id)));
        ui->tableWidget_2->setItem(rowCount, 1, new QTableWidgetItem(name));
        ui->tableWidget_2->setItem(rowCount, 2, new QTableWidgetItem(domain));
        ui->tableWidget_2->setItem(rowCount, 3, new QTableWidgetItem(QString::number(completedProjects)));
        ui->tableWidget_2->setItem(rowCount, 4, new QTableWidgetItem(QString::number(matchPercentage) + "%"));
    }
}

void MainWindow::on_tableWidget_2_itemClicked(QTableWidgetItem *item) {
    int row = item->row();
    QString contractorDomain = ui->tableWidget_2->item(row, 2)->text();
    QSqlQuery query;
    query.prepare("SELECT id_projet, nom_projet, type_projet, budget, echeance FROM projets WHERE id_contracteur IS NULL");
    if (!query.exec()) {
        qDebug() << "Error fetching projects:" << query.lastError().text();
        return;
    }

    ui->tableWidget->setRowCount(0);

    while (query.next()) {
        int id = query.value(0).toInt();
        QString name = query.value(1).toString();
        QString domain = query.value(2).toString();
        int budget = query.value(3).toInt();
        QString deadline = query.value(4).toString();

        int matchPercentage = 0;
        if (domain == contractorDomain) {
            matchPercentage += 70;
        }
        matchPercentage += qMin(budget / 10000, 30);

        int rowCount = ui->tableWidget->rowCount();
        ui->tableWidget->insertRow(rowCount);
        ui->tableWidget->setItem(rowCount, 0, new QTableWidgetItem(QString::number(id)));
        ui->tableWidget->setItem(rowCount, 1, new QTableWidgetItem(name));
        ui->tableWidget->setItem(rowCount, 2, new QTableWidgetItem(domain));
        ui->tableWidget->setItem(rowCount, 3, new QTableWidgetItem(QString::number(budget)));
        ui->tableWidget->setItem(rowCount, 4, new QTableWidgetItem(deadline));
        ui->tableWidget->setItem(rowCount, 5, new QTableWidgetItem(QString::number(matchPercentage) + "%"));
    }
}

void MainWindow::on_evalbutt_clicked() {
    QSqlQueryModel *model = new QSqlQueryModel();
    model->setQuery("SELECT id_contracteur, nom, domaine, historique FROM contracteurs");
    if (model->lastError().isValid()) {
        qDebug() << "Error fetching contractors for evaluation:" << model->lastError().text();
        QMessageBox::warning(this, "Database Error", "Failed to fetch contractors for evaluation.");
        return;
    }

    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Domaine"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Projets Réalisés"));

    ui->evatab->setModel(model);
    ui->evatab->resizeColumnsToContents();
}

void MainWindow::on_matchinbutt_clicked() {
    qDebug() << "Matching button clicked.";

    // Populate the free projects table
    QSqlQuery projectQuery;
    projectQuery.prepare("SELECT id_projet, nom_projet, type_projet, budget, echeance FROM projets WHERE id_contracteur IS NULL");
    if (!projectQuery.exec()) {
        qDebug() << "Error fetching free projects:" << projectQuery.lastError().text();
        QMessageBox::warning(this, "Database Error", "Failed to fetch free projects.");
        return;
    }

    ui->tableWidget->setRowCount(0);

    while (projectQuery.next()) {
        int rowCount = ui->tableWidget->rowCount();
        ui->tableWidget->insertRow(rowCount);
        ui->tableWidget->setItem(rowCount, 0, new QTableWidgetItem(projectQuery.value(0).toString()));
        ui->tableWidget->setItem(rowCount, 1, new QTableWidgetItem(projectQuery.value(1).toString()));
        ui->tableWidget->setItem(rowCount, 2, new QTableWidgetItem(projectQuery.value(2).toString()));
        ui->tableWidget->setItem(rowCount, 3, new QTableWidgetItem(projectQuery.value(3).toString()));
        ui->tableWidget->setItem(rowCount, 4, new QTableWidgetItem(projectQuery.value(4).toString()));
    }

    qDebug() << "Free projects table populated successfully.";

    // Populate the suggested contractors table
    QSqlQuery contractorQuery;
    contractorQuery.prepare("SELECT id_contracteur, nom, domaine, historique FROM contracteurs");
    if (!contractorQuery.exec()) {
        qDebug() << "Error fetching contractors:" << contractorQuery.lastError().text();
        QMessageBox::warning(this, "Database Error", "Failed to fetch contractors.");
        return;
    }

    ui->tableWidget_2->setRowCount(0);

    while (contractorQuery.next()) {
        int rowCount = ui->tableWidget_2->rowCount();
        ui->tableWidget_2->insertRow(rowCount);
        ui->tableWidget_2->setItem(rowCount, 0, new QTableWidgetItem(contractorQuery.value(0).toString()));
        ui->tableWidget_2->setItem(rowCount, 1, new QTableWidgetItem(contractorQuery.value(1).toString()));
        ui->tableWidget_2->setItem(rowCount, 2, new QTableWidgetItem(contractorQuery.value(2).toString()));
        ui->tableWidget_2->setItem(rowCount, 3, new QTableWidgetItem(contractorQuery.value(3).toString()));
    }

    qDebug() << "Suggested contractors table populated successfully.";
}

void MainWindow::on_matchingbutt_clicked() {
    qDebug() << "Matching button clicked.";

    // Populate the free projects table
    QSqlQuery projectQuery;
    projectQuery.prepare("SELECT id_projet, nom_projet, type_projet, budget, echeance FROM projets WHERE id_contracteur IS NULL");
    if (!projectQuery.exec()) {
        qDebug() << "Error fetching free projects:" << projectQuery.lastError().text();
        QMessageBox::warning(this, "Database Error", "Failed to fetch free projects.");
        return;
    }

    ui->tableWidget->setRowCount(0);

    while (projectQuery.next()) {
        int rowCount = ui->tableWidget->rowCount();
        ui->tableWidget->insertRow(rowCount);
        ui->tableWidget->setItem(rowCount, 0, new QTableWidgetItem(projectQuery.value(0).toString()));
        ui->tableWidget->setItem(rowCount, 1, new QTableWidgetItem(projectQuery.value(1).toString()));
        ui->tableWidget->setItem(rowCount, 2, new QTableWidgetItem(projectQuery.value(2).toString()));
        ui->tableWidget->setItem(rowCount, 3, new QTableWidgetItem(projectQuery.value(3).toString()));
        ui->tableWidget->setItem(rowCount, 4, new QTableWidgetItem(projectQuery.value(4).toString()));
    }

    qDebug() << "Free projects table populated successfully.";

    // Populate the suggested contractors table
    QSqlQuery contractorQuery;
    contractorQuery.prepare("SELECT id_contracteur, nom, domaine, historique FROM contracteurs");
    if (!contractorQuery.exec()) {
        qDebug() << "Error fetching contractors:" << contractorQuery.lastError().text();
        QMessageBox::warning(this, "Database Error", "Failed to fetch contractors.");
        return;
    }

    ui->tableWidget_2->setRowCount(0);

    while (contractorQuery.next()) {
        int rowCount = ui->tableWidget_2->rowCount();
        ui->tableWidget_2->insertRow(rowCount);
        ui->tableWidget_2->setItem(rowCount, 0, new QTableWidgetItem(contractorQuery.value(0).toString()));
        ui->tableWidget_2->setItem(rowCount, 1, new QTableWidgetItem(contractorQuery.value(1).toString()));
        ui->tableWidget_2->setItem(rowCount, 2, new QTableWidgetItem(contractorQuery.value(2).toString()));
        ui->tableWidget_2->setItem(rowCount, 3, new QTableWidgetItem(contractorQuery.value(3).toString()));
    }

    qDebug() << "Suggested contractors table populated successfully.";
}
