// Project Headers
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "architechtes.h"
#include "dialog.h"
#include "arduino.h"
#include "IconDelegate.h"
#include "connection.h"

// Qt Core
#include <QTimer>
#include <QDebug>
#include <QRandomGenerator>
#include <QPropertyAnimation>

// Qt GUI & Widgets
#include <QMessageBox>
#include <QFileDialog>
#include <QGraphicsScene>
#include <QGraphicsProxyWidget>
#include <QPainter>
#include <QColor>
#include <QFontMetrics>
#include <QPdfWriter>
#include <QTableWidget>
#include <QRegularExpression>
#include <QRegularExpressionValidator>
#include <QMediaPlayer>
#include <QAudioOutput>

// SQL
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlQueryModel>

// Qt Charts
#include <QtCharts/QChartView>
#include <QtCharts/QChart>
#include <QtCharts/QPieSeries>
#include <QtCharts/QPieSlice>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QBarCategoryAxis>
#include <QtCharts/QValueAxis>
#include <QtCharts/QLegendMarker>

MainWindow::MainWindow(QWidget *parent, const QString &userRole)
    : QMainWindow(parent),
    ui(new Ui::MainWindow),
    m_userRole(userRole),
    proxyModel(new QSortFilterProxyModel(this)),
    isAscending(true)
{
    ui->setupUi(this);

    // ----- COMMON: Setup tabs based on role -----
    //setupTabsBasedOnRole();

    // ----- COMMON: Arduino initialization -----
    arduino = new Arduino(this);
    arduino->connectToArduino();

    connect(arduino, &Arduino::arduinoReady, this, [this]() {
        QString name = gestionRessources.getScannerName();
        int qty = gestionRessources.getScannerQuantity();
        QString cmd = QString("SET:%1:%2\n").arg(name).arg(qty);
        arduino->sendData(name, qty);
        qDebug() << "→ Sent to Arduino:" << cmd.trimmed();
    });

    connect(arduino, &Arduino::decrementRequested, this, &MainWindow::handleDecrement);

    // ----- RESOURCE UI Initialization -----
    ui->mainStack->setCurrentWidget(ui->mainStack);
    fillTab();
    ui->triButton->setIcon(QIcon(":/ressources/images/ascending.png"));
    connect(ui->tableView, &QTableView::clicked, this, &MainWindow::handleIconClick);

    // ----- EMPLOYEE/ROLE UI Initialization -----
    fillTableWidget();
    connect(ui->tableWidget, &QTableWidget::itemClicked, this, &MainWindow::on_tableWidget_itemClicked);

    // ----- BUTTON CONNECTIONS (Avoid duplicates if same name) -----
    //connect(ui->ajouter, &QPushButton::clicked, this, &MainWindow::on_addEmployeeButton_clicked);
    connect(ui->annuler, &QPushButton::clicked, this, &MainWindow::on_annuler_clicked);  // Use correct annuler handler
    connect(ui->refresh, &QPushButton::clicked, this, &MainWindow::on_refreshButton_clicked);
    connect(ui->refresh_3, &QPushButton::clicked, this, &MainWindow::on_refreshButton2_clicked);
    connect(ui->refresh_4, &QPushButton::clicked, this, &MainWindow::refreshTableView);
    connect(ui->chercher, &QPushButton::clicked, this, &MainWindow::on_chercher_clicked);
    connect(ui->triButton, &QPushButton::clicked, this, &MainWindow::on_triButton_2_clicked);
    connect(ui->triCb, &QComboBox::currentIndexChanged, this, &MainWindow::on_triCb_currentIndexChanged);
    connect(ui->statpb, &QPushButton::clicked, this, &MainWindow::on_statpb_clicked);  // or on_statConge_clicked (pick one)

    connect(ui->bellIcon, &QPushButton::clicked, this, &MainWindow::on_bellIcon_clicked);
    connect(ui->bellIcon, &QPushButton::clicked, this, &MainWindow::showAllAlerts);

    QList<QPair<QString, QString>> alerts = gestionRessources.checkAlerts();
    for (const auto& alert : alerts) {
        handleAlertNotification(alert.first, alert.second);
    }

    connect(ui->id_p, &QLineEdit::returnPressed, this, &MainWindow::populateEmployeeInfo);
    connect(ui->soumettre, &QPushButton::clicked, this, &MainWindow::on_soumettreButton_clicked);

    QSqlQueryModel *model = emp.afficherconge();
    ui->afficher_conge->setModel(model);
    ui->afficher_conge->resizeColumnsToContents();
    ui->afficher_conge->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->afficher_conge->setSelectionMode(QAbstractItemView::SingleSelection);
    connect(ui->afficher_conge->selectionModel(), &QItemSelectionModel::selectionChanged, this, &MainWindow::onSelectionChanged);
    connect(ui->refuser_conge, &QPushButton::clicked, this, &MainWindow::on_refuser_clicked);
    connect(ui->accepter_conge, &QPushButton::clicked, this, &MainWindow::on_acceptation_clicked);

    connect(ui->calendarConges, &QCalendarWidget::clicked, this, &MainWindow::onCalendarDateClicked);
    connect(ui->calendarConges, &QCalendarWidget::clicked, this, &MainWindow::refreshCongeTableViewOnDateClick);

    connect(ui->tableWidget->selectionModel(), &QItemSelectionModel::selectionChanged, this, &MainWindow::onRowSelected);

    // Login buttons
    connect(ui->pushButton, &QPushButton::clicked, this, &MainWindow::onLoginClicked);
    connect(ui->pushButton_cl, &QPushButton::clicked, this, &MainWindow::onLoginClicked);
    connect(ui->pushButton_ct, &QPushButton::clicked, this, &MainWindow::onLoginClicked);
    connect(ui->pushButton_contrats, &QPushButton::clicked, this, &MainWindow::onLoginClicked);
    connect(ui->pushButton_proj, &QPushButton::clicked, this, &MainWindow::onLoginClicked);
    //connect(ui->pushButton_r, &QPushButton::clicked, this, &MainWindow::onLoginClicked);
}


MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_ajouter_clicked()
{
    QString nom2 = ui->nomRessource->text();
    int quantite = ui->quantiteRessource->text().toInt();
    QString categorie = ui->categorieRessource->currentText();
    int fournisseur = ui->fournisseurRessource->text().toInt();
    QDate dateAchat = ui->dateAjout->date();
    QString etat = ui->etatRessource->currentText();
    double prix = ui->coutRessource->text().toDouble();
    QDate dateEntretien = ui->dateEntretien->date();
    if ((ui->nomRessource->text().trimmed().isEmpty())) {
        QMessageBox::warning(this, "Erreur", "Le champ 'Nom' est obligatoire !");
        return;
    }
    if (quantite <= 0) {
        QMessageBox::warning(this, "Erreur", "La quantité doit être supérieure à 0 !");
        return;
    }
    if (categorie.isEmpty()) {
        QMessageBox::warning(this, "Erreur", "Veuillez sélectionner une catégorie !");
        return;
    }
    if (fournisseur <= 0 || QString::number(fournisseur).length() != 8) {
        QMessageBox::warning(this, "Erreur", "Le fournisseur doit être un numéro valide à 8 chiffres !");
        return;
    }
    if (etat.isEmpty()) {
        QMessageBox::warning(this, "Erreur", "Veuillez sélectionner un état !");
        return;
    }
    if (prix <= 0.0) {
        QMessageBox::warning(this, "Erreur", "Le prix doit être supérieur à 0 !");
        return;
    }
    if (dateAchat > QDate::currentDate()) {
        QMessageBox::warning(this, "Erreur", "La date d'achat ne peut pas être dans le futur !");
        return;
    }
    if (dateEntretien > QDate::currentDate()) {
        QMessageBox::warning(this, "Erreur", "La date d'entretien ne peut pas être dans le futur !");
        return;
    }
    bool success = gestionRessources.ajouterRessource(nom2, quantite, categorie, fournisseur, dateAchat, etat, prix, dateEntretien);
    if (success) {
        fillTab();
        clearFields();
        QMessageBox::information(this, "Succès", "Ressource ajoutée avec succès !");
        // Check if the added resource is the scanner (ID 9)
        if (nom2 == gestionRessources.getScannerName()) {
            QString name = gestionRessources.getScannerName();
            int qty = gestionRessources.getScannerQuantity();
            arduino->sendData(name, qty);
            qDebug() << "→ Sent to Arduino after add:" << QString("SET:%1:%2\n").arg(name).arg(qty).trimmed();
        }
        return;
    } else {
        QMessageBox::critical(this, "Erreur", "Échec de l'ajout de la ressource !");
    }
}

void MainWindow::on_modifier_clicked()
{
    if (m_currentResourceId == -1) return;
    int id = m_currentResourceId;
    QString nom = ui->nomRessource->text();
    int quantite = ui->quantiteRessource->text().toInt();
    QString categorie = ui->categorieRessource->currentText();
    int fournisseur = ui->fournisseurRessource->text().toInt();
    QDate dateAchat = ui->dateAjout->date();
    QString etat = ui->etatRessource->currentText();
    double prix = ui->coutRessource->text().toDouble();
    QDate dateEntretien = ui->dateEntretien->date();
    if (nom.isEmpty()) {
        QMessageBox::warning(this, "Erreur", "Le champ 'Nom' est obligatoire !");
        return;
    }
    if (quantite <= 0) {
        QMessageBox::warning(this, "Erreur", "La quantité doit être supérieure à 0 !");
        return;
    }
    if (categorie.isEmpty()) {
        QMessageBox::warning(this, "Erreur", "Veuillez sélectionner une catégorie !");
        return;
    }
    if (fournisseur <= 0 || QString::number(fournisseur).length() != 8) { // Corrected from 😎 to 8
        QMessageBox::warning(this, "Erreur", "Le fournisseur doit être un numéro valide à 8 chiffres !");
        return;
    }
    if (etat.isEmpty()) {
        QMessageBox::warning(this, "Erreur", "Veuillez sélectionner un état !");
        return;
    }
    if (prix <= 0.0) {
        QMessageBox::warning(this, "Erreur", "Le prix doit être supérieur à 0 !");
        return;
    }
    if (dateAchat > QDate::currentDate()) {
        QMessageBox::warning(this, "Erreur", "La date d'achat ne peut pas être dans le futur !");
        return;
    }
    if (dateEntretien > QDate::currentDate()) {
        QMessageBox::warning(this, "Erreur", "La date d'entretien ne peut pas être dans le futur !");
        return;
    }
    bool success = gestionRessources.updateRessource(id, nom, quantite, categorie, fournisseur,
                                                     dateAchat, etat, prix, dateEntretien);
    if (success) {
        fillTab();
        clearFields();
        m_currentResourceId = -1;

        // Check if the modified resource is the scanner (ID 9)
        if (id == 9) {
            QString name = gestionRessources.getScannerName();
            int qty = gestionRessources.getScannerQuantity();
            arduino->sendData(name, qty);
            qDebug() << "→ Sent to Arduino after modify:" << QString("SET:%1:%2\n").arg(name).arg(qty).trimmed();
        }
    }
}

void MainWindow::clearFields()
{
    ui->nomRessource->clear();
    ui->quantiteRessource->clear();
    ui->categorieRessource->setCurrentIndex(0);
    ui->fournisseurRessource->clear();
    ui->dateAjout->setDate(QDate::currentDate());
    ui->etatRessource->setCurrentIndex(0);
    ui->coutRessource->clear();
    ui->dateEntretien->setDate(QDate::currentDate());
}

void MainWindow::on_annuler_clicked()
{
    clearFields();
}

void MainWindow::on_chercher_clicked()
{
    QString searchText = ui->recherche->text();
    QString searchCriteria = ui->rechercheCb->currentText();
    QSqlQueryModel *model = new QSqlQueryModel(this);
    gestionRessources.rechercheRessource(searchText, searchCriteria, model);
    ui->tableView->setModel(model);
}

void MainWindow::on_triCb_2_currentIndexChanged(int index)
{
    // Get the sorting criteria from the combo box
    QString criteria = ui->triCb->currentText();
    int columnIndex = -1;

    // Determine the column index based on the selected criteria
    if (criteria == "Date d'achat") {
        columnIndex = 4;
    } else if (criteria == "Quantité") {
        columnIndex = 3;
    } else if (criteria == "Coût") {
        columnIndex = 5;
    }

    if (columnIndex != -1) {
        // Apply sorting with the current sorting order
        Qt::SortOrder order = isAscending ? Qt::AscendingOrder : Qt::DescendingOrder;
        proxyModel->sort(columnIndex, order);
    }
}

void MainWindow::on_triButton_clicked()
{
    static bool isButtonClicked = false;
    if (isButtonClicked) {
        return;
    }
    isButtonClicked = true;
    QTimer::singleShot(300, [this]() {
        isButtonClicked = false; // Reset the click state after the timer expires
    });
    QString criteria = ui->triCb->currentText();
    int columnIndex = -1;
    if (criteria == "Date d'achat") {
        columnIndex = 4;
    } else if (criteria == "Quantité") {
        columnIndex = 3;
    } else if (criteria == "Coût") {
        columnIndex = 5;
    }
    if (columnIndex == -1) {
        columnIndex = 0; // Assuming ID is in column 0
    }
    isAscending = !isAscending;
    Qt::SortOrder order = isAscending ? Qt::AscendingOrder : Qt::DescendingOrder;
    proxyModel->sort(columnIndex, order);
    ui->triButton->setIcon(QIcon(isAscending
                                     ? ":/ressources/images/ascending.png"
                                     : ":/ressources/images/descending.png"));
    qDebug() << "Sorting column:" << columnIndex << "Order:" << (isAscending ? "Ascending" : "Descending");
}

void MainWindow::fillTab()
{
    QSqlQueryModel* model = gestionRessources.afficher();
    if (!model || model->rowCount() == 0) {
        return;
    }
    // Set up the proxy model
    proxyModel->setSourceModel(model);
    proxyModel->setSortCaseSensitivity(Qt::CaseInsensitive);
    // Update the QTableView
    ui->tableView->setModel(proxyModel);
    ui->tableView->setSortingEnabled(true);
    ui->tableView->setItemDelegateForColumn(10, new IconDelegate(this));  // Modifier
    ui->tableView->setItemDelegateForColumn(11, new IconDelegate(this)); // Supprimer
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableView->horizontalHeader()->setDefaultAlignment(Qt::AlignCenter);
}

void MainWindow::handleIconClick(const QModelIndex &index)
{
    if (!index.isValid()) return;
    int row = index.row();
    int column = index.column();
    QModelIndex idIndex = proxyModel->index(row, 0);
    int id = proxyModel->data(idIndex).toInt();
    if (column == 10) { //(pen icon)
        m_currentResourceId = id;
        QString nom, categorie, etat;
        int quantite, fournisseur;
        QDate dateAchat, dateEntretien;
        double prix;
        gestionRessources.load(id, nom, quantite, categorie, fournisseur, dateAchat, etat, prix, dateEntretien);
        // Fill UI fields
        ui->nomRessource->setText(nom);
        ui->quantiteRessource->setText(QString::number(quantite));
        ui->categorieRessource->setCurrentText(categorie);
        ui->fournisseurRessource->setText(QString::number(fournisseur));
        ui->dateAjout->setDate(dateAchat);
        ui->etatRessource->setCurrentText(etat);
        ui->coutRessource->setText(QString::number(prix));
        ui->dateEntretien->setDate(dateEntretien);
    }
    else if (column == 11) {
        gestionRessources.supprimerRessource(id);
        fillTab();

        // Check if deleted resource is scanner (ID 9)
        if (id == 9) {
            QString name = gestionRessources.getScannerName();
            int qty = gestionRessources.getScannerQuantity();
            arduino->sendData(name, qty);
            qDebug() << "→ Sent to Arduino after delete:" << QString("SET:%1:%2\n").arg(name).arg(qty).trimmed();
        }
    }
}

void MainWindow::on_exportPdf_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(this, "Enregistrer le PDF", "", "PDF Files (*.pdf)");
    if (fileName.isEmpty())
        return;

    QPdfWriter pdf(fileName);
    pdf.setPageSize(QPageSize(QPageSize::A4));
    pdf.setResolution(300);

    QPainter painter(&pdf);
    int y = 80;

    // Add logo
    QPixmap logo(":/ressources/images/Logo.png");
    if (!logo.isNull()) {
        painter.drawPixmap(-40, -40, logo.scaledToHeight(220, Qt::SmoothTransformation));
    }

    // Add current date (top-right)
    QFont dateFont("Helvetica", 11, QFont::Normal);
    painter.setFont(dateFont);
    QString dateStr = QDate::currentDate().toString("dd/MM/yyyy");
    painter.drawText(pdf.width() - 300, 50, "📅 " + dateStr);

    // Add title
    QFont titleFont("Helvetica", 18, QFont::Bold);
    painter.setFont(titleFont);
    painter.drawText(QRect(0, y, pdf.width(), 100), Qt::AlignCenter, "Rapport des Ressources");
    y += 260;

    // Add chart
    QPixmap chartPixmap = gestionRessources.genererGraph();
    if (!chartPixmap.isNull()) {
        int chartWidth = pdf.width() - 120;
        QPixmap scaledChart = chartPixmap.scaledToWidth(chartWidth, Qt::SmoothTransformation);
        painter.drawPixmap(60, y, scaledChart);
        y += scaledChart.height() + 120;
    }
    QSqlQuery query;
    // Add low stock resources
    painter.setFont(QFont("Helvetica", 13, QFont::Bold));
    painter.setPen(QPen(Qt::darkRed));
    painter.drawText(60, y, "⚠ Ressources en faible stock (< 4)");
    y += 80;
    painter.setFont(QFont("Helvetica", 11));
    painter.setPen(Qt::black);
    if (query.exec("SELECT NOM_RESSOURCE, CATEGORIE, QUANTITE, FOURNISSEUR FROM RESSOURCES WHERE QUANTITE < 4 AND ETAT = 'Disponible' ")) {
        while (query.next()) {
            QString line = QString("Nom: %1 | Catégorie: %2 | Quantité: %3 | Fournisseur: %4")
                               .arg(query.value(0).toString())
                               .arg(query.value(1).toString())
                               .arg(query.value(2).toInt())
                               .arg(query.value(3).toInt());

            QFontMetrics metrics(painter.font());
            int textWidth = metrics.horizontalAdvance(line);
            QRect bgRect(50, y - 15, textWidth + 20, 25);
            painter.fillRect(bgRect, QColor(255, 200, 200));
            painter.drawText(50, y, line);
            y += 75;
            painter.setPen(Qt::darkCyan);
            painter.drawText(60, y, "🔁 Pensez à réapprovisionner cette ressource");
            painter.setPen(Qt::black);
            y += 85;
        }
    }
    // Add average quantity by category
    if (query.exec("SELECT AVG(total) FROM (SELECT SUM(QUANTITE) AS total FROM RESSOURCES GROUP BY CATEGORIE)")) {
        if (query.next()) {
            double moyenne = query.value(0).toDouble();
            painter.setFont(QFont("Helvetica", 11));
            painter.setPen(Qt::darkMagenta);
            painter.drawText(60, y, QString("📊 Moyenne des quantités par catégorie : %1").arg(QString::number(moyenne, 'f', 2)));
            y += 80;
        }
    }
    // Add total suppliers
    if (query.exec("SELECT COUNT(DISTINCT FOURNISSEUR) FROM RESSOURCES")) {
        if (query.next()) {
            int fournisseurs = query.value(0).toInt();
            painter.setPen(Qt::black);
            painter.setFont(QFont("Helvetica", 11));
            painter.drawText(60, y, QString("📌 Nombre de fournisseurs enregistrés : %1").arg(fournisseurs));
            y += 80;
        }
    }
    // Add total resources
    y += 20;
    painter.setPen(Qt::black);
    painter.drawLine(50, y, pdf.width() - 50, y);
    y += 60;

    if (query.exec("SELECT SUM (QUANTITE) FROM RESSOURCES ")) {
        if (query.next()) {
            int total = query.value(0).toInt();
            painter.drawText(60, y, QString("📦 Nombre total de ressources: %1").arg(total));
        }
    }
    y += 80;

    // Add weekly tip
    QStringList tips = {
        "💡 Conseil du jour: Rangez les ressources technologiques dans un endroit sec pour prolonger leur durée de vie.",
        "💡 Conseil du jour: Faites tourner les stocks pour utiliser d’abord les anciennes ressources.",
        "💡 Conseil du jour: Organisez les ressources par catégorie pour un accès rapide.",
        "💡 Conseil du jour: Effectuez une vérification mensuelle de l’état des ressources.",
        "💡 Conseil du jour: Conservez une trace numérique des entrées et sorties de stock.",
        "💡 Conseil du jour: Nettoyez régulièrement les équipements pour éviter l'accumulation de poussière.",
        "💡 Conseil du jour: Étiquetez clairement les ressources pour éviter les confusions.",
        "💡 Conseil du jour: Formez votre équipe à l'utilisation correcte des ressources pour réduire les dommages.",
        "💡 Conseil du jour: Planifiez des audits réguliers pour vérifier l'état des ressources.",
        "💡 Conseil du jour: Réparez immédiatement les équipements endommagés pour éviter des coûts plus élevés.",
        "💡 Conseil du jour: Stockez les ressources inflammables dans des zones sécurisées.",
        "💡 Conseil du jour: Utilisez des logiciels de gestion pour suivre les stocks en temps réel.",
        "💡 Conseil du jour: Évitez de surcharger les espaces de stockage pour réduire les risques d'accidents.",
        "💡 Conseil du jour: Vérifiez les dates d'expiration des ressources périssables.",
        "💡 Conseil du jour: Investissez dans des équipements de qualité pour une meilleure durabilité.",
        "💡 Conseil du jour: Réduisez les déchets en recyclant les ressources inutilisées."
    };
    QString tip = tips.at(QRandomGenerator::global()->bounded(tips.size()));
    painter.setFont(QFont("Helvetica", 11));
    painter.setPen(Qt::darkYellow);
    painter.drawText(60, y, tip);

    painter.end();
    QMessageBox::information(this, "PDF", "PDF généré avec succès !");
}

void MainWindow::on_statpb_clicked()
{
    QPieSeries* series = gestionRessources.stat();
    int total = 0;
    for (auto slice : series->slices()) {
        total += slice->value();
    }
    QMap<QString, QColor> categoryColors = {
        {"Eclairage", QColor(78, 23, 100)},    // Deep Purple (#4e1764)
        {"Technologie", QColor(168, 50, 121)}, // Magenta (#a83279)
        {"Papeterie", QColor(255, 148, 84)},   // Orange (#FF9454)
        {"Nettoyage", QColor(167, 181, 254)},  // Light Blue (#A7B5FE)
        {"Mobilier", QColor(32, 30, 75)},      // Coral (#201E4B)
        {"Electrique", QColor(146, 195, 165)},   // Dark Purple (#009688)
        {"Outils", QColor(255, 235, 174)},     // Yellow (#FFEBAE)
        {"Autre",QColor(0, 150, 136) }       // Cyan (#92C3A5)
    };
    // Assign colors and labels based on category
    for (int i = 0; i < series->count(); i++) {
        QPieSlice* slice = series->slices().at(i);
        // Ensure the slice label matches the category name
        QString category = slice->label().trimmed(); // Trim any extra spaces
        if (categoryColors.contains(category)) {
            slice->setBrush(categoryColors[category]);
        } else {
            slice->setBrush(Qt::gray); // Default color for unknown categories
            qDebug() << "Unknown category:" << category;
        }
        QString originalCategory = category;

        // Calculate and set percentage label for the slice
        double percentage = (slice->value() / total) * 100.0;
        slice->setLabel(QString("%1%").arg(QString::number(percentage, 'f', 1))); // Only percentage in the slice label
        slice->setProperty("categoryName", originalCategory); // Store original name as property
        slice->setLabelVisible(true);
        slice->setLabelFont(QFont("Arial", 12, QFont::Bold));
        // Add hover effect
        connect(slice, &QPieSlice::hovered, [slice](bool state) {
            slice->setExploded(state);
            slice->setExplodeDistanceFactor(state ? 0.1 : 0);
        });
    }
    QChart* chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Statistiques Des Catégories");
    chart->setTitleFont(QFont("Arial", 16, QFont::Bold));
    chart->setBackgroundBrush(QBrush(Qt::white));
    chart->setAnimationOptions(QChart::SeriesAnimations);
    // Customize legend to only show category names
    QLegend* legend = chart->legend();
    legend->setVisible(true);
    legend->setAlignment(Qt::AlignRight);
    legend->setFont(QFont("Arial", 12));
    // Update legend labels to only show category names
    QList<QLegendMarker*> legendMarkers = legend->markers(series);
    for (int i = 0; i < legendMarkers.size(); i++) {
        QLegendMarker* marker = legendMarkers.at(i);
        QPieSlice* slice = series->slices().at(i);
        QString categoryName = slice->property("categoryName").toString();
        marker->setLabel(categoryName);
    }
    QChartView* chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    chartView->setMinimumSize(550, 400); // Adjust to a readable size
    chartView->setBackgroundBrush(Qt::transparent); // Ensure the chart itself is transparent
    // Create a QWidget with layout to control spacing
    QWidget* containerWidget = new QWidget;
    QVBoxLayout* layout = new QVBoxLayout(containerWidget);
    layout->setContentsMargins(0, 37, 0, 0); // Top margin = 30px space before chart
    layout->addWidget(chartView);
    containerWidget->setStyleSheet("background: transparent;"); // Make sure container has no background
    QGraphicsProxyWidget* proxy = new QGraphicsProxyWidget();
    proxy->setWidget(containerWidget);
    QGraphicsScene* scene = new QGraphicsScene();
    scene->setBackgroundBrush(Qt::transparent); // Set transparent background for scene
    scene->addItem(proxy); // Add the whole widget with spacing
    ui->acceuil2->setScene(scene);
}

void MainWindow::on_refresh_clicked()
{
    ui->recherche->clear();
    fillTab();
    ui->rechercheCb->setCurrentIndex(0);
}

void MainWindow::handleAlertNotification(const QString &message, const QString &type)
{
    if (type == "low_stock") {
        // 🔊 Play alert sound
        QMediaPlayer* player = new QMediaPlayer(this);
        QAudioOutput* audioOutput = new QAudioOutput(this);
        player->setAudioOutput(audioOutput);
        player->setSource(QUrl("qrc:/ressources/sounds/notif.wav"));  // Place sound in resources or use absolute path
        audioOutput->setVolume(0.7); // Optional: adjust volume
        player->play();

        // 🟥 Red popup for low stock
        QColor color = QColor(255, 99, 71);

        QWidget *popup = new QWidget();
        popup->setWindowFlags(Qt::FramelessWindowHint | Qt::ToolTip);
        popup->setAttribute(Qt::WA_DeleteOnClose);
        popup->setStyleSheet(QString("background-color: %1; color: white; border-radius: 6px;").arg(color.name()));
        popup->resize(300, 60);

        QLabel *label = new QLabel(message, popup);
        label->setAlignment(Qt::AlignCenter);
        label->setWordWrap(true);
        label->setGeometry(10, 10, 280, 40);

        popup->move(this->x() + this->width() - popup->width() - 100, this->y() + 60 + popupOffset);
        popup->show();

        // Fade-out effect
        QPropertyAnimation *animation = new QPropertyAnimation(popup, "windowOpacity");
        animation->setDuration(1500);  // Shorter fade
        animation->setStartValue(1);
        animation->setEndValue(0);

        connect(animation, &QPropertyAnimation::finished, popup, &QWidget::close); // Close after fade
        QTimer::singleShot(5000, animation, SLOT(start()));

        alertHistory.append(message);
        popupOffset += 70;
        updateBellCount();
    }
}

void MainWindow::showAllAlerts()
{
    if (alertHistory.isEmpty()) {
        QMessageBox::information(this, "🔔 Historique des alertes", "✅ Aucun problème détecté !");
        return;
    }

    // Check if the history widget is already visible
    if (historyWidget && historyWidget->isVisible()) {
        historyWidget->close();
        return; // Close the history if it's already open
    }

    // Create a new history widget if not already created
    historyWidget = new QWidget(this);
    historyWidget->setWindowTitle("🕓 Historique des alertes");

    int baseHeight = 100;
    int alertHeight = 40;
    int totalHeight = baseHeight + alertHistory.size() * alertHeight;
    historyWidget->setFixedSize(360, std::min(totalHeight, 500));  // Cap max height

    historyWidget->setStyleSheet("background-color: #f0f0f0;");

    QVBoxLayout* mainLayout = new QVBoxLayout(historyWidget);

    QScrollArea* scrollArea = new QScrollArea(historyWidget);
    QWidget* alertContainer = new QWidget();
    QVBoxLayout* alertLayout = new QVBoxLayout(alertContainer);

    for (int i = 0; i < alertHistory.size(); ++i) {
        QString alert = alertHistory[i];

        QWidget* rowWidget = new QWidget(alertContainer);
        QHBoxLayout* rowLayout = new QHBoxLayout(rowWidget);
        rowLayout->setContentsMargins(5, 0, 5, 0);

        QLabel* alertLabel = new QLabel(alert, rowWidget);
        alertLabel->setWordWrap(true);
        QPushButton* removeBtn = new QPushButton("❌", rowWidget);
        removeBtn->setFixedSize(24, 24);
        removeBtn->setStyleSheet("color: red; background: transparent; border: none; font-weight: bold;");

        connect(removeBtn, &QPushButton::clicked, [=]() {
            alertHistory.removeAt(i);
            updateBellCount();
            historyWidget->close();
            showAllAlerts(); // Refresh list
        });

        rowLayout->addWidget(alertLabel);
        rowLayout->addStretch();
        rowLayout->addWidget(removeBtn);
        rowWidget->setLayout(rowLayout);
        alertLayout->addWidget(rowWidget);
    }

    alertContainer->setLayout(alertLayout);
    scrollArea->setWidget(alertContainer);
    scrollArea->setWidgetResizable(true);
    mainLayout->addWidget(scrollArea);

    // Clear All Button
    QPushButton* clearAll = new QPushButton("🗑️ Tout effacer", historyWidget);
    clearAll->setStyleSheet("background-color: #e74c3c; color: white; padding: 6px 12px; border-radius: 6px;");
    connect(clearAll, &QPushButton::clicked, [=]() {
        alertHistory.clear();
        updateBellCount();
        historyWidget->close();
    });
    mainLayout->addWidget(clearAll, 0, Qt::AlignRight);

    historyWidget->setLayout(mainLayout);
    historyWidget->move(this->x() + this->width() - historyWidget->width() - 20, this->y() + 100); // Top-right

    historyWidget->show();
}

void MainWindow::onClearAlertsClicked()
{
    alertHistory.clear();
}

void MainWindow::updateBellCount()
{
    int alertCount = alertHistory.size();
    ui->bellIcon->setText(QString("🔔 %1").arg(alertCount));  // Adding the bell emoji and count
    ui->bellIcon->setVisible(alertCount > 0);  // Only show the bell if there's at least one alert
}

void MainWindow::on_bellIcon_clicked()
{
    if (alertHistory.isEmpty()) {
        return; // Don't do anything if there are no alerts
    }

    // Check if the history is already open. If it is, close it.
    if (historyWidget && historyWidget->isVisible()) {
        historyWidget->close();
    } else {
        // Otherwise, show the alert history
        showAllAlerts();
    }
}

void MainWindow::handleDecrement() {
    qDebug() << "Received DECREMENT request from Arduino";
    int oldQty = gestionRessources.getScannerQuantity();
    qDebug() << "Quantity before decrement:" << oldQty;

    if (gestionRessources.decrementScannerQuantity()) {
        QString name = gestionRessources.getScannerName();
        int newQty = gestionRessources.getScannerQuantity();
        qDebug() << "Quantity after decrement:" << newQty;
        arduino->sendData(name, newQty); // Send updated quantity to Arduino
        qDebug() << "→ Sent to Arduino after decrement:" << QString("SET:%1:%2\n").arg(name).arg(newQty).trimmed();

        // Refresh the UI
        fillTab();

        // Check for low stock alert
        QList<QPair<QString, QString>> alerts = gestionRessources.checkAlerts();
        for (const auto& alert : alerts) {
            handleAlertNotification(alert.first, alert.second);
        }

        QMessageBox::information(this, "Succès", "Quantité de scanner décrémentée !");
    } else {
        qDebug() << "Failed to decrement scanner quantity: " << gestionRessources.getScannerQuantity();
        QMessageBox::warning(this, "Erreur", "Échec de la mise à jour de la quantité du scanner !");
    }
}
// ------------------------- GESTION DES ARCHITECTES -------------------------------- \\


// Update the fillTableWidget method to ensure proper data storage for sorting
void MainWindow::fillTableWidget() {
    QSqlQueryModel *model = emp.afficher();  // Fetch the data from the database.

    // Clear the existing table content
    ui->tableWidget->clearContents();
    ui->tableWidget->setRowCount(0);
    ui->tableWidget->setColumnCount(8); // 8 columns

    // Set column headers
    ui->tableWidget->setHorizontalHeaderLabels({"ID", "Nom", "Prenom", "Date", "Poste", "Email", "Salaire", "Sexe"});

    for (int row = 0; row < model->rowCount(); ++row) {
        ui->tableWidget->insertRow(row);

        // ID (QString)
        QTableWidgetItem *idItem = new QTableWidgetItem(model->data(model->index(row, 0)).toString());

        // Nom
        QTableWidgetItem *nomItem = new QTableWidgetItem(model->data(model->index(row, 1)).toString());

        // Prenom
        QTableWidgetItem *prenomItem = new QTableWidgetItem(model->data(model->index(row, 2)).toString());

        // Date (QDate for proper sorting)
        QDate dateValue = model->data(model->index(row, 6)).toDate();
        QTableWidgetItem *dateItem = new QTableWidgetItem(dateValue.toString("yyyy-MM-dd"));
        dateItem->setData(Qt::UserRole, dateValue);  // Store actual date for sorting

        // Poste
        QTableWidgetItem *posteItem = new QTableWidgetItem(model->data(model->index(row, 4)).toString());

        // Email
        QTableWidgetItem *emailItem = new QTableWidgetItem(model->data(model->index(row, 3)).toString());

        // Salaire (double/float for proper sorting)
        double salaireValue = model->data(model->index(row, 7)).toDouble();
        QTableWidgetItem *salaireItem = new QTableWidgetItem(QString::number(salaireValue, 'f', 2));
        salaireItem->setData(Qt::UserRole, salaireValue);  // Store actual numeric value for sorting

        // Sexe
        QTableWidgetItem *sexeItem = new QTableWidgetItem(model->data(model->index(row, 5)).toString());

        // Insert all items into the table
        ui->tableWidget->setItem(row, 0, idItem);
        ui->tableWidget->setItem(row, 1, nomItem);
        ui->tableWidget->setItem(row, 2, prenomItem);
        ui->tableWidget->setItem(row, 3, dateItem);
        ui->tableWidget->setItem(row, 4, posteItem);
        ui->tableWidget->setItem(row, 5, emailItem);
        ui->tableWidget->setItem(row, 6, salaireItem);
        ui->tableWidget->setItem(row, 7, sexeItem);
    }

    // Enable sorting by clicking headers
    ui->tableWidget->setSortingEnabled(true);
    ui->tableWidget->resizeColumnsToContents();
}



void MainWindow::on_refreshButton_clicked()
{
    ui->id_rech->clear(); // Clear 'id' field
    ui->nom->clear(); // Clear 'nom' field
    ui->prenom->clear(); // Clear 'prenom' field
    ui->email->clear(); // Clear 'email' field
    ui->salaire->clear(); // Clear 'salaire' field
    ui->poste->setCurrentIndex(0); // Reset combo box (set to default/first item)
    ui->homme->setChecked(false); // Uncheck 'homme' radio button
    ui->femme_2->setChecked(false); // Uncheck 'femme' radio button
    ui->date_emboche->setDate(QDate::currentDate()); // Reset date field to current date
}


void MainWindow::on_refreshButton2_clicked()
{
    ui->id_p->clear(); // Clear 'id' field
    ui->nom_conge->clear(); // Clear 'nom' field
    ui->prenom_conge->clear(); // Clear 'prenom' field
    ui->email_conge->clear(); // Clear 'email' field
    ui->raison_conge->clear(); // Clear 'salaire' field
    ui->poste_conge->clear(); // Reset combo box (set to default/first item)
    ui->date_debut->setDate(QDate::currentDate()); // Uncheck 'homme' radio button
    ui->date_fin->setDate(QDate::currentDate()); // Reset date field to current date
}


void MainWindow::on_addEmployeeButton_clicked()
{
    // Validate 'nom'
    if (ui->nom->text().isEmpty()) {
        QMessageBox::warning(this, "Input Error", "Nom vide !!");
        return;
    }

    // Validate 'prenom'
    if (ui->prenom->text().isEmpty()) {
        QMessageBox::warning(this, "Input Error", "Prenom vide !!");
        return;
    }

    // Validate 'email' format using regex
    QString email = ui->email->text();
    QRegularExpression emailRegex(R"((\w+)(\.?[\w-]+)*@([\w-]+\.)+[\w-]{2,})");
    QRegularExpressionValidator emailValidator(emailRegex);
    int emailPos = 0;
    if (ui->email->text().isEmpty() || emailValidator.validate(email, emailPos) != QValidator::Acceptable) {
        QMessageBox::warning(this, "Input Error", "Email vide ou invalide !!");
        return;
    }

    // Validate 'salaire' input is numeric
    bool salaireOk;
    double salaire = ui->salaire->text().toDouble(&salaireOk);
    if (!salaireOk || salaire <= 0) {
        QMessageBox::warning(this, "Input Error", "Salaire vide ou invalide !!");
        return;
    }

    if (ui->poste->currentText() == "choisir poste") {
        QMessageBox::warning(this, "Input Error", "Choisir un poste valide.");
        return;
    }

    // Validate 'genre' selection
    if (!ui->homme->isChecked() && !ui->femme_2->isChecked()) {
        QMessageBox::warning(this, "Input Error", "Choisir votre genre.");
        return;
    }

    // Get values from UI elements and set to the 'Employe' object
    QString nom = ui->nom->text();
    QString prenom = ui->prenom->text();
    QString sexe = ui->homme->isChecked() ? "M" : "F"; // Radio buttons for male/female
    QString poste = ui->poste->currentText();
    emp.date_embauche = ui->date_emboche->date(); // Date from QDateEdit widget

    // Set employee attributes
    emp.setNom(nom);
    emp.setPrenom(prenom);
    emp.setSexe(sexe);
    emp.setEmail(email);
    emp.setSalaire(salaire);
    emp.setPoste(poste);

    // Optionally, add employee to database
    if (emp.ajouter()) {  // Assuming you have an ajouter() function to add the employee to the database
        QMessageBox::information(this, "Success", "Employé ajouté avec succès.");
        fillTableWidget(); // Refresh the table widget

        // Reset all form fields
        ui->nom->clear(); // Clear 'nom' field
        ui->prenom->clear(); // Clear 'prenom' field
        ui->email->clear(); // Clear 'email' field
        ui->salaire->clear(); // Clear 'salaire' field
        ui->poste->setCurrentIndex(0); // Reset combo box (set to default/first item)
        ui->homme->setChecked(false); // Uncheck 'homme' radio button
        ui->femme_2->setChecked(false); // Uncheck 'femme' radio button
        ui->date_emboche->setDate(QDate::currentDate()); // Reset date field to current date
    } else {
        QMessageBox::warning(this, "Error", "Échec de l'ajout de l'employé.");
    }
}





void MainWindow::on_modifyEmployeeButton_clicked()
{
    // Retrieve the employee ID from a selected row or an input field
    QString id = ui->id_rech->text();
    if (id.isEmpty()) {
        QMessageBox::warning(this, "Input Error", "L'ID pour modifier est vide.");
        return;
    }

    // Get values from UI elements for each field
    QString nom = ui->nom->text();
    QString prenom = ui->prenom->text();
    QString sexe = ui->homme->isChecked() ? "M" : (ui->femme_2->isChecked() ? "F" : "");
    QString email = ui->email->text();
    float salaire = ui->salaire->text().toFloat();
    QString poste = ui->poste->currentData().toString();
    QDate date_emboche = ui->date_emboche->date();

    // Call the modifier function with the collected values
    bool success = emp.modifier(nom, prenom, sexe, email, salaire, poste, date_emboche, id);
    bool exists = emp.idExists(id);

    if (exists) {
        if (success) {
            QMessageBox::information(this, "Success", "Information de l'employé modifiée avec succès.");
            fillTableWidget(); // Refresh the table widget
            ui->tableWidget->resizeColumnsToContents();  // Resize columns to fit content

            // Reset all form fields
            ui->id_rech->clear(); // Clear 'id' field
            ui->nom->clear(); // Clear 'nom' field
            ui->prenom->clear(); // Clear 'prenom' field
            ui->email->clear(); // Clear 'email' field
            ui->salaire->clear(); // Clear 'salaire' field
            ui->poste->setCurrentIndex(0); // Reset combo box (set to default/first item)
            ui->homme->setChecked(false); // Uncheck 'homme' radio button
            ui->femme_2->setChecked(false); // Uncheck 'femme' radio button
            ui->date_emboche->setDate(QDate::currentDate()); // Reset date field to current date

        } else {
            QMessageBox::warning(this, "Failure", "Échec de la modification des informations de l'employé.");
        }
    } else {
        QMessageBox::information(this, "Failure", "L'ID pour modifier n'existe pas.");
    }
}
void MainWindow::on_tableWidget_itemClicked(QTableWidgetItem *item)
{
    // Get the row index of the clicked item
    int row = item->row();

    // Retrieve the data from the clicked row for each column
    QString id = ui->tableWidget->item(row, 0)->text();  // "ID" is in the first column
    QString nom = ui->tableWidget->item(row, 1)->text();  // "Nom" is in the second column
    QString prenom = ui->tableWidget->item(row, 2)->text();  // "Prenom" is in the third column
    QDate date = QDate::fromString(ui->tableWidget->item(row, 3)->text(), "yyyy-MM-dd");  // "Date" is in the fourth column
    QString poste = ui->tableWidget->item(row, 4)->text();  // "Poste" is in the fifth column
    QString email = ui->tableWidget->item(row, 5)->text();  // "Email" is in the sixth column
    QString sexe = ui->tableWidget->item(row, 7)->text();  // "Sexe" is in the seventh column
    QString salaireText = ui->tableWidget->item(row, 6)->text();  // "Salaire" is in the eighth column

    // Debug: Print the value of salaireText to verify the raw string value
    qDebug() << "Salaire Text: " << salaireText;

    // Convert the string to a double (handle potential conversion errors)
    bool conversionOk;
    double salaire = salaireText.toDouble(&conversionOk);

    // Debug: Print the result of conversion
    if (conversionOk) {
        qDebug() << "Converted Salaire: " << salaire;
    } else {
        qDebug() << "Conversion failed, setting salary to 0";
        salaire = 0;  // Fallback to 0 if conversion fails
    }

    // Populate the corresponding UI fields with the selected row data
    ui->id_rech->setText(id);  // Set the ID in the id_rech QLineEdit
    ui->nom->setText(nom);
    ui->prenom->setText(prenom);
    ui->date_emboche->setDate(date);
    ui->poste->setCurrentText(poste);
    ui->email->setText(email);
    if (sexe == "M") {
        ui->homme->setChecked(true);  // Assuming you have radio buttons for "Male" and "Female"
    } else if (sexe == "F") {
        ui->femme_2->setChecked(true);
    }

    // Check if the salaire is valid before setting the QLineEdit
    if (conversionOk) {
        ui->salaire->setText(QString::number(salaire));  // Set the Salaire in the salaire QLineEdit
    } else {
        ui->salaire->setText("0");  // In case of an invalid salary, set it to "0"
    }
}
void MainWindow::refreshTableWidget() {
    // Fetch updated data from the database
    QSqlQueryModel *model = emp.afficher();  // Assuming 'emp.afficher()' returns a QSqlQueryModel with updated data.

    // Clear any existing data in the table widget
    ui->tableWidget->clearContents();
    ui->tableWidget->setRowCount(0);

    // Set the correct column count (ID + other fields)
    ui->tableWidget->setColumnCount(8);  // 8 columns (ID, Nom, Prenom, Date, Poste, Email, Salaire, Sexe)

    // Set the column headers
    ui->tableWidget->setHorizontalHeaderLabels({"ID", "Nom", "Prenom", "Date", "Poste", "Email", "Salaire", "Sexe"});

    // Populate the table with the data
    for (int row = 0; row < model->rowCount(); ++row) {
        ui->tableWidget->insertRow(row);

        // Set data for each column
        ui->tableWidget->setItem(row, 0, new QTableWidgetItem(model->data(model->index(row, 0)).toString())); // ID
        ui->tableWidget->setItem(row, 1, new QTableWidgetItem(model->data(model->index(row, 1)).toString())); // Nom
        ui->tableWidget->setItem(row, 2, new QTableWidgetItem(model->data(model->index(row, 2)).toString())); // Prenom
        ui->tableWidget->setItem(row, 3, new QTableWidgetItem(model->data(model->index(row, 3)).toString())); // Date
        ui->tableWidget->setItem(row, 4, new QTableWidgetItem(model->data(model->index(row, 4)).toString())); // Poste
        ui->tableWidget->setItem(row, 5, new QTableWidgetItem(model->data(model->index(row, 5)).toString())); // Email
        ui->tableWidget->setItem(row, 6, new QTableWidgetItem(model->data(model->index(row, 6)).toString())); // Salaire
        ui->tableWidget->setItem(row, 7, new QTableWidgetItem(model->data(model->index(row, 7)).toString())); // Sexe
    }

    // Resize the columns to fit the content
    ui->tableWidget->resizeColumnsToContents();
}
void MainWindow::displayCongeStatistics() {
    // 1. Récupération des données
    QMap<QString, int> stats = emp.getCongeStats();

    int accepteCount = stats.value("accepté", 0);
    int refuseCount = stats.value("refusé", 0);
    int total = accepteCount + refuseCount;

    qDebug() << "[Debug] Acceptés:" << accepteCount << "| Refusés:" << refuseCount;

    // 2. Cas où aucune donnée n'est disponible
    if (total == 0) {
        QGraphicsScene *scene = new QGraphicsScene();
        QLabel *label = new QLabel("Aucune donnée disponible\n(Vérifiez la connexion à la base ou les états des congés)");
        label->setAlignment(Qt::AlignCenter);
        label->setStyleSheet("font-size: 14px; color: #FF0000;");
        scene->addWidget(label);
        ui->pie->setScene(scene);
        return;
    }

    // 3. Création du diagramme circulaire
    QPieSeries *series = new QPieSeries();

    if (accepteCount > 0) {
        QPieSlice *acceptedSlice = series->append("Acceptés", accepteCount);
        acceptedSlice->setColor(QColor("#2ecc71")); // Vert
        acceptedSlice->setLabelVisible(true);
    }

    if (refuseCount > 0) {
        QPieSlice *refusedSlice = series->append("Refusés", refuseCount);
        refusedSlice->setColor(QColor("#e74c3c")); // Rouge
        refusedSlice->setLabelVisible(true);
    }

    // 4. Configuration des labels
    // Configuration des labels
    for (QPieSlice *slice : series->slices()) {
        double percentage = (slice->value() / total) * 100.0;
        QString labelText;

        if (slice->label().contains("Acceptés")) {
            labelText = QString("Congés acceptés - %1%").arg(percentage, 0, 'f', 1);
        } else if (slice->label().contains("Refusés")) {
            labelText = QString("Congés refusés - %1%").arg(percentage, 0, 'f', 1);
        } else {
            labelText = QString("%1%").arg(percentage, 0, 'f', 1);
        }

        slice->setLabel(labelText);
    }


    // 5. Création du graphique
    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Statistiques des congés");
    chart->legend()->setAlignment(Qt::AlignRight);
    chart->setAnimationOptions(QChart::AllAnimations);

    // 6. Affichage dans la scène
    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    chartView->setMinimumSize(600, 450);

    QGraphicsScene *scene = new QGraphicsScene();
    scene->addWidget(chartView);
    ui->pie->setScene(scene);
    ui->pie->show();
}

/*void MainWindow::on_rechercherButton_clicked() {
    QString idText = ui->id_rech->text().trimmed();
    bool ok;
    int id = idText.toInt(&ok);

    if (!ok || idText.isEmpty()) {
        QMessageBox::warning(this, "Erreur", "ID invalide !");
        return;
    }

    Architecte arch;
    if (arch.fetchById(id)) {
        // Peupler les champs
        ui->nom->setText(arch.getNom());
        ui->prenom->setText(arch.getPrenom());
        ui->email->setText(arch.getEmail());
        ui->salaire->setText(QString::number(arch.getSalaire()));
        ui->poste->setCurrentText(arch.getPoste());
        ui->date_emboche->setDate(arch.getDateEmbauche());

        // Gérer le genre
        if (arch.getSexe() == "M") {
            ui->homme->setChecked(true);
            ui->femme_2->setChecked(false);
        } else {
            ui->homme->setChecked(false);
            ui->femme_2->setChecked(true);
        }
    } else {
        QMessageBox::information(this, "Recherche", "Aucun architecte trouvé avec cet ID.");
}

}*/

void MainWindow::on_rechercherButton_clicked() {
    QString searchText = ui->id_rech->text().trimmed();
    QString searchCriteria = ui->rechercheCb->currentText();
    QSqlQuery query;

    if (searchText.isEmpty()) {
        query.prepare("SELECT * FROM ARCHITECTES");
    } else {
        if (searchCriteria == "ID") {
            query.prepare("SELECT * FROM ARCHITECTES WHERE ID_ARCHITECTE = :searchText");
            query.bindValue(":searchText", searchText.toInt());
        } else if (searchCriteria == "Nom") {
            query.prepare("SELECT * FROM ARCHITECTES WHERE LOWER(NOM) LIKE LOWER(:searchText)");
            query.bindValue(":searchText", "%" + searchText + "%");
        } else if (searchCriteria == "Prénom") {
            query.prepare("SELECT * FROM ARCHITECTES WHERE LOWER(PRENOM) LIKE LOWER(:searchText)");
            query.bindValue(":searchText", "%" + searchText + "%");
        } else if (searchCriteria == "Email") {
            query.prepare("SELECT * FROM ARCHITECTES WHERE LOWER(EMAIL) LIKE LOWER(:searchText)");
            query.bindValue(":searchText", "%" + searchText + "%");
        } else if (searchCriteria == "Poste") {
            query.prepare("SELECT * FROM ARCHITECTES WHERE LOWER(POSTE) LIKE LOWER(:searchText)");
            query.bindValue(":searchText", "%" + searchText + "%");
        } else if (searchCriteria == "Sexe") {
            query.prepare("SELECT * FROM ARCHITECTES WHERE SEXE = :searchText");
            query.bindValue(":searchText", searchText);
        } else if (searchCriteria == "Date") {
            query.prepare("SELECT * FROM ARCHITECTES WHERE DATE_EMBAUCHE LIKE :searchText");
            query.bindValue(":searchText", "%" + searchText + "%");
        } else {
            QMessageBox::warning(this, "Erreur", "Critère de recherche invalide.");
            return;
        }
    }

    if (!query.exec()) {
        qDebug() << "Erreur requête:" << query.lastError().text();
        QMessageBox::warning(this, "Erreur", "Erreur lors de l'exécution de la recherche.");
        return;
    }

    ui->tableWidget->setRowCount(0);
    ui->tableWidget->setColumnCount(8);
    QStringList headers = {"ID", "Nom", "Prénom", "Date", "Poste", "Email", "Salaire", "Sexe"};
    ui->tableWidget->setHorizontalHeaderLabels(headers);

    int row = 0;
    while (query.next()) {
        ui->tableWidget->insertRow(row);
        ui->tableWidget->setItem(row, 0, new QTableWidgetItem(query.value("ID_ARCHITECTE").toString()));
        ui->tableWidget->setItem(row, 1, new QTableWidgetItem(query.value("NOM").toString()));
        ui->tableWidget->setItem(row, 2, new QTableWidgetItem(query.value("PRENOM").toString()));
        ui->tableWidget->setItem(row, 3, new QTableWidgetItem(query.value("DATE_EMBAUCHE").toString()));
        ui->tableWidget->setItem(row, 4, new QTableWidgetItem(query.value("POSTE").toString()));
        ui->tableWidget->setItem(row, 5, new QTableWidgetItem(query.value("EMAIL").toString()));
        ui->tableWidget->setItem(row, 6, new QTableWidgetItem(query.value("SALAIRE").toString()));
        ui->tableWidget->setItem(row, 7, new QTableWidgetItem(query.value("SEXE").toString()));
        row++;
    }

    ui->tableWidget->resizeColumnsToContents();
    qDebug() << "Recherche exécutée sur critère:" << searchCriteria << ", texte:" << searchText;

    // Connect the selection model to handle row selection
    connect(ui->tableWidget->selectionModel(), &QItemSelectionModel::selectionChanged, this, &MainWindow::onRowSelected);
}

void MainWindow::onRowSelected() {
    // Get the index of the selected row
    QModelIndexList selectedIndexes = ui->tableWidget->selectionModel()->selectedRows();

    if (!selectedIndexes.isEmpty()) {
        // Get the first selected row
        int selectedRow = selectedIndexes.first().row();

        // Highlight the selected row
        ui->tableWidget->selectRow(selectedRow);

        // Optionally, you can add additional logic here to highlight or update the row's appearance
        qDebug() << "Row " << selectedRow << " selected.";
    }
}


void MainWindow::on_comboBox_tri_3_currentIndexChanged(int index) {
    const int DATE_COLUMN = 3; // Colonne de la date dans le QTableWidget

    Qt::SortOrder order = Qt::DescendingOrder; // Par défaut : décroissant

    if (index == 1) { // Si "Date croissante" est sélectionné
        order = Qt::AscendingOrder;
    }

    ui->tableWidget->sortItems(DATE_COLUMN, order);
}

// Sorts table based on the comboBox_tri_3 selected criteria
void MainWindow::on_triCb_currentIndexChanged(int index)
{
    Q_UNUSED(index);

    QString criteria = ui->comboBox_tri_3->currentText();
    int columnIndex = -1;

    if (criteria == "Date d'embauche") columnIndex = 3;
    else if (criteria == "Salaire") columnIndex = 6;
    else if (criteria == "Sexe") columnIndex = 7;

    if (columnIndex != -1) {
        // Before sorting, make sure the UserRole is set for the date column
        if (columnIndex == 3) { // Only do this for the date column
            for (int row = 0; row < ui->tableWidget->rowCount(); ++row) {
                QTableWidgetItem* item = ui->tableWidget->item(row, columnIndex);
                if (item) {
                    QDate date = QDate::fromString(item->text(), "dd/MM/yyyy");
                    item->setData(Qt::UserRole, date);
                }
            }
        }

        ui->tableWidget->sortItems(columnIndex, isAscending ? Qt::AscendingOrder : Qt::DescendingOrder);
    }
}

void MainWindow::on_triButton_2_clicked()
{
    static bool isButtonClicked = false;
    if (isButtonClicked) return;

    isButtonClicked = true;
    QTimer::singleShot(300, [this]() {
        isButtonClicked = false;
    });

    isAscending = !isAscending;
    on_triCb_currentIndexChanged(ui->comboBox_tri_3->currentIndex());

    ui->triButton->setIcon(QIcon(isAscending
                                     ? "C:/Users/onsna/OneDrive/Desktop/Projet C++/Architechtes/Architechtes_interface/Architechtes_interface/images/ascending.png"
                                     : "C:/Users/onsna/OneDrive/Desktop/Projet C++/Architechtes/Architechtes_interface/Architechtes_interface/images/descending.png"));
}

void MainWindow::on_pdf_2_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(this, "Enregistrer le PDF", "", "PDF Files (*.pdf)");
    if (fileName.isEmpty()) return;
    if (!fileName.endsWith(".pdf")) fileName += ".pdf";

    QPdfWriter pdf(fileName);
    pdf.setPageSize(QPageSize(QPageSize::A4));
    pdf.setResolution(300);
    pdf.setPageMargins(QMargins(50, 50, 50, 50));

    QPainter painter(&pdf);
    if (!painter.isActive()) {
        QMessageBox::warning(this, "Erreur", "Impossible de créer le fichier PDF.");
        return;
    }

    int y = 80; // Position verticale initiale

    // Logo aligné à gauche
    QPixmap logo("C:/Users/onsna/OneDrive/Desktop/Projet C++/Architechtes/Architechtes_interface/Architechtes_interface/images/Logo.png");
    if (!logo.isNull()) {
        painter.drawPixmap( -300, -400, logo.scaledToHeight(150, Qt::SmoothTransformation));
    }

    // Date en haut à gauche
    QFont dateFont("Helvetica", 11);
    painter.setFont(dateFont);
    QString dateStr = QDate::currentDate().toString("dd/MM/yyyy");

    // Calculate text width to align properly
    QFontMetrics dateMetrics(dateFont);
    int dateWidth = dateMetrics.horizontalAdvance("📅 " + dateStr);

    // Position calculation:
    // pdf.width() = total page width (A4 width in pixels at 300 DPI ≈ 2480 pixels)
    // Right margin = 50 (as set in pdf.setPageMargins)
    // So, X position = pageWidth - rightMargin - textWidth
    int dateX = pdf.width() - dateWidth - -300; // 50 is the right margin
    int dateY = -300; // Top margin (adjust if needed)

    painter.drawText(dateX, dateY, "📅 " + dateStr);
    // Titre principal
    QFont titleFont("Helvetica", 20, QFont::Bold);
    painter.setFont(titleFont);
    painter.setPen(QColor(85, 0, 127));
    painter.drawText(QRect(0, y, pdf.width(), 100), Qt::AlignCenter, "Liste des Architectes");
    y += 300;

    // Configuration du tableau
    QFont headerFont("Helvetica", 12, QFont::Bold);
    QFont contentFont("Helvetica", 11);
    painter.setFont(contentFont);

    int rowHeight = 100; // Hauteur de ligne augmentée
    QStringList headers = {"ID", "Nom", "Prénom", "Date", "Poste", "Email", "Salaire", "Sexe"};
    int totalWidth = pdf.width() - 100;

    // Distribution des colonnes (identique au style ressources)
    QVector<int> columnWidths = {
        static_cast<int>(totalWidth * 0.12),  // ID (5%)
        static_cast<int>(totalWidth * 0.30),  // Nom (12%)
        static_cast<int>(totalWidth * 0.35),  // Prénom (12%)
        static_cast<int>(totalWidth * 0.25),  // Date (7%)
        static_cast<int>(totalWidth * 0.25),  // Poste (10%)
        static_cast<int>(totalWidth * 0.40),  // Email (35%)
        static_cast<int>(totalWidth * 0.20),  // Salaire (10%)
        static_cast<int>(totalWidth * 0.12)   // Sexe (9%)
    };

    int leftMargin = -525;
    int yOffset = y;

    // Dessin de l'en-tête
    auto drawHeaderRow = [&]() {
        painter.setFont(headerFont);
        painter.setPen(QColor(0, 102, 204));
        painter.setBrush(QColor(220, 220, 250));

        int x = leftMargin;
        for (int col = 0; col < headers.size(); ++col) {
            QRect cellRect(x, yOffset, columnWidths[col], rowHeight);
            painter.fillRect(cellRect, QColor(220, 220, 250));
            painter.drawRect(cellRect);
            painter.drawText(cellRect, Qt::AlignCenter, headers[col]);
            x += columnWidths[col];
        }
    };

    drawHeaderRow();
    yOffset += rowHeight;

    // Données du tableau
    painter.setFont(contentFont);
    painter.setPen(Qt::black);

    for (int row = 0; row < ui->tableWidget->rowCount(); ++row) {
        // Fond alterné
        if (row % 2 == 0) {
            painter.fillRect(QRect(leftMargin, yOffset, totalWidth, rowHeight), QColor(245, 245, 245));
        }

        int x = leftMargin;
        for (int col = 0; col < headers.size(); ++col) {
            QString text = ui->tableWidget->item(row, col) ? ui->tableWidget->item(row, col)->text() : "";
            QRect cellRect(x, yOffset, columnWidths[col], rowHeight);

            painter.drawRect(cellRect);
            painter.drawText(cellRect.adjusted(8, 4, -8, -4),
                             Qt::AlignLeft | Qt::AlignVCenter | Qt::TextWordWrap,
                             text);
            x += columnWidths[col];
        }

        yOffset += rowHeight;

        // Gestion des sauts de page
        if (yOffset + rowHeight > pdf.height() - 100) {
            pdf.newPage();
            yOffset = 100;
            drawHeaderRow();
            yOffset += rowHeight;
        }
    }

    painter.end();
    QMessageBox::information(this, "Succès", "Le fichier PDF a été exporté avec succès !");
}
bool MainWindow::customTableWidgetItemCompare(QTableWidgetItem* item1, QTableWidgetItem* item2)
{
    // Compare as numbers
    bool ok1, ok2;
    double num1 = item1->text().toDouble(&ok1);
    double num2 = item2->text().toDouble(&ok2);
    if (ok1 && ok2) return num1 < num2;

    // Compare as dates
    QDate date1 = QDate::fromString(item1->text(), "yyyy-MM-dd");
    QDate date2 = QDate::fromString(item2->text(), "yyyy-MM-dd");
    if (date1.isValid() && date2.isValid()) return date1 < date2;

    // Fallback to string
    return item1->text() < item2->text();
}

void MainWindow::on_tableWidget_sortIndicatorChanged(int logicalIndex, Qt::SortOrder order)
{
    Q_UNUSED(order);

    QString criteria = ui->comboBox_tri_3->currentText();
    if ((criteria == "Date d'embauche" && logicalIndex == 3) ||
        (criteria == "Salaire" && logicalIndex == 6) ||
        (criteria == "Sexe" && logicalIndex == 7))
    {
        ui->tableWidget->setSortingEnabled(false);

        int column = logicalIndex;
        QList<QPair<QTableWidgetItem*, int>> indexedItems;

        for (int i = 0; i < ui->tableWidget->rowCount(); ++i) {
            indexedItems.append({ui->tableWidget->item(i, column), i});
        }

        std::sort(indexedItems.begin(), indexedItems.end(),
                  [this](const QPair<QTableWidgetItem*, int>& a, const QPair<QTableWidgetItem*, int>& b) {
                      return isAscending
                                 ? customTableWidgetItemCompare(a.first, b.first)
                                 : customTableWidgetItemCompare(b.first, a.first);
                  });

        // Store full row data
        QList<QList<QTableWidgetItem*>> sortedRows;
        for (const auto& pair : indexedItems) {
            QList<QTableWidgetItem*> rowItems;
            for (int col = 0; col < ui->tableWidget->columnCount(); ++col) {
                QTableWidgetItem *original = ui->tableWidget->item(pair.second, col);
                rowItems.append(original ? original->clone() : new QTableWidgetItem(""));
            }
            sortedRows.append(rowItems);
        }

        // Clear and reinsert sorted rows
        ui->tableWidget->setRowCount(0);
        for (const auto& rowItems : sortedRows) {
            int newRow = ui->tableWidget->rowCount();
            ui->tableWidget->insertRow(newRow);
            for (int col = 0; col < rowItems.size(); ++col) {
                ui->tableWidget->setItem(newRow, col, rowItems[col]);
            }
        }

        ui->tableWidget->setSortingEnabled(true);
    }
}
void MainWindow::populateEmployeeInfo()
{
    QString id_emp = ui->id_p->text().trimmed();

    if (id_emp.isEmpty()) {
        QMessageBox::warning(this, "Champ requis", "Veuillez saisir un ID !");
        ui->id_p->setFocus();
        return;
    }

    bool ok;
    int id_arch = id_emp.toInt(&ok);
    if (!ok || id_arch <= 0) {
        QMessageBox::warning(this, "Format invalide", "ID doit être un nombre positif !");
        ui->id_p->selectAll();
        ui->id_p->setFocus();
        return;
    }

    Architecte arch;
    if (arch.fetchById(id_arch)) {
        // Debug des données reçues
        qDebug() << "Données récupérées - Nom:" << arch.getNom()
                 << "| Prénom:" << arch.getPrenom()
                 << "| Email:" << arch.getEmail()
                 << "| Poste:" << arch.getPoste();

        // Vérification visuelle des champs UI
        qDebug() << "Champs UI existants :"
                 << ui->nom_conge->objectName()
                 << ui->prenom_conge->objectName();

        // Mise à jour avec vérification de nullité
        if (!arch.getNom().isEmpty()) ui->nom_conge->setText(arch.getNom());
        else qWarning() << "Nom vide !";

        if (!arch.getPrenom().isEmpty()) ui->prenom_conge->setText(arch.getPrenom());
        else qWarning() << "Prénom vide !";

        ui->email_conge->setText(arch.getEmail());
        ui->poste_conge->setText(arch.getPoste());

        // Force la mise à jour de l'UI
        qApp->processEvents();
        qDebug() << "Valeurs après mise à jour :"
                 << ui->nom_conge->text()
                 << ui->prenom_conge->text();

    } else {
        QMessageBox::critical(this, "Erreur", "Architecte non trouvé !");
        ui->id_p->clear();
    }

}
void MainWindow::on_soumettreButton_clicked()
{
    Architecte arch; // Remplacement de Personel par Architecte

    QString id_emp = ui->id_p->text().trimmed();
    QString nom = ui->nom_conge->text().trimmed();
    QString prenom = ui->prenom_conge->text().trimmed();
    QString email = ui->email_conge->text().trimmed();
    QString raison = ui->raison_conge->text().trimmed();
    QString poste = ui->poste_conge->text().trimmed();
    QDate date_d = ui->date_debut->date();
    QDate date_f = ui->date_fin->date();

    // Validation numérique de l'ID
    bool ok;
    int id_arch = id_emp.toInt(&ok);
    if (!ok) {
        QMessageBox::warning(this, "Erreur", "ID invalide. Doit être un nombre.");
        ui->id_p->clear();
        return;
    }

    // Validation des champs obligatoires
    if (nom.isEmpty() || prenom.isEmpty() || email.isEmpty() || raison.isEmpty() || poste.isEmpty()) {
        QMessageBox::warning(this, "Erreur", "Tous les champs doivent être remplis !");
        return;
    }

    // Appel à ajouterconge() de la classe Architecte
    if (arch.ajouterconge(id_emp, nom, prenom, email, raison, poste, date_d, date_f)) {
        QMessageBox::information(this, "Succès", "Demande de congé enregistrée !");
    } else {
        QMessageBox::critical(this, "Erreur", "Échec de l'enregistrement !");
    }

}
void MainWindow::onSelectionChanged(const QItemSelection &selected, const QItemSelection &deselected)
{
    Q_UNUSED(deselected); // Indiquer au compilateur qu'on n'utilise pas ce paramètre

    bool hasSelection = !selected.isEmpty();
    ui->accepter_conge->setEnabled(hasSelection);
    ui->refuser_conge->setEnabled(hasSelection);

    if(hasSelection) {
        QModelIndex index = selected.indexes().first();
        if(index.isValid() && index.column() == 0) {
            QString id = index.data().toString();
            ui->id_emp3->setText(id);
            qDebug() << "Sélection valide - ID:" << id;
        }
    }
    else {
        ui->id_emp3->clear();
        qDebug() << "Aucune sélection";
    }
}QSqlQueryModel *Architecte::afficherconge() {
    QSqlQueryModel *model = new QSqlQueryModel();

    // Nouvelle requête SQL adaptée à la nouvelle base de données
    model->setQuery("SELECT \"ID_CONGE\", \"ID_EMP\", \"NOM\", \"PRENOM\", \"EMAIL\", \"POSTE\", \"RAISON\", \"DATE_D\", \"DATE_F\", \"TYPE_CONGE\", \"CONSEIG\", \"ETAT\" FROM conge");

    if (model->lastError().isValid()) {
        qDebug() << "Erreur d'exécution de la requête :" << model->lastError().text();
        delete model;
        return nullptr;
    }

    // Mise à jour des entêtes de colonnes
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID Congé"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("ID Employé"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Nom"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Prénom"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("Email"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("Poste"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("Raison"));
    model->setHeaderData(7, Qt::Horizontal, QObject::tr("Date Début"));
    model->setHeaderData(8, Qt::Horizontal, QObject::tr("Date Fin"));
    model->setHeaderData(9, Qt::Horizontal, QObject::tr("Type Congé"));
    model->setHeaderData(10, Qt::Horizontal, QObject::tr("Consigne"));
    model->setHeaderData(11, Qt::Horizontal, QObject::tr("État"));

    return model;
}
void MainWindow::refreshTableView()
{
    QSqlQueryModel *model = emp.afficherconge();
    ui->afficher_conge->setModel(model);
    ui->afficher_conge->resizeColumnsToContents();

    connect(ui->afficher_conge->selectionModel(),
            &QItemSelectionModel::selectionChanged,
            this,
            &MainWindow::onSelectionChanged);
}
// Pour l'acceptation
void MainWindow::on_acceptation_clicked()
{
    qDebug() << "Bouton 'Accepter' cliqué";

    if (!ui->afficher_conge->selectionModel()) {
        qDebug() << "Pas de selectionModel !";
        return;
    }

    QModelIndexList selection = ui->afficher_conge->selectionModel()->selectedRows();
    qDebug() << "Nombre de lignes sélectionnées:" << selection.size();

    if (selection.isEmpty()) {
        QMessageBox::warning(this, "Avertissement", "Sélectionnez un congé !");
        return;
    }

    QString id = selection.first().siblingAtColumn(0).data().toString();
    qDebug() << "ID sélectionné:" << id;

    if(emp.updateCongeStatus(id, "ACCEPTÉ")) {
        refreshTableView();
        QMessageBox::information(this, "Succès", "Congé accepté !");
    } else {
        QMessageBox::critical(this, "Erreur", "Échec de la mise à jour du congé.");
    }
}


// Pour le refus
void MainWindow::on_refuser_clicked()
{
    if(ui->afficher_conge->selectionModel()->selectedRows().count() != 1) {
        QMessageBox::warning(this, "Erreur", "Sélection invalide !");
        return;
    }

    QModelIndex index = ui->afficher_conge->selectionModel()->currentIndex();
    QString id = index.sibling(index.row(), 0).data().toString();

    if(emp.updateCongeStatus(id, "REFUSÉ")) {
        refreshTableView();
        QMessageBox::information(this, "Succès", "Congé Refusé !");
    } else {
        QMessageBox::critical(this, "Erreur", "Échec de la mise à jour du congé.");
    }

}

void MainWindow::on_statConge_clicked()
{
    QMap<QString, int> stats = architecte.getCongeStats();  // Call the method you showed earlier

    // Remove entries with 0 count to avoid showing 0% slices
    QMap<QString, int> filteredStats;
    for (auto it = stats.constBegin(); it != stats.constEnd(); ++it) {
        if (it.value() > 0) {
            filteredStats.insert(it.key(), it.value());
        }
    }

    QPieSeries* series = new QPieSeries();
    int total = 0;

    // Populate the series with accepted and refused counts
    for (auto it = filteredStats.constBegin(); it != filteredStats.constEnd(); ++it) {
        series->append(it.key(), it.value());
        total += it.value();
    }

    QMap<QString, QColor> congeColors = {
        {"accepté", QColor(0, 62, 28)},   // Green (#003E1C)
        {"refusé", QColor(86, 9, 5)}     // Red (#560905 )
    };

    for (int i = 0; i < series->count(); ++i) {
        QPieSlice* slice = series->slices().at(i);
        QString label = slice->label().trimmed().toLower();

        if (congeColors.contains(label)) {
            slice->setBrush(congeColors[label]);
        } else {
            slice->setBrush(Qt::gray);
            qDebug() << "Unknown congé state:" << label;
        }

        QString originalLabel = label;
        double percentage = (slice->value() / total) * 100.0;
        slice->setLabel(QString("%1%").arg(QString::number(percentage, 'f', 1)));
        slice->setProperty("congeEtat", originalLabel);
        slice->setLabelVisible(true);
        slice->setLabelFont(QFont("Arial", 12, QFont::Bold));

        connect(slice, &QPieSlice::hovered, [slice](bool state) {
            slice->setExploded(state);
            slice->setExplodeDistanceFactor(state ? 0.1 : 0);
        });
    }

    QChart* chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Statistiques des Congés");
    chart->setTitleFont(QFont("Arial", 16, QFont::Bold));
    chart->setBackgroundBrush(QBrush(Qt::white));
    chart->setAnimationOptions(QChart::SeriesAnimations);

    QLegend* legend = chart->legend();
    legend->setVisible(true);
    legend->setAlignment(Qt::AlignRight);
    legend->setFont(QFont("Arial", 12));

    // Fix duplicate legend entries by setting custom labels
    QList<QLegendMarker*> legendMarkers = legend->markers(series);
    for (int i = 0; i < legendMarkers.size(); ++i) {
        QLegendMarker* marker = legendMarkers.at(i);
        QPieSlice* slice = series->slices().at(i);
        QString congeEtat = slice->property("congeEtat").toString();

        // Capitalize the first letter
        congeEtat = congeEtat.left(1).toUpper() + congeEtat.mid(1);
        marker->setLabel(congeEtat);
    }

    QChartView* chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    chartView->setMinimumSize(550, 400);
    chartView->setBackgroundBrush(Qt::transparent);

    QWidget* containerWidget = new QWidget;
    QVBoxLayout* layout = new QVBoxLayout(containerWidget);
    layout->setContentsMargins(0, 37, 0, 0);
    layout->addWidget(chartView);
    containerWidget->setStyleSheet("background: transparent;");

    QGraphicsProxyWidget* proxy = new QGraphicsProxyWidget();
    proxy->setWidget(containerWidget);
    QGraphicsScene* scene = new QGraphicsScene();
    scene->setBackgroundBrush(Qt::transparent);
    scene->addItem(proxy);

    ui->pie->setScene(scene);
}


void MainWindow::onLoginClicked()
{
    Dialog *loginDialog = new Dialog(this);

    connect(loginDialog, &Dialog::userAuthenticated, this, [=](int id, const QString &role) {
        // Optional: show a message or update UI with the logged-in user's info
        QMessageBox::information(this, "Authentifié", "ID: " + QString::number(id) + "\nRôle: " + role);
    });

    loginDialog->exec();  // or use show() if you prefer non-blocking
}



/*
void MainWindow::afficherConges(const QDate &date)
{
    ui->listConges->clear();  // Vide la liste des congés avant chaque nouvelle sélection
    QString dateStr = date.toString("yyyy-MM-dd");

    // Préparer la requête pour récupérer les congés pour cette date
    QSqlQuery query;
    query.prepare("SELECT NOM, PRENOM, TYPE_CONGE, RAISON FROM CONGE "
                  "WHERE DATE(:date) BETWEEN DATE_D AND DATE_F");
    query.bindValue(":date", dateStr);

    // Exécuter la requête
    if (query.exec()) {
        bool found = false;
        while (query.next()) {
            QString nom = query.value(0).toString();
            QString prenom = query.value(1).toString();
            QString typeConge = query.value(2).toString();
            QString raison = query.value(3).toString();

            // Ajouter les congés dans la liste
            ui->listConges->addItem(typeConge + " - " + prenom + " " + nom + " (" + raison + ")");
            found = true;
        }

        // Afficher le message selon qu'il y ait ou non des congés
        if (found) {
            ui->labelInfo->setText("Congés pour le " + date.toString("dd MMMM yyyy") + " :");
        } else {
            ui->labelInfo->setText("Aucun congé pour le " + date.toString("dd MMMM yyyy") + ".");
        }
    } else {
        qDebug() << "Erreur requête SQL :" << query.lastError().text();
    }
}
*/


void MainWindow::onCalendarDateClicked(const QDate &date)
{
    // Set the date in the date_debut and date_fin fields
    ui->date_debut->setDate(date);
    ui->date_fin->setDate(date);
}


void MainWindow::refreshCongeTableViewOnDateClick(const QDate &date)
{
    // Create a new QSqlQueryModel to hold the data
    QSqlQueryModel *model = new QSqlQueryModel();

    // Convert the selected date to a string format (ensure it matches the Oracle format)
    QString selectedDate = date.toString("yyyy-MM-dd");

    qDebug() << "Selected date:" << selectedDate;

    // SQL query to fetch only the desired columns from the "CONGE" table for the selected date
    QSqlQuery query;
    query.prepare("SELECT NOM, PRENOM, EMAIL, POSTE, DATE_D, DATE_F, ETAT "
                  "FROM MARAM.CONGE "
                  "WHERE DATE_D <= TO_DATE(:selectedDate, 'YYYY-MM-DD') "
                  "AND DATE_F >= TO_DATE(:selectedDate, 'YYYY-MM-DD')");

    query.bindValue(":selectedDate", selectedDate);

    // Print the final query for debugging purposes
    qDebug() << "Executing query: SELECT NOM, PRENOM, EMAIL, POSTE, DATE_D, DATE_F, ETAT "
                "FROM MARAM.CONGE WHERE DATE_D <= TO_DATE('" << selectedDate << "', 'YYYY-MM-DD') "
                                "AND DATE_F >= TO_DATE('" << selectedDate << "', 'YYYY-MM-DD')";

    if (query.exec()) {
        qDebug() << "Query executed successfully.";

        model->setQuery(query);  // Set the query result into the model

        // Check if we have results and update the table
        if (model->rowCount() > 0) {
            // Set the model to the QTableView
            ui->afficher_conge_3->setModel(nullptr);  // Reset the previous model
            ui->afficher_conge_3->setModel(model);

            // Resize columns to contents for better display
            ui->afficher_conge_3->resizeColumnsToContents();

            // Update the headers to match the data
            model->setHeaderData(0, Qt::Horizontal, QObject::tr("Nom"));
            model->setHeaderData(1, Qt::Horizontal, QObject::tr("Prénom"));
            model->setHeaderData(2, Qt::Horizontal, QObject::tr("Email"));
            model->setHeaderData(3, Qt::Horizontal, QObject::tr("Poste"));
            model->setHeaderData(4, Qt::Horizontal, QObject::tr("Date Début"));
            model->setHeaderData(5, Qt::Horizontal, QObject::tr("Date Fin"));
            model->setHeaderData(6, Qt::Horizontal, QObject::tr("État"));
        } else {
            qDebug() << "No records found for the selected date.";
        }
    } else {
        qDebug() << "Error executing query: " << query.lastError().text();
    }
}

void MainWindow::on_voirlesStatistiques_clicked()
{
    ui->mainStack->setCurrentIndex(1);
}

void MainWindow::on_commandLinkButton_clicked()
{
    ui->mainStack->setCurrentIndex(0);
}

void MainWindow::on_pushButton_clicked()
{
    ui->mainStack->setCurrentIndex(2);
}

void MainWindow::on_pushButton_r_clicked()
{
    ui->mainStack->setCurrentIndex(0);
}


void MainWindow::on_ajouter_2_clicked()
{
    // Validate 'nom'
    if (ui->nom->text().isEmpty()) {
        QMessageBox::warning(this, "Input Error", "Nom vide !!");
        return;
    }

    // Validate 'prenom'
    if (ui->prenom->text().isEmpty()) {
        QMessageBox::warning(this, "Input Error", "Prenom vide !!");
        return;
    }

    // Validate 'email' format using regex
    QString email = ui->email->text();
    QRegularExpression emailRegex(R"((\w+)(\.?[\w-]+)*@([\w-]+\.)+[\w-]{2,})");
    QRegularExpressionValidator emailValidator(emailRegex);
    int emailPos = 0;
    if (ui->email->text().isEmpty() || emailValidator.validate(email, emailPos) != QValidator::Acceptable) {
        QMessageBox::warning(this, "Input Error", "Email vide ou invalide !!");
        return;
    }

    // Validate 'salaire' input is numeric
    bool salaireOk;
    double salaire = ui->salaire->text().toDouble(&salaireOk);
    if (!salaireOk || salaire <= 0) {
        QMessageBox::warning(this, "Input Error", "Salaire vide ou invalide !!");
        return;
    }

    if (ui->poste->currentText() == "choisir poste") {
        QMessageBox::warning(this, "Input Error", "Choisir un poste valide.");
        return;
    }

    // Validate 'genre' selection
    if (!ui->homme->isChecked() && !ui->femme_2->isChecked()) {
        QMessageBox::warning(this, "Input Error", "Choisir votre genre.");
        return;
    }

    // Get values from UI elements and set to the 'Employe' object
    QString nom = ui->nom->text();
    QString prenom = ui->prenom->text();
    QString sexe = ui->homme->isChecked() ? "M" : "F"; // Radio buttons for male/female
    QString poste = ui->poste->currentText();
    emp.date_embauche = ui->date_emboche->date(); // Date from QDateEdit widget

    // Set employee attributes
    emp.setNom(nom);
    emp.setPrenom(prenom);
    emp.setSexe(sexe);
    emp.setEmail(email);
    emp.setSalaire(salaire);
    emp.setPoste(poste);

    // Optionally, add employee to database
    if (emp.ajouter()) {  // Assuming you have an ajouter() function to add the employee to the database
        QMessageBox::information(this, "Success", "Employé ajouté avec succès.");
        fillTableWidget(); // Refresh the table widget

        // Reset all form fields
        ui->nom->clear(); // Clear 'nom' field
        ui->prenom->clear(); // Clear 'prenom' field
        ui->email->clear(); // Clear 'email' field
        ui->salaire->clear(); // Clear 'salaire' field
        ui->poste->setCurrentIndex(0); // Reset combo box (set to default/first item)
        ui->homme->setChecked(false); // Uncheck 'homme' radio button
        ui->femme_2->setChecked(false); // Uncheck 'femme' radio button
        ui->date_emboche->setDate(QDate::currentDate()); // Reset date field to current date
    } else {
        QMessageBox::warning(this, "Error", "Échec de l'ajout de l'employé.");
    }
}

void MainWindow::on_supprimerEmploye_clicked() {
    // Get the ID from the input field
    QString id = ui->id_rech->text();

    // Check if the input field is empty
    if (id.isEmpty()) {
        QMessageBox::warning(this, "Input Error", "L'ID pour supprimer est vide.");
        return;
    }

    // Check if the ID exists in the database
    bool exists = emp.idExists(id);
    if (!exists) {
        QMessageBox::warning(this, "Error", "L'ID n'existe pas dans la base de données.");
        return;
    }

    // Try to delete the employee
    bool test = emp.supprimer(id);

    if (test) {
        QMessageBox::information(this, "Success", "Employé supprimé avec succès.");
        fillTableWidget(); // Refresh the table widget

        // Reset all form fields
        ui->id_rech->clear(); // Clear 'id' field
        ui->nom->clear(); // Clear 'nom' field
        ui->prenom->clear(); // Clear 'prenom' field
        ui->email->clear(); // Clear 'email' field
        ui->salaire->clear(); // Clear 'salaire' field
        ui->poste->setCurrentIndex(0); // Reset combo box (set to default/first item)
        ui->homme->setChecked(false); // Uncheck 'homme' radio button
        ui->femme_2->setChecked(false); // Uncheck 'femme' radio button
        ui->date_emboche->setDate(QDate::currentDate()); // Reset date field to current date

    } else {
        QMessageBox::warning(this, "Error", "Échec de la suppression de l'employé.");
    }

}


void MainWindow::on_modifier_2_clicked()
{
    // Retrieve the employee ID from a selected row or an input field
    QString id = ui->id_rech->text();
    if (id.isEmpty()) {
        QMessageBox::warning(this, "Input Error", "L'ID pour modifier est vide.");
        return;
    }

    // Get values from UI elements for each field
    QString nom = ui->nom->text();
    QString prenom = ui->prenom->text();
    QString sexe = ui->homme->isChecked() ? "M" : (ui->femme_2->isChecked() ? "F" : "");
    QString email = ui->email->text();
    float salaire = ui->salaire->text().toFloat();
    QString poste = ui->poste->currentData().toString();
    QDate date_emboche = ui->date_emboche->date();

    // Call the modifier function with the collected values
    bool success = emp.modifier(nom, prenom, sexe, email, salaire, poste, date_emboche, id);
    bool exists = emp.idExists(id);

    if (exists) {
        if (success) {
            QMessageBox::information(this, "Success", "Information de l'employé modifiée avec succès.");
            fillTableWidget(); // Refresh the table widget
            ui->tableWidget->resizeColumnsToContents();  // Resize columns to fit content

            // Reset all form fields
            ui->id_rech->clear(); // Clear 'id' field
            ui->nom->clear(); // Clear 'nom' field
            ui->prenom->clear(); // Clear 'prenom' field
            ui->email->clear(); // Clear 'email' field
            ui->salaire->clear(); // Clear 'salaire' field
            ui->poste->setCurrentIndex(0); // Reset combo box (set to default/first item)
            ui->homme->setChecked(false); // Uncheck 'homme' radio button
            ui->femme_2->setChecked(false); // Uncheck 'femme' radio button
            ui->date_emboche->setDate(QDate::currentDate()); // Reset date field to current date

        } else {
            QMessageBox::warning(this, "Failure", "Échec de la modification des informations de l'employé.");
        }
    } else {
        QMessageBox::information(this, "Failure", "L'ID pour modifier n'existe pas.");
    }

}


void MainWindow::on_refresh_2_clicked()
{
    ui->id_rech->clear(); // Clear 'id' field
    ui->nom->clear(); // Clear 'nom' field
    ui->prenom->clear(); // Clear 'prenom' field
    ui->email->clear(); // Clear 'email' field
    ui->salaire->clear(); // Clear 'salaire' field
    ui->poste->setCurrentIndex(0); // Reset combo box (set to default/first item)
    ui->homme->setChecked(false); // Uncheck 'homme' radio button
    ui->femme_2->setChecked(false); // Uncheck 'femme' radio button
    ui->date_emboche->setDate(QDate::currentDate());
}



void MainWindow::on_annuler_2_clicked()
{
    // Get the ID from the input field
    QString id = ui->id_rech->text();

    // Check if the input field is empty
    if (id.isEmpty()) {
        QMessageBox::warning(this, "Input Error", "L'ID pour supprimer est vide.");
        return;
    }

    // Check if the ID exists in the database
    bool exists = emp.idExists(id);
    if (!exists) {
        QMessageBox::warning(this, "Error", "L'ID n'existe pas dans la base de données.");
        return;
    }

    // Try to delete the employee
    bool test = emp.supprimer(id);

    if (test) {
        QMessageBox::information(this, "Success", "Employé supprimé avec succès.");
        fillTableWidget(); // Refresh the table widget

        // Reset all form fields
        ui->id_rech->clear(); // Clear 'id' field
        ui->nom->clear(); // Clear 'nom' field
        ui->prenom->clear(); // Clear 'prenom' field
        ui->email->clear(); // Clear 'email' field
        ui->salaire->clear(); // Clear 'salaire' field
        ui->poste->setCurrentIndex(0); // Reset combo box (set to default/first item)
        ui->homme->setChecked(false); // Uncheck 'homme' radio button
        ui->femme_2->setChecked(false); // Uncheck 'femme' radio button
        ui->date_emboche->setDate(QDate::currentDate()); // Reset date field to current date

    } else {
        QMessageBox::warning(this, "Error", "Échec de la suppression de l'employé.");
    }
}


void MainWindow::on_accepter_conge_clicked()
{
    qDebug() << "Bouton 'Accepter' cliqué";

    if (!ui->afficher_conge->selectionModel()) {
        qDebug() << "Pas de selectionModel !";
        return;
    }

    QModelIndexList selection = ui->afficher_conge->selectionModel()->selectedRows();
    qDebug() << "Nombre de lignes sélectionnées:" << selection.size();

    if (selection.isEmpty()) {
        QMessageBox::warning(this, "Avertissement", "Sélectionnez un congé !");
        return;
    }

    QString id = selection.first().siblingAtColumn(0).data().toString();
    qDebug() << "ID sélectionné:" << id;

    if(emp.updateCongeStatus(id, "ACCEPTÉ")) {
        refreshTableView();
        QMessageBox::information(this, "Succès", "Congé accepté !");
    } else {
        QMessageBox::critical(this, "Erreur", "Échec de la mise à jour du congé.");
    }
}


void MainWindow::on_refuser_conge_clicked()
{
    if(ui->afficher_conge->selectionModel()->selectedRows().count() != 1) {
        QMessageBox::warning(this, "Erreur", "Sélection invalide !");
        return;
    }

    QModelIndex index = ui->afficher_conge->selectionModel()->currentIndex();
    QString id = index.sibling(index.row(), 0).data().toString();

    if(emp.updateCongeStatus(id, "REFUSÉ")) {
        refreshTableView();
        QMessageBox::information(this, "Succès", "Congé Refusé !");
    } else {
        QMessageBox::critical(this, "Erreur", "Échec de la mise à jour du congé.");
    }

}


void MainWindow::on_refresh_4_clicked()
{
    QSqlQueryModel *model = emp.afficherconge();
    ui->afficher_conge->setModel(model);
    ui->afficher_conge->resizeColumnsToContents();

    connect(ui->afficher_conge->selectionModel(),
            &QItemSelectionModel::selectionChanged,
            this,
            &MainWindow::onSelectionChanged);
}


void MainWindow::on_statpb_2_clicked()
{
    QMap<QString, int> stats = architecte.getCongeStats();  // Call the method you showed earlier

    // Remove entries with 0 count to avoid showing 0% slices
    QMap<QString, int> filteredStats;
    for (auto it = stats.constBegin(); it != stats.constEnd(); ++it) {
        if (it.value() > 0) {
            filteredStats.insert(it.key(), it.value());
        }
    }

    QPieSeries* series = new QPieSeries();
    int total = 0;

    // Populate the series with accepted and refused counts
    for (auto it = filteredStats.constBegin(); it != filteredStats.constEnd(); ++it) {
        series->append(it.key(), it.value());
        total += it.value();
    }

    QMap<QString, QColor> congeColors = {
        {"accepté", QColor(0, 62, 28)},   // Green (#003E1C)
        {"refusé", QColor(86, 9, 5)}     // Red (#560905 )
    };

    for (int i = 0; i < series->count(); ++i) {
        QPieSlice* slice = series->slices().at(i);
        QString label = slice->label().trimmed().toLower();

        if (congeColors.contains(label)) {
            slice->setBrush(congeColors[label]);
        } else {
            slice->setBrush(Qt::gray);
            qDebug() << "Unknown congé state:" << label;
        }

        QString originalLabel = label;
        double percentage = (slice->value() / total) * 100.0;
        slice->setLabel(QString("%1%").arg(QString::number(percentage, 'f', 1)));
        slice->setProperty("congeEtat", originalLabel);
        slice->setLabelVisible(true);
        slice->setLabelFont(QFont("Arial", 12, QFont::Bold));

        connect(slice, &QPieSlice::hovered, [slice](bool state) {
            slice->setExploded(state);
            slice->setExplodeDistanceFactor(state ? 0.1 : 0);
        });
    }

    QChart* chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Statistiques des Congés");
    chart->setTitleFont(QFont("Arial", 16, QFont::Bold));
    chart->setBackgroundBrush(QBrush(Qt::white));
    chart->setAnimationOptions(QChart::SeriesAnimations);

    QLegend* legend = chart->legend();
    legend->setVisible(true);
    legend->setAlignment(Qt::AlignRight);
    legend->setFont(QFont("Arial", 12));

    // Fix duplicate legend entries by setting custom labels
    QList<QLegendMarker*> legendMarkers = legend->markers(series);
    for (int i = 0; i < legendMarkers.size(); ++i) {
        QLegendMarker* marker = legendMarkers.at(i);
        QPieSlice* slice = series->slices().at(i);
        QString congeEtat = slice->property("congeEtat").toString();

        // Capitalize the first letter
        congeEtat = congeEtat.left(1).toUpper() + congeEtat.mid(1);
        marker->setLabel(congeEtat);
    }

    QChartView* chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    chartView->setMinimumSize(550, 400);
    chartView->setBackgroundBrush(Qt::transparent);

    QWidget* containerWidget = new QWidget;
    QVBoxLayout* layout = new QVBoxLayout(containerWidget);
    layout->setContentsMargins(0, 37, 0, 0);
    layout->addWidget(chartView);
    containerWidget->setStyleSheet("background: transparent;");

    QGraphicsProxyWidget* proxy = new QGraphicsProxyWidget();
    proxy->setWidget(containerWidget);
    QGraphicsScene* scene = new QGraphicsScene();
    scene->setBackgroundBrush(Qt::transparent);
    scene->addItem(proxy);

    ui->pie->setScene(scene);
}


void MainWindow::on_soumettre_clicked()
{
    Architecte arch; // Remplacement de Personel par Architecte

    QString id_emp = ui->id_p->text().trimmed();
    QString nom = ui->nom_conge->text().trimmed();
    QString prenom = ui->prenom_conge->text().trimmed();
    QString email = ui->email_conge->text().trimmed();
    QString raison = ui->raison_conge->text().trimmed();
    QString poste = ui->poste_conge->text().trimmed();
    QDate date_d = ui->date_debut->date();
    QDate date_f = ui->date_fin->date();

    // Validation numérique de l'ID
    bool ok;
    int id_arch = id_emp.toInt(&ok);
    if (!ok) {
        QMessageBox::warning(this, "Erreur", "ID invalide. Doit être un nombre.");
        ui->id_p->clear();
        return;
    }

    // Validation des champs obligatoires
    if (nom.isEmpty() || prenom.isEmpty() || email.isEmpty() || raison.isEmpty() || poste.isEmpty()) {
        QMessageBox::warning(this, "Erreur", "Tous les champs doivent être remplis !");
        return;
    }

    // Appel à ajouterconge() de la classe Architecte
    if (arch.ajouterconge(id_emp, nom, prenom, email, raison, poste, date_d, date_f)) {
        QMessageBox::information(this, "Succès", "Demande de congé enregistrée !");
    } else {
        QMessageBox::critical(this, "Erreur", "Échec de l'enregistrement !");
    }

}


void MainWindow::on_refresh_5_clicked()
{
    ui->id_p->clear(); // Clear 'id' field
    ui->nom_conge->clear(); // Clear 'nom' field
    ui->prenom_conge->clear(); // Clear 'prenom' field
    ui->email_conge->clear(); // Clear 'email' field
    ui->raison_conge->clear(); // Clear 'salaire' field
    ui->poste_conge->clear(); // Reset combo box (set to default/first item)
    ui->date_debut->setDate(QDate::currentDate()); // Uncheck 'homme' radio button
    ui->date_fin->setDate(QDate::currentDate());
}


void MainWindow::on_chercher_2_clicked()
{
    QString searchText = ui->id_rech->text().trimmed();
    QString searchCriteria = ui->rechercheCb_2->currentText();
    QSqlQuery query;

    if (searchText.isEmpty()) {
        query.prepare("SELECT * FROM ARCHITECTES");
    } else {
        if (searchCriteria == "ID") {
            query.prepare("SELECT * FROM ARCHITECTES WHERE ID_ARCHITECTE = :searchText");
            query.bindValue(":searchText", searchText.toInt());
        } else if (searchCriteria == "Nom") {
            query.prepare("SELECT * FROM ARCHITECTES WHERE LOWER(NOM) LIKE LOWER(:searchText)");
            query.bindValue(":searchText", "%" + searchText + "%");
        } else if (searchCriteria == "Prénom") {
            query.prepare("SELECT * FROM ARCHITECTES WHERE LOWER(PRENOM) LIKE LOWER(:searchText)");
            query.bindValue(":searchText", "%" + searchText + "%");
        } else if (searchCriteria == "Email") {
            query.prepare("SELECT * FROM ARCHITECTES WHERE LOWER(EMAIL) LIKE LOWER(:searchText)");
            query.bindValue(":searchText", "%" + searchText + "%");
        } else if (searchCriteria == "Poste") {
            query.prepare("SELECT * FROM ARCHITECTES WHERE LOWER(POSTE) LIKE LOWER(:searchText)");
            query.bindValue(":searchText", "%" + searchText + "%");
        } else if (searchCriteria == "Sexe") {
            query.prepare("SELECT * FROM ARCHITECTES WHERE SEXE = :searchText");
            query.bindValue(":searchText", searchText);
        } else if (searchCriteria == "Date") {
            query.prepare("SELECT * FROM ARCHITECTES WHERE DATE_EMBAUCHE LIKE :searchText");
            query.bindValue(":searchText", "%" + searchText + "%");
        } else {
            QMessageBox::warning(this, "Erreur", "Critère de recherche invalide.");
            return;
        }
    }

    if (!query.exec()) {
        qDebug() << "Erreur requête:" << query.lastError().text();
        QMessageBox::warning(this, "Erreur", "Erreur lors de l'exécution de la recherche.");
        return;
    }

    ui->tableWidget->setRowCount(0);
    ui->tableWidget->setColumnCount(8);
    QStringList headers = {"ID", "Nom", "Prénom", "Date", "Poste", "Email", "Salaire", "Sexe"};
    ui->tableWidget->setHorizontalHeaderLabels(headers);

    int row = 0;
    while (query.next()) {
        ui->tableWidget->insertRow(row);
        ui->tableWidget->setItem(row, 0, new QTableWidgetItem(query.value("ID_ARCHITECTE").toString()));
        ui->tableWidget->setItem(row, 1, new QTableWidgetItem(query.value("NOM").toString()));
        ui->tableWidget->setItem(row, 2, new QTableWidgetItem(query.value("PRENOM").toString()));
        ui->tableWidget->setItem(row, 3, new QTableWidgetItem(query.value("DATE_EMBAUCHE").toString()));
        ui->tableWidget->setItem(row, 4, new QTableWidgetItem(query.value("POSTE").toString()));
        ui->tableWidget->setItem(row, 5, new QTableWidgetItem(query.value("EMAIL").toString()));
        ui->tableWidget->setItem(row, 6, new QTableWidgetItem(query.value("SALAIRE").toString()));
        ui->tableWidget->setItem(row, 7, new QTableWidgetItem(query.value("SEXE").toString()));
        row++;
    }

    ui->tableWidget->resizeColumnsToContents();
    qDebug() << "Recherche exécutée sur critère:" << searchCriteria << ", texte:" << searchText;

    // Connect the selection model to handle row selection
    connect(ui->tableWidget->selectionModel(), &QItemSelectionModel::selectionChanged, this, &MainWindow::onRowSelected);
}



void MainWindow::on_refresh_3_clicked()
{
    ui->id_rech->clear(); // Clear 'id' field
    ui->nom->clear(); // Clear 'nom' field
    ui->prenom->clear(); // Clear 'prenom' field
    ui->email->clear(); // Clear 'email' field
    ui->salaire->clear(); // Clear 'salaire' field
    ui->poste->setCurrentIndex(0); // Reset combo box (set to default/first item)
    ui->homme->setChecked(false); // Uncheck 'homme' radio button
    ui->femme_2->setChecked(false); // Uncheck 'femme' radio button
    ui->date_emboche->setDate(QDate::currentDate());
}

