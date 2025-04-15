#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "IconDelegate.h"
#include <QSqlError>
#include <QFileDialog>
#include <QGraphicsScene>
#include <QtCharts/QPieSeries>
#include <QtCharts/QPieSlice>
#include <QtCharts/QChartView>
#include <QtCharts/QChart>
#include "connection.h"
#include <QTimer>
#include <QMessageBox>
#include <QPdfWriter>
#include <QPainter>
#include <QFontMetrics>
#include <QRandomGenerator>
#include <QLegendMarker>
#include <QGraphicsProxyWidget>
#include <QPropertyAnimation>
#include <QMediaPlayer>
#include <QAudioOutput>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    proxyModel(new QSortFilterProxyModel(this)),
    isAscending(true)
{
    ui->setupUi(this);
    ui->acceuil1->setCurrentWidget(ui->acceuil1);
    fillTab();
    // Set default sorting icon
    ui->triButton->setIcon(QIcon(":/ressources/images/ascending.png"));
    // Connect signals to slots
    connect(ui->tableView, &QTableView::clicked, this, &MainWindow::handleIconClick);
    connect(ui->modifier, &QPushButton::clicked, this, &MainWindow::on_modifier_clicked);
    connect(ui->annuler, &QPushButton::clicked, this, &MainWindow::on_annuler_clicked);
    connect(ui->chercher, &QPushButton::clicked, this, &MainWindow::on_chercher_clicked);
    connect(ui->triButton, &QPushButton::clicked, this, &MainWindow::on_triButton_clicked);
    connect(ui->triCb, &QComboBox::currentIndexChanged, this, &MainWindow::on_triCb_currentIndexChanged);
    connect(ui->exportPdf, &QPushButton::clicked, this, &MainWindow::on_exportPdf_clicked);
    connect(ui->statpb, &QPushButton::clicked, this, &MainWindow::on_statpb_clicked);
    connect(ui->bellIcon, &QPushButton::clicked, this, &MainWindow::on_bellIcon_clicked);
    connect(ui->bellIcon, &QPushButton::clicked, this, &MainWindow::showAllAlerts);
    QList<QPair<QString, QString>> alerts = gestionRessources.checkAlerts();
    for (const auto& alert : alerts) {
        handleAlertNotification(alert.first, alert.second);
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::on_ajouter_clicked()
{
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
    bool success = gestionRessources.ajouterRessource(nom, quantite, categorie, fournisseur, dateAchat, etat, prix, dateEntretien);
    if (success) {
        fillTab();
        clearFields();
        QMessageBox::information(this, "Succès", "Ressource ajoutée avec succès !");
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
    bool success = gestionRessources.updateRessource(id, nom, quantite, categorie, fournisseur,
                                                     dateAchat, etat, prix, dateEntretien);
    if (success) {
        fillTab();
        clearFields();
        m_currentResourceId = -1;
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

void MainWindow::on_triCb_currentIndexChanged()
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
        player->setSource(QUrl("qrc:ressources/sounds/notif.wav"));  // Place sound in resources or use absolute path
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


