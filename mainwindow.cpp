#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QSqlError>
#include <QDebug>
#include <QFileDialog>
#include <QTextDocument>
#include <QPdfWriter>
#include <QPainter>
#include <QSqlDatabase>
#include <QStandardItemModel>
#include <QtCharts/QChart>
#include <QtCharts/QChartView>
#include <QtCharts/QPieSeries>
#include <QtCharts/QPieSlice>
#include <QGraphicsProxyWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QJsonArray>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , networkManager(new QNetworkAccessManager(this)) // Initialize network manager
{
    ui->setupUi(this);

    // Ensure the correct UI elements are used
    connect(ui->pushButton_4, &QPushButton::clicked, this, &MainWindow::on_pushButton_ASK_clicked);
    refreshTableWidget();
    // Display stats at startup
    displayProjectStats();

    // Apply custom style to the QComboBox for better readability
    ui->comboBox->setStyleSheet(
        "QComboBox {"
        "    border: 2px solid #9f86c0;"
        "    border-radius: 5px;"
        "    background-color: white;"
        "    color: black;"
        "    padding: 4px;"
        "    font: 9pt 'Segoe UI';"
        "}"
        "QComboBox QAbstractItemView {"
        "    background-color: white;"
        "    color: black;"
        "    selection-background-color: #dcd6f7;"
        "    selection-color: black;"
        "    border: 1px solid #9f86c0;"
        "}"
    );

    ui->comboBox_2->setStyleSheet(
        "QComboBox {"
        "    border: 2px solid #9f86c0;"
        "    border-radius: 5px;"
        "    background-color: white;"
        "    color: black;"
        "    padding: 4px;"
        "    font: 9pt 'Segoe UI';"
        "}"
        "QComboBox QAbstractItemView {"
        "    background-color: white;"
        "    color: black;"
        "    selection-background-color: #dcd6f7;"
        "    selection-color: black;"
        "    border: 1px solid #9f86c0;"
        "}"
    );

    // Connect signals to slots
    connect(ui->tableView, &QTableView::clicked, this, &MainWindow::on_tableView_itemClicked);
    connect(ui->ajouter, &QPushButton::clicked, this, &MainWindow::on_addProjectButton_clicked);
    connect(ui->annuler, &QPushButton::clicked, this, &MainWindow::on_cancelButton_clicked);
    connect(ui->supprimer, &QPushButton::clicked, this, &MainWindow::on_deleteProjectButton_clicked);
    connect(ui->modifier, &QPushButton::clicked, this, &MainWindow::on_modifyProjectButton_clicked);
    connect(ui->comboBox_tri_2, &QComboBox::currentTextChanged, this, &MainWindow::on_sortButton_clicked);
    connect(ui->comboBox_2, &QComboBox::currentTextChanged, this, &MainWindow::on_searchButton_clicked);
    connect(ui->chercher_2, &QPushButton::clicked, this, &MainWindow::on_searchButton_clicked);
    connect(ui->pdf_2, &QPushButton::clicked, this, &MainWindow::on_exportPDFButton_clicked);
    connect(ui->stat1_2, &QPushButton::clicked, this, &MainWindow::on_stat1_2_clicked);

    fillTableWidget();
}

void MainWindow::on_pushButton_ASK_clicked()
{
    QString userMessage = ui->lineEdit_projets->text().trimmed();
    if (userMessage.isEmpty()) {
        QMessageBox::warning(this, "Erreur", "Veuillez entrer une question.");
        return;
    }

    ui->textEdit_chart->append("Vous: " + userMessage);
    ui->lineEdit_projets->clear();

    sendChatbotRequest(userMessage);
}

void MainWindow::sendChatbotRequest(const QString &userMessage)
{
    QString fullUrl = chatbotApiUrl + "?key=" + chatbotApiKey;

    QNetworkRequest request;
    request.setUrl(QUrl(fullUrl));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QJsonObject payload;
    QJsonArray contents;
    QJsonObject content;
    QJsonArray parts;
    QJsonObject textPart;

    textPart["text"] = userMessage;
    parts.append(textPart);
    content["parts"] = parts;
    contents.append(content);
    payload["contents"] = contents;

    QNetworkReply *reply = networkManager->post(request, QJsonDocument(payload).toJson());
    connect(reply, &QNetworkReply::finished, this, &MainWindow::handleChatbotResponse);
}

void MainWindow::handleChatbotResponse()
{
    QNetworkReply *reply = qobject_cast<QNetworkReply *>(sender());
    if (!reply) return;

    QByteArray response = reply->readAll();
    if (reply->error() != QNetworkReply::NoError) {
        ui->textEdit_chart->append("Erreur: " + reply->errorString());
        reply->deleteLater();
        return;
    }

    QJsonDocument doc = QJsonDocument::fromJson(response);
    if (doc.isNull()) {
        ui->textEdit_chart->append("Erreur: Réponse invalide.");
        reply->deleteLater();
        return;
    }

    QJsonObject responseObj = doc.object();
    if (responseObj.contains("candidates")) {
        QJsonArray candidates = responseObj["candidates"].toArray();
        if (!candidates.isEmpty()) {
            QJsonObject content = candidates[0].toObject()["content"].toObject();
            QJsonArray parts = content["parts"].toArray();
            if (!parts.isEmpty()) {
                QString botReply = parts[0].toObject()["text"].toString();
                ui->textEdit_chart->append("Assistant: " + botReply);
                reply->deleteLater();
                return;
            }
        }
    }

    ui->textEdit_chart->append("Erreur: Impossible de traiter la réponse.");
    reply->deleteLater();
}

void MainWindow::displayProjectStats()
{
    ProjetCRUD projetCRUD;
    QMap<QString, int> statutCount = projetCRUD.getStatutStatistics();

    // Calculate percentages
    int total = 0;
    for (int count : statutCount.values()) {
        total += count;
    }

    QString statsText = "<==================== CHATBOT====================>\n";
    for (auto it = statutCount.begin(); it != statutCount.end(); ++it) {
        double percentage = (it.value() * 100.0) / total;
        statsText += QString("- %1: %2% (%3 projets)\n")
                         .arg(it.key())
                         .arg(percentage, 0, 'f', 1)
                         .arg(it.value());
    }

    ui->textEdit_chart->append(statsText); // Corrected to use textEdit_chart
}

// Fonction getResponse() adaptée
QString MainWindow::getResponse(const QString &question)
{
    // Corrected: Ensure this function is declared in the header file
    QString lowerQuestion = question.toLower();

    if (lowerQuestion.contains("bonjour") || lowerQuestion.contains("salut")) {
        return "Bonjour ! Je suis l'assistant de gestion de projets. Comment puis-je vous aider ?";
    }
    else if (lowerQuestion.contains("comment créer un projet")) {
        return "Pour créer un projet, allez dans l'onglet 'Projets' et cliquez sur 'Ajouter'. Remplissez les champs requis (nom, type, budget, échéance).";
    }
    else if (lowerQuestion.contains("modifier un projet")) {
        return "Sélectionnez le projet dans la liste, cliquez sur 'Modifier', faites vos changements et sauvegardez.";
    }
    else if (lowerQuestion.contains("supprimer un projet")) {
        return "Sélectionnez le projet et cliquez sur 'Supprimer'. Attention : cette action est irréversible.";
    }
    else if (lowerQuestion.contains("types de projets")) {
        return "Nous gérons différents types de projets : bureaux, résidentiel, commercial, et autres.";
    }
    else if (lowerQuestion.contains("statistiques") || lowerQuestion.contains("stats")) {
        return "Cliquez sur le bouton 'Stat' pour voir la répartition des projets par type, budget et statut.";
    }
    else if (lowerQuestion.contains("rechercher un projet")) {
        return "Utilisez la barre de recherche en haut de la liste des projets. Vous pouvez filtrer par ID, nom ou type.";
    }
    else if (lowerQuestion.contains("trier les projets")) {
        return "Cliquez sur les en-têtes de colonne (Nom, Budget, Échéance) pour trier la liste.";
    }
    else if (lowerQuestion.contains("budget")) {
        return "Le budget d'un projet peut être saisi lors de la création ou modifié ultérieurement dans les détails du projet.";
    }
    else if (lowerQuestion.contains("échéance")) {
        return "L'échéance indique la date de fin prévue du projet. Vous pouvez la modifier dans les détails du projet.";
    }
    else if (lowerQuestion.contains("statut")) {
        return "Les statuts possibles sont : En cours, Terminé, Commercialisé. Changez le statut dans les détails du projet.";
    }
    else if (lowerQuestion.contains("exporter")) {
        return "Vous pouvez exporter la liste des projets en PDF via le bouton 'Exportation PDF'.";
    }
    else if (lowerQuestion.contains("client")) {
        return "Chaque projet peut être associé à un client. Cette information est modifiable dans les détails du projet.";
    }
    else if (lowerQuestion.contains("architecte") || lowerQuestion.contains("contracteur")) {
        return "Les ID d'architecte et de contracteur peuvent être associés à un projet dans ses propriétés avancées.";
    }
    else if (lowerQuestion.contains("pourcentage") || lowerQuestion.contains("répartition")) {
        return "Le diagramme circulaire montre la répartition des projets par type. Cliquez sur 'Stat' pour le voir.";
    }
    else if (lowerQuestion.contains("ajouter") && lowerQuestion.contains("projet")) {
        return "Remplissez le formulaire d'ajout avec : ID auto-généré, nom, type, budget, échéance et statut.";
    }
    else if (lowerQuestion.contains("filtre") || lowerQuestion.contains("recherche avancée")) {
        return "Utilisez la recherche avancée pour filtrer par type, statut ou plage de budget.";
    }
    else if (lowerQuestion.contains("aide") || lowerQuestion.contains("documentation")) {
        return "Consultez le menu 'Aide' pour le guide utilisateur complet ou posez-moi une question spécifique.";
    }
    else if (lowerQuestion.contains("merci") || lowerQuestion.contains("remercie")) {
        return "Je vous en prie ! N'hésitez pas si vous avez d'autres questions sur la gestion des projets.";
    }
    else if (lowerQuestion.contains("au revoir") || lowerQuestion.contains("à plus")) {
        return "Au revoir ! Bonne gestion de vos projets !";
    }
    else {
        return "Je n'ai pas compris votre question. Voici ce que je peux faire :\n"
               "- Aider à créer/modifier/supprimer des projets\n"
               "- Expliquer les statistiques et rapports\n"
               "- Donner des infos sur les budgets et échéances\n"
               "- Aider avec les recherches et tris\n"
               "Essayez une question plus précise !";
    }
}

MainWindow::~MainWindow()
{
    delete ui;
    delete networkManager; // Clean up network manager
}

void MainWindow::fillTableWidget() {
    if (!QSqlDatabase::database().isOpen()) {
        qDebug() << "Database connection is not open!";
        return;
    }

    QSqlQueryModel *model = currentProject.afficher();
    if (model) {
        ui->tableView->setModel(model);
        ui->tableView->resizeColumnsToContents(); // Adjust column widths
        ui->tableView->horizontalHeader()->setStretchLastSection(true); // Stretch the last column
        ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows); // Select entire rows
        ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers); // Disable editing

        qDebug() << "TableView updated successfully.";
    } else {
        qDebug() << "Failed to retrieve model for TableView.";
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
    if (nom.isEmpty() || type.isEmpty() || budget <= 0 || echeance.isEmpty() || statut.isEmpty() || statut == "Statut") {
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

    // Récupération des valeurs
    QString statutDB = ui->tableView->model()->data(ui->tableView->model()->index(row, 5)).toString();
    
    // Mapping des valeurs pour le ComboBox
    if (statutDB == "En cours") {
        ui->comboBox_2->setCurrentText("En cours");
    } else if (statutDB == "Terminé") {
        ui->comboBox_2->setCurrentText("Terminé");
    } else if (statutDB == "Commercialisé") {
        ui->comboBox_2->setCurrentText("Commercialisé");
    } else {
        ui->comboBox_2->setCurrentIndex(0); // Valeur par défaut
    }
    
    // ... le reste de votre code existant ...
    ui->id_rech_2->setText(ui->tableView->model()->data(ui->tableView->model()->index(row, 0)).toString());
    ui->lineEdit_7->setText(ui->tableView->model()->data(ui->tableView->model()->index(row, 1)).toString());
    ui->comboBox->setCurrentText(ui->tableView->model()->data(ui->tableView->model()->index(row, 2)).toString());
    ui->lineEdit_5->setText(ui->tableView->model()->data(ui->tableView->model()->index(row, 3)).toString());
    ui->dateEdit->setDate(QDate::fromString(ui->tableView->model()->data(ui->tableView->model()->index(row, 4)).toString(), "yyyy-MM-dd"));
    ui->dateEdit_2->setDate(QDate::fromString(ui->tableView->model()->data(ui->tableView->model()->index(row, 4)).toString(), "yyyy-MM-dd"));
    ui->lineEdit_2->setText(ui->tableView->model()->data(ui->tableView->model()->index(row, 6)).toString());
    ui->lineEdit_3->setText(ui->tableView->model()->data(ui->tableView->model()->index(row, 7)).toString());
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

void MainWindow::on_sortButton_clicked() {
    QString critere = ui->comboBox_tri_2->currentText();
    QString ordre = "ASC"; // Default to ascending order

    if (critere.contains("decroissant", Qt::CaseInsensitive)) {
        ordre = "DESC";
        critere = "ID_PROJET";
    } else if (critere.contains("croissant", Qt::CaseInsensitive)) {
        critere = "ID_PROJET";
    } else if (critere == "Date d'achat") {
        critere = "ECHEANCE";
    } else if (critere == "Quantité") {
        critere = "BUDGET";
    } else if (critere == "Catégorie") {
        critere = "TYPE_PROJET";
    } else {
        QMessageBox::warning(this, "Erreur", "Critère de tri invalide.");
        return;
    }

    QSqlQueryModel *model = currentProject.trier(critere, ordre);
    if (model && model->rowCount() > 0) {
        ui->tableView->setModel(model);
        qDebug() << "Tri effectué avec succès.";
    } else {
        QMessageBox::information(this, "Aucun résultat", "Aucun projet trouvé pour ce tri.");
    }
}

void MainWindow::on_searchButton_clicked() {
    QString keyword = ui->id_rech_2->text();
    if (keyword.isEmpty()) {
        QMessageBox::warning(this, "Erreur", "Veuillez entrer un ID pour la recherche.");
        return;
    }

    QSqlQueryModel *model = currentProject.rechercher(keyword);
    if (model && model->rowCount() > 0) {
        ui->tableView->setModel(model);
        qDebug() << "Recherche effectuée avec succès.";
    } else {
        QMessageBox::information(this, "Aucun résultat", "Aucun projet trouvé pour cet ID.");
    }
}

void MainWindow::on_exportPDFButton_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(this, "Exporter la Liste des Projets en PDF", "", "*.pdf");
    if (fileName.isEmpty())
        return;

    if (QFileInfo(fileName).suffix().isEmpty())
        fileName.append(".pdf");

    QPdfWriter pdf(fileName);
    pdf.setResolution(300);
    pdf.setPageMargins(QMarginsF(30, 30, 30, 30));

    const int pageWidth = pdf.width();
    const int pageHeight = pdf.height();

    QPainter painter(&pdf);
    painter.setRenderHint(QPainter::Antialiasing);

    const int leftMargin = 50;
    const int topMargin = 100;
    const int bottomMargin = 50;
    int currentY = topMargin;

    painter.setFont(QFont("Arial", 16, QFont::Bold));
    QRect titleRect(0, 50, pageWidth, 40);
    painter.drawText(titleRect, Qt::AlignCenter, "Liste Détaillée des Projets");
    currentY += 60;

    QSqlQueryModel model;
    model.setQuery("SELECT ID_PROJET, NOM_PROJET, TYPE_PROJET, BUDGET, ECHEANCE, STATUT FROM projets");

    if (model.lastError().isValid()) {
        QMessageBox::critical(this, "Erreur de base de données", "Erreur lors de la récupération des données des projets : " + model.lastError().text());
        painter.end();
        return;
    }

    if (model.rowCount() == 0) {
        painter.setFont(QFont("Arial", 12));
        painter.drawText(leftMargin, currentY, "Aucun projet à afficher.");
        painter.end();
        return;
    }

    const int columnCount = model.columnCount();
    const int rowCount = model.rowCount();
    const int headerHeight = 30;
    const int rowHeight = 25;
    const int cellPadding = 5;

    QVector<int> columnWidths(columnCount);
    int totalWidth = 0;

    painter.setFont(QFont("Arial", 8, QFont::Bold));
    for (int col = 0; col < columnCount; ++col) {
        QString header = model.headerData(col, Qt::Horizontal).toString();
        columnWidths[col] = painter.fontMetrics().horizontalAdvance(header) + cellPadding * 2;

        painter.setFont(QFont("Arial", 8));
        for (int row = 0; row < rowCount; ++row) {
            QString data = model.data(model.index(row, col)).toString();
            columnWidths[col] = qMax(columnWidths[col], painter.fontMetrics().horizontalAdvance(data) + cellPadding * 2);
        }
        columnWidths[col] = qMax(columnWidths[col], 80); // Minimum width
        totalWidth += columnWidths[col];
    }

    if (totalWidth > pageWidth - 2 * leftMargin) {
        double ratio = (pageWidth - 2 * leftMargin) / (double)totalWidth;
        for (int col = 0; col < columnCount; ++col) {
            columnWidths[col] *= ratio;
        }
    }

    int tableLeft = leftMargin; // Align left
    currentY += 20;

    // Draw Table Header
    painter.setFont(QFont("Arial", 8, QFont::Bold));
    painter.setPen(QPen(Qt::black, 1));
    painter.setBrush(QBrush(QColor(220, 220, 220))); // Light Gray

    int currentX = tableLeft;
    for (int col = 0; col < columnCount; ++col) {
        painter.drawRect(currentX, currentY, columnWidths[col], headerHeight);
        painter.drawText(QRect(currentX + cellPadding, currentY, columnWidths[col] - 2 * cellPadding, headerHeight),
                         Qt::AlignLeft | Qt::AlignVCenter, model.headerData(col, Qt::Horizontal).toString());
        currentX += columnWidths[col];
    }
    currentY += headerHeight;

    // Draw Table Data
    painter.setFont(QFont("Arial", 8));
    painter.setPen(QPen(Qt::black, 0.5));
    painter.setBrush(Qt::NoBrush);

    for (int row = 0; row < rowCount; ++row) {
        currentX = tableLeft;
        for (int col = 0; col < columnCount; ++col) {
            painter.drawRect(currentX, currentY, columnWidths[col], rowHeight);
            QString text = model.data(model.index(row, col)).toString();
            if (col == 4) { // Format Date
                QDate date = QDate::fromString(text, Qt::ISODate);
                if (date.isValid()) {
                    text = date.toString("dd-MM-yyyy");
                }
            }
            painter.drawText(QRect(currentX + cellPadding, currentY, columnWidths[col] - 2 * cellPadding, rowHeight),
                             Qt::AlignLeft | Qt::AlignVCenter, text);
            currentX += columnWidths[col];
        }
        currentY += rowHeight;

        if (currentY > pageHeight - bottomMargin - rowHeight) {
            painter.setFont(QFont("Arial", 8));
            painter.drawText(QRect(0, pageHeight - 30, pageWidth, 20),
                             Qt::AlignCenter,
                             "Date de génération : " + QDate::currentDate().toString("dd-MM-yyyy"));
            pdf.newPage();
            currentY = topMargin + 60 + headerHeight; // Reset Y after title and header on new page

            // Redraw Header on new page
            currentX = tableLeft;
            painter.setFont(QFont("Arial", 8, QFont::Bold));
            painter.setPen(QPen(Qt::black, 1));
            painter.setBrush(QBrush(QColor(220, 220, 220)));
            for (int col = 0; col < columnCount; ++col) {
                painter.drawRect(currentX, currentY - headerHeight, columnWidths[col], headerHeight);
                painter.drawText(QRect(currentX + cellPadding, currentY - headerHeight, columnWidths[col] - 2 * cellPadding, headerHeight),
                                 Qt::AlignLeft | Qt::AlignVCenter, model.headerData(col, Qt::Horizontal).toString());
                currentX += columnWidths[col];
            }
            painter.setFont(QFont("Arial", 8));
            painter.setPen(QPen(Qt::black, 0.5));
            painter.setBrush(Qt::NoBrush);
        }
    }

    painter.setFont(QFont("Arial", 8));
    painter.drawText(QRect(0, pageHeight - 30, pageWidth, 20),
                     Qt::AlignCenter,
                     "Date de génération : " + QDate::currentDate().toString("dd-MM-yyyy"));

    painter.end();
    QMessageBox::information(this, "Export PDF", "La liste des projets a été exportée avec succès !");
}

void MainWindow::on_importPDFButton_clicked() {
    QString filePath = QFileDialog::getOpenFileName(this, "Importer un fichier PDF", "", "*.pdf");
    if (!filePath.isEmpty()) {
        if (currentProject.importerPDF(filePath)) {
            QMessageBox::information(this, "Succès", "Fichier PDF importé avec succès.");
        } else {
            QMessageBox::warning(this, "Erreur", "Échec de l'importation du fichier PDF.");
        }
    }
}

void MainWindow::on_showStatsButton_clicked() {
    QSqlQuery query("SELECT TYPE_PROJET, COUNT(*) FROM projets GROUP BY TYPE_PROJET");
    QString stats;
    while (query.next()) {
        stats += query.value(0).toString() + ": " + query.value(1).toString() + "\n";
    }
    QMessageBox::information(this, "Statistiques", stats);
}

void MainWindow::on_advancedSearchButton_clicked() {
    // Ensure the widgets exist in the .ui file and their names match
    QString critere = ui->comboBox_tri_2->currentText(); // Use comboBox_tri_2 as a placeholder
    QString valeur = ui->id_rech_2->text();              // Use id_rech_2 as a placeholder

    if (valeur.isEmpty()) {
        QMessageBox::warning(this, "Erreur", "Veuillez entrer une valeur pour la recherche.");
        return;
    }

    QString colonne;
    if (critere == "Nom") {
        colonne = "NOM_PROJET";
    } else if (critere == "Type") {
        colonne = "TYPE_PROJET";
    } else if (critere == "Statut") {
        colonne = "STATUT";
    } else {
        QMessageBox::warning(this, "Erreur", "Critère de recherche invalide.");
        return;
    }

    QSqlQueryModel *model = currentProject.rechercherAvance(colonne, valeur);
    if (model && model->rowCount() > 0) {
        ui->tableView->setModel(model);
        qDebug() << "Recherche avancée effectuée avec succès.";
    } else {
        QMessageBox::information(this, "Aucun résultat", "Aucun projet trouvé pour cette recherche.");
    }
}

void MainWindow::on_searchByCriteriaButton_clicked() {
    QString critere = "STATUT"; // Default to searching by status
    QString valeur = ui->id_rech_2->text(); // Reuse the existing input field for simplicity

    if (valeur.isEmpty()) {
        QMessageBox::warning(this, "Erreur", "Veuillez entrer une valeur pour la recherche.");
        return;
    }

    // Determine the search criterion based on the input
    if (valeur.contains("Terminé", Qt::CaseInsensitive) || valeur.contains("En cours", Qt::CaseInsensitive)) {
        critere = "STATUT";
    } else if (valeur.contains("résidentiel", Qt::CaseInsensitive) || valeur.contains("bureaux", Qt::CaseInsensitive)) {
        critere = "TYPE_PROJET";
    } else {
        critere = "NOM_PROJET";
    }

    QSqlQueryModel *model = currentProject.rechercherParCritere(critere, valeur);
    if (model && model->rowCount() > 0) {
        ui->tableView->setModel(model);
        qDebug() << "Recherche par critère effectuée avec succès.";
    } else {
        QMessageBox::information(this, "Aucun résultat", "Aucun projet trouvé pour cette recherche.");
    }
}

void MainWindow::on_statButton_clicked() {
    QMap<QString, int> categoryCount;
    QSqlQuery query("SELECT TYPE_PROJET FROM projets");

    while (query.next()) {
        QString type = query.value(0).toString().toLower();
        QString category;

        if (type.contains("bureaux")) {
            category = "Bureaux";
        } else if (type.contains("résidentiel")) {
            category = "Résidentiel";
        } else if (type.contains("commercial")) {
            category = "Commercial";
        } else {
            category = "Autres";
        }

        categoryCount[category]++;
    }

    QMap<QString, QColor> categoryColors = {
        {"Bureaux", QColor(33, 158, 188)},     // Soft Blue
        {"Résidentiel", QColor(176, 196, 177)}, // Fresh Green
        {"Commercial", QColor(237, 175, 184)}, // Vibrant Orange
        {"Autres", QColor(155, 89, 182)}       // Elegant Purple
    };

    QPieSeries *series = new QPieSeries();
    int total = 0;
    for (int count : categoryCount.values())
        total += count;

    for (auto it = categoryCount.begin(); it != categoryCount.end(); ++it) {
        double percentage = (double(it.value()) / total) * 100.0;
        QPieSlice *slice = series->append(it.key() + QString(" (%1%)").arg(percentage, 0, 'f', 1), it.value());

        slice->setLabelVisible(true);
        slice->setExploded(false);
        slice->setPen(Qt::NoPen);
        slice->setBrush(categoryColors.value(it.key(), Qt::lightGray));

        QObject::connect(slice, &QPieSlice::hovered, this, [slice](bool hovered) {
            slice->setExploded(hovered);
            slice->setLabelFont(hovered ? QFont("Arial", 11, QFont::Bold) : QFont("Arial", 9));
            slice->setBrush(hovered
                                ? slice->brush().color().lighter(120)  // Slightly lighter on hover
                                : slice->brush().color().darker(100)); // Back to normal
        });
    }

    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Statistiques Des Catégories");
    chart->setTitleFont(QFont("Arial", 14, QFont::Bold));
    chart->legend()->setVisible(true);
    chart->legend()->setAlignment(Qt::AlignRight);
    chart->setBackgroundVisible(true);
    chart->setBackgroundBrush(QBrush(Qt::white));
    chart->setDropShadowEnabled(false);
    chart->setBackgroundPen(Qt::NoPen);
    chart->setAnimationOptions(QChart::AllAnimations);

    // Set donut chart style
    series->setHoleSize(0.4); // Create a donut chart

    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    // Size of chart inside pie_2
    QSize viewSize = ui->pie_2->size();
    int chartW = viewSize.width() * 0.9;
    int chartH = viewSize.height() * 0.9;
    chartView->setFixedSize(chartW, chartH);

    if (ui->pie_2->scene()) {
        delete ui->pie_2->scene();
    }

    QGraphicsScene *scene = new QGraphicsScene(this);

    QGraphicsProxyWidget *proxy = scene->addWidget(chartView);

    // Center the chart
    int x = (viewSize.width() - chartW) / 2;
    int y = (viewSize.height() - chartH) / 2;
    proxy->setPos(x, y);

    ui->pie_2->setScene(scene);
    ui->pie_2->setSceneRect(scene->sceneRect()); // Lock the scene size

    // Disable scrollbars or scaling
    ui->pie_2->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->pie_2->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->pie_2->setAlignment(Qt::AlignLeft | Qt::AlignTop); // Avoid auto-centering
}

void MainWindow::on_stat1_2_clicked() {
    QSqlQuery query("SELECT TYPE_PROJET, COUNT(*) FROM projets GROUP BY TYPE_PROJET");
    QPieSeries *series = new QPieSeries();

    int total = 0;
    QMap<QString, int> categoryCount;
    while (query.next()) {
        QString type = query.value(0).toString();
        int count = query.value(1).toInt();
        categoryCount[type] = count;
        total += count;
    }

    for (auto it = categoryCount.begin(); it != categoryCount.end(); ++it) {
        double percentage = (double(it.value()) / total) * 100.0;
        QPieSlice *slice = series->append(it.key() + QString(" (%1%)").arg(percentage, 0, 'f', 1), it.value());
        slice->setLabelVisible(true);
    }

    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Statistiques des Projets");
    chart->setAnimationOptions(QChart::AllAnimations);

    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    // Adjust the size of the chart to fit the bar_2 graphics view
    QSize viewSize = ui->bar_2->size();
    chartView->setFixedSize(viewSize);

    if (ui->bar_2->scene()) {
        delete ui->bar_2->scene();
    }

    QGraphicsScene *scene = new QGraphicsScene(this);
    scene->addWidget(chartView);
    ui->bar_2->setScene(scene);
    ui->bar_2->setSceneRect(scene->sceneRect());
}
