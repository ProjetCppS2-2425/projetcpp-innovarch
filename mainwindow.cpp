// Project Headers
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "architechtes.h"
#include "rec.h"
#include "dialog.h"
#include "arduino.h"
//#include "arduinocontracteur.h"
#include "contracteur.h"
#include "contrats.h"
#include "mailer.h"
#include "arduinocontrat.h"
#include "IconDelegate.h"
#include "connection.h"
#include <QJsonArray>
#include "projetcrud.h"

#include "sms.h"
#include "arduinocl.h"
#include "clients.h"
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
#include <QStandardItemModel>
#include <QGroupBox>
#include <QDesktopServices>
#include <QTableWidget>

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
    networkManager(new QNetworkAccessManager(this)),
    proxyModel(new QSortFilterProxyModel(this)),
    isAscending(true)
{
    ui->setupUi(this);
    refreshTableWidgetAh();
    // Display stats at startup
    displayProjectStats();
    //****************************************************************************************
    //****************************************************************************************
    //********************************AHMED***************************************************
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
    connect(ui->tableView_2, &QTableView::clicked, this, &MainWindow::on_tableView_itemClicked);
    connect(ui->ajouter_3, &QPushButton::clicked, this, &MainWindow::on_addProjectButton_clicked);
    connect(ui->annuler_3, &QPushButton::clicked, this, &MainWindow::on_cancelButton_clicked);
    connect(ui->supprimer, &QPushButton::clicked, this, &MainWindow::on_deleteProjectButton_clicked);
    connect(ui->modifier_3, &QPushButton::clicked, this, &MainWindow::on_modifyProjectButton_clicked);
    connect(ui->comboBox_tri_2, &QComboBox::currentTextChanged, this, &MainWindow::on_sortButton_clicked);
    connect(ui->comboBox_2, &QComboBox::currentTextChanged, this, &MainWindow::on_searchButton_clicked);
    connect(ui->chercher_3, &QPushButton::clicked, this, &MainWindow::on_searchButton_clicked);
    connect(ui->pdf_3, &QPushButton::clicked, this, &MainWindow::on_exportPDFButton_clicked);
    connect(ui->stat1_2, &QPushButton::clicked, this, &MainWindow::on_stat1_2_clicked);

    fillTableWidgetAh();
    //****************************************************************************************
    //****************************************************************************************
    //********************************AHMED***************************************************
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
    populateLowStockTable();
    ui->triButton->setIcon(QIcon(":/ressources/images/ascending.png"));
    ui->triButton_2->setIcon(QIcon(":/ressources/images/ascending.png"));
    connect(ui->tableView, &QTableView::clicked, this, &MainWindow::handleIconClick);


    // ----- EMPLOYEE/ROLE UI Initialization -----
    fillTableWidget();
    connect(ui->tableWidget, &QTableWidget::cellClicked, this, &MainWindow::handleEmployeeCellClicked);

    // ----- BUTTON CONNECTIONS (Avoid duplicates if same name) -----
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
    connect(ui->recPerso, &QPushButton::clicked, this, &MainWindow::handlePersonalizedRecommendation);


    QList<QPair<QString, QString>> alerts = gestionRessources.checkAlerts();
    for (const auto& alert : alerts) {
        handleAlertNotification(alert.first, alert.second);
    }

    connect(ui->id_p, &QLineEdit::returnPressed, this, &MainWindow::populateEmployeeInfo);
    //connect(ui->soumettre, &QPushButton::clicked, this, &MainWindow::on_soumettreButton_clicked);

    QSqlQueryModel *model = emp.afficherconge();
    ui->afficher_conge->setModel(model);
    ui->afficher_conge->resizeColumnsToContents();
    ui->afficher_conge->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->afficher_conge->setSelectionMode(QAbstractItemView::SingleSelection);
    connect(ui->afficher_conge->selectionModel(), &QItemSelectionModel::selectionChanged, this, &MainWindow::onSelectionChanged);
    //connect(ui->refuser_conge, &QPushButton::clicked, this, &MainWindow::on_refuser_clicked);
    //connect(ui->accepter_conge, &QPushButton::clicked, this, &MainWindow::on_acceptation_clicked);

    connect(ui->calendarConges, &QCalendarWidget::clicked, this, &MainWindow::onCalendarDateClicked);
    connect(ui->calendarConges, &QCalendarWidget::clicked, this, &MainWindow::refreshCongeTableViewOnDateClick);

    connect(ui->tableWidget->selectionModel(), &QItemSelectionModel::selectionChanged, this, &MainWindow::onRowSelected);

    // Login buttons
    connect(ui->pushButton, &QPushButton::clicked, this, &MainWindow::onLoginClicked);
    connect(ui->pushButton_cl, &QPushButton::clicked, this, &MainWindow::onLoginClicked);
   connect(ui->pushButton_ct, &QPushButton::clicked, this, &MainWindow::onLoginClicked);
  connect(ui->pushButton_contrats, &QPushButton::clicked, this, &MainWindow::onLoginClicked);
    connect(ui->pushButton_proj, &QPushButton::clicked, this, &MainWindow::onLoginClicked);
    connect(ui->pushButton_r, &QPushButton::clicked, this, &MainWindow::onLoginClicked);
    connect(ui->pushButton_7, &QPushButton::clicked, this, &MainWindow::onLoginClicked);






    //partie clients


    connect(ui->tableView_4, &QTableView::clicked, this, &MainWindow::on_tableView_itemClicked1);
    connect(ui->ajouter_6, &QPushButton::clicked, this, &MainWindow::on_addClientButton_clicked);
    connect(ui->annuler_6, &QPushButton::clicked, this, &MainWindow::on_annulerButton_clicked);
    connect(ui->supprimer_3, &QPushButton::clicked, this, &MainWindow::on_supprimerClient_clicked);
    connect(ui->modifier_6, &QPushButton::clicked, this, &MainWindow::on_modifyClientButton_clicked);
    connect(ui->chercher_6, &QPushButton::clicked, this, &MainWindow::on_pushButtonRecherche_clicked);
    connect(ui->TrierButton_3, &QPushButton::clicked, this, &MainWindow::on_trierClientButton_clicked);
    connect(ui->pdf_5, &QPushButton::clicked, this, &MainWindow::on_pdfClientButton_clicked);
    connect(ui->statButton_2, &QPushButton::clicked, this, &MainWindow::on_statButton1_clicked);
    connect(ui->sms_2, &QPushButton::clicked, this, &MainWindow::on_btnEnvoyerSMS_clicked);
    connect(ui->Door_2, &QPushButton::clicked, this, &MainWindow::on_pushButton_openDoor_clicked);






    qDebug() << "Calling fillTableWidget() at startup";
    fillTableWidget1();

    // Connexion à Arduino
    // ArduinoCL A;
    int connection = A.connect_arduino();
    if (connection == 0)
        qDebug() << "✅ Arduino connecté sur " << A.getarduino_port_name();
    else if (connection == 1)
        qDebug() << "⚠️ Arduino détecté mais pas connecté.";
    else
        qDebug() << "❌ Arduino non détecté.";

//partie contracteur///////

    fillTableWidget2();
    connect(ui->tableView_2contracteur, &QTableView::clicked, this, &MainWindow::on_tableView_2contracteur_itemClicked);
    connect(ui->ajoutercontracteur, &QPushButton::clicked, this, &MainWindow::on_addContracteurButtoncontracteur_clicked);
    connect(ui->annulercontracteur, &QPushButton::clicked, this, &MainWindow::on_annulerButtoncontracteur_clicked);
    connect(ui->supprimercontracteur, &QPushButton::clicked, this, &MainWindow::on_supprimerContracteurcontracteur_clicked);
    connect(ui->modifiercontracteur, &QPushButton::clicked, this, &MainWindow::on_modifyContracteurButtoncontracteur_clicked);
    connect(ui->comboBox_tri_2contracteur, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &MainWindow::on_comboBox_tri_2contracteur_currentIndexChanged);
    connect(ui->chercher_2contracteur, &QPushButton::clicked, this, &MainWindow::on_chercher_2contracteur_clicked);
    connect(ui->pdf_2contracteur, &QPushButton::clicked, this, &MainWindow::on_pdf_2contracteur_clicked);

    // Connect statistics-related buttons to their slots
    connect(ui->stat1_2, &QPushButton::clicked, this, &MainWindow::on_generateStatisticsButtoncontracteur_clicked);
    connect(ui->stat2_2, &QPushButton::clicked, this, &MainWindow::on_generateStatisticsButtoncontracteur_clicked);
    connect(ui->statbuttcontracteur, &QPushButton::clicked, this, &MainWindow::on_generateStatisticsButtoncontracteur_clicked);
    connect(ui->pdf_3contracteur, &QPushButton::clicked, this, &MainWindow::on_exportStatisticsPDFButtoncontracteur_clicked);
    connect(ui->contractorlisttablecontracteur, &QTableView::clicked, this, &MainWindow::on_contractorlisttablecontracteur_clicked);

    // Connect the "Contracteurs" button to its slot
    connect(ui->pushButton_6, &QPushButton::clicked, this, &MainWindow::on_pushButton_6contracteur_clicked);

    // Populate the architects table
    loadArchitectsToListView();

    // Connect to Arduino
        /*arduino->connectToArduino() ;

        connect(arduinoTimer, &QTimer::timeout, this, &MainWindow::readArduinoData);


        // Set up a timer to continuously read from Arduino
        QTimer *arduinoTimer = new QTimer(this);
        connect(arduinoTimer, &QTimer::timeout, this, &MainWindow::readArduinoData);
        arduinoTimer->start(100); // Check every 100ms





        qDebug() << "Calling fillTableWidget() at startup";
        fillTableWidget1();

        // Connexion à Arduino
       // ArduinoCL A;
       int connection2 = A.connect_arduino();
        if (connection2 == 0)
            qDebug() << "✅ Arduino connecté sur " << A.getarduino_port_name();
        else if (connection2 == 1)
            qDebug() << "⚠️ Arduino détecté mais pas connecté.";
        else
            qDebug() << "❌ Arduino non détecté.";*/


    ////////contrat////////


    connect(ui->affichercontrat, &QPushButton::clicked, this, &MainWindow::afficherContrats);
        AB.connect_arduino();

        timer = new QTimer(this);
        connect(timer, &QTimer::timeout, this, &MainWindow::handleKeypadInput);
        timer->start(500); // vérifie toutes les 500ms





        // Correct signal-slot connections
        connect(ui->tableWidgetcontrat, &QTableWidget::cellClicked, this, &MainWindow::on_tableWidgetcontrat_cellClicked);
        connect(ui->tributtoncontrat, &QPushButton::clicked, this, &MainWindow::on_tributtoncontrat_clicked);
        connect(ui->cherchercontrat, &QPushButton::clicked, this, &MainWindow::on_cherchercontrat_clicked);
        connect(ui->pushbutton_Email, &QPushButton::clicked, this, &MainWindow::on_pushButton_email_clicked);
        connect(ui->exportercontrat, &QPushButton::clicked, this, &MainWindow::on_exportercontrat_clicked);
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
        populateLowStockTable();
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
        populateLowStockTable();
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

void MainWindow::populateLowStockTable()
{
    QSqlQuery query("SELECT NOM_RESSOURCE, QUANTITE, CATEGORIE, FOURNISSEUR FROM RESSOURCES WHERE QUANTITE < 5");

    auto* model = new QStandardItemModel(this);
    model->setHorizontalHeaderLabels({"Nom", "Quantité", "Catégorie", "Fournisseur", "Action"});

    int row = 0;
    while (query.next()) {
        QString nom = query.value("NOM_RESSOURCE").toString();
        int quantite = query.value("QUANTITE").toInt();
        QString categorie = query.value("CATEGORIE").toString();
        QString fournisseur = query.value("FOURNISSEUR").toString();

        model->setItem(row, 0, new QStandardItem(nom));
        model->setItem(row, 1, new QStandardItem(QString::number(quantite)));
        model->setItem(row, 2, new QStandardItem(categorie));
        model->setItem(row, 3, new QStandardItem(fournisseur));
        model->setItem(row, 4, new QStandardItem()); // Placeholder for the button
        row++;
    }

    ui->tableView2->setModel(model);

    // Add buttons to the last column (index 4)
    for (int i = 0; i < model->rowCount(); ++i) {
        QPushButton* button = new QPushButton("Recommandation");
        button->setStyleSheet(R"(
            QPushButton {
                background-color: white;
                color: black;
                border: none;
                border-radius: 2px;
            }
            QPushButton:hover {
                background-color: #aec3b0;
            })");

        QModelIndex index = model->index(i, 4);
        ui->tableView2->setIndexWidget(index, button);

        connect(button, &QPushButton::clicked, this, [=]() {
            handleRecommendationClick(i);
        });
    }

    ui->tableView2->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableView2->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableView2->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableView2->setAlternatingRowColors(true);
}

void MainWindow::showProductCards(const QList<Product>& products, const QString& title)
{
    QDialog* dialog = new QDialog(this);
    dialog->setWindowTitle("Suggestions pour restocker");

    QScrollArea* scrollArea = new QScrollArea;
    QWidget* container = new QWidget;
    QGridLayout* layout = new QGridLayout(container);

    int row = 0, col = 0;
    for (const Product& product : products) {
        QGroupBox* card = new QGroupBox;
        card->setStyleSheet(R"(QGroupBox {
        border: 1px solid #ccc;
        border-radius: 10px;
        padding: 10px;
        background-color: white;}
        QGroupBox:hover {
        border: 2px solid #0099ff;
        background-color: #f0f8ff;
        })");
        QVBoxLayout* cardLayout = new QVBoxLayout(card);
        cardLayout->setAlignment(Qt::AlignCenter);

        QLabel* img = new QLabel;
        QPixmap pix(product.imagePath);
        img->setPixmap(pix.scaled(120, 120, Qt::KeepAspectRatio, Qt::SmoothTransformation));
        img->setFixedSize(130, 130);
        img->setAlignment(Qt::AlignCenter);
        img->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

        QLabel* name = new QLabel("<b>" + product.name + "</b>");
        name->setWordWrap(true);
        name->setAlignment(Qt::AlignCenter);

        QLabel* price = new QLabel(product.price);
        price->setAlignment(Qt::AlignCenter);

        QLabel* rating = new QLabel("⭐ " + product.rating);
        rating->setAlignment(Qt::AlignCenter);

        QPushButton* visit = new QPushButton("Voir le produit");
        visit->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        visit->setStyleSheet(R"(QPushButton {
        background-color: #0099ff;
        color: white;
        border: none;
        border-radius: 5px;
        padding: 6px 12px;}
        QPushButton:hover {
        background-color: #007acc;})");
        connect(visit, &QPushButton::clicked, this, [=]() {
            QDesktopServices::openUrl(QUrl(QUrl(product.url)));
        });

        cardLayout->addWidget(img);
        cardLayout->addWidget(name);
        cardLayout->addWidget(price);
        cardLayout->addWidget(rating);
        cardLayout->addWidget(visit, 0, Qt::AlignHCenter);
        cardLayout->setSpacing(8);

        layout->addWidget(card, row, col);
        col++;
        if (col == 3) {
            col = 0;
            row++;
        }
    }

    scrollArea->setWidget(container);
    scrollArea->setWidgetResizable(true);

    QVBoxLayout* mainLayout = new QVBoxLayout(dialog);

    // ✅ Add the dynamic title at the top
    if (!title.isEmpty()) {
        QLabel* titleLabel = new QLabel(title);
        titleLabel->setStyleSheet("font-size: 18px; font-weight: bold; color: #333; margin-bottom: 15px;");
        titleLabel->setAlignment(Qt::AlignCenter);
        mainLayout->addWidget(titleLabel);
    }

    mainLayout->addWidget(scrollArea);
    dialog->resize(600, 500);
    dialog->exec();
}

void MainWindow::handlePersonalizedRecommendation()
{
    QSqlQuery query("SELECT * FROM (SELECT CATEGORIE, SUM(QUANTITE) AS total FROM RESSOURCES GROUP BY CATEGORIE ORDER BY total DESC) WHERE ROWNUM = 1");

    if (!query.next()) {
        qDebug() << "SQL Error:" << query.lastError().text();
        QMessageBox::warning(this, "Erreur", "Impossible de récupérer les données de recommandation.");
        return;
    }

    QString topCategory = query.value("CATEGORIE").toString();
    QString title = "Recommandation pour la catégorie la plus utilisée: " + topCategory;

    QList<Product> products = getRecommendationsForCategory(topCategory);

    if (products.isEmpty()) {
        QMessageBox::information(this, "Recommandations", "Aucun produit trouvé pour la catégorie : " + topCategory);
        return;
    }

    showProductCards(products, title); // ✅ Pass the title to show in the popup
}


void MainWindow::handleRecommendationClick(int row)
{
    QAbstractItemModel* model = ui->tableView2->model();
    if (!model) return;

    QString category = model->index(row, 2).data().toString(); // Column 2 = Category
    QString resourceName = model->index(row, 0).data().toString(); // Column 0 = Name
    QString title = "Recommandations pour : " + resourceName;

    QList<Product> products = getRecommendationsForCategory(category);

    if (products.isEmpty()) {
        QMessageBox::information(this, "Recommandations", "Aucun produit trouvé pour la catégorie : " + category);
        return;
    }

    showProductCards(products, title);
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
    ui->tableWidget->setColumnCount(10); // 8 columns

    // Set column headers
    ui->tableWidget->setHorizontalHeaderLabels({"ID", "Nom", "Prenom", "Date", "Poste", "Email", "Salaire", "Sexe","Modifier", "Supprimer"});
    QIcon modifyIcon(":/ressources/images/pen.png");     // Use resource path or absolute path
    QIcon deleteIcon(":/ressources/images/bin.png");
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
        //modify button
        QTableWidgetItem *modifyItem = new QTableWidgetItem();
        modifyItem->setIcon(modifyIcon);
        modifyItem->setData(Qt::UserRole, model->data(model->index(row, 0)).toString()); // Store ID
        modifyItem->setFlags(Qt::ItemIsEnabled); // Non-editable but clickable

        // Delete button
        QTableWidgetItem *deleteItem = new QTableWidgetItem();
        deleteItem->setIcon(deleteIcon);
        deleteItem->setData(Qt::UserRole, model->data(model->index(row, 0)).toString()); // Store ID
        deleteItem->setFlags(Qt::ItemIsEnabled);
        // Insert all items into the table
        ui->tableWidget->setItem(row, 0, idItem);
        ui->tableWidget->setItem(row, 1, nomItem);
        ui->tableWidget->setItem(row, 2, prenomItem);
        ui->tableWidget->setItem(row, 3, dateItem);
        ui->tableWidget->setItem(row, 4, posteItem);
        ui->tableWidget->setItem(row, 5, emailItem);
        ui->tableWidget->setItem(row, 6, salaireItem);
        ui->tableWidget->setItem(row, 7, sexeItem);
        ui->tableWidget->setItem(row, 8, modifyItem);
        ui->tableWidget->setItem(row, 9, deleteItem);

    }

    // Enable sorting by clicking headers
    ui->tableWidget->setSortingEnabled(true);
    ui->tableWidget->resizeColumnsToContents();
}

void MainWindow::handleEmployeeCellClicked(int row, int column)
{
    if (column == 8) { // Pen (modify)
        QString id = ui->tableWidget->item(row, 0)->text();
        QString nom = ui->tableWidget->item(row, 1)->text();
        QString prenom = ui->tableWidget->item(row, 2)->text();
        QDate date_emboche = QDate::fromString(ui->tableWidget->item(row, 3)->text(), "yyyy-MM-dd");
        QString poste = ui->tableWidget->item(row, 4)->text();
        QString email = ui->tableWidget->item(row, 5)->text();
        float salaire = ui->tableWidget->item(row, 6)->data(Qt::UserRole).toFloat();
        QString sexe = ui->tableWidget->item(row, 7)->text();

        // Prefill UI fields
        ui->id_rech->setText(id);
        ui->nom->setText(nom);
        ui->prenom->setText(prenom);
        ui->email->setText(email);
        ui->salaire->setText(QString::number(salaire, 'f', 2));
        ui->date_emboche->setDate(date_emboche);

        if (sexe == "M") ui->homme->setChecked(true);
        else if (sexe == "F") ui->femme_2->setChecked(true);
        else { ui->homme->setChecked(false); ui->femme_2->setChecked(false); }

        // Match poste in combo box
        int index = ui->poste->findText(poste);
        if (index != -1) ui->poste->setCurrentIndex(index);

    } else if (column == 9) { // Bin (delete)
        QString id = ui->tableWidget->item(row, 0)->text();
        bool deleted = emp.supprimer(id);
        if (deleted) {
            QMessageBox::information(this, "Suppression", "Employé supprimé avec succès.");
            fillTableWidget();
        } else {
            QMessageBox::warning(this, "Erreur", "Échec de la suppression.");
        }
    }
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

void MainWindow::refreshTableWidget() {
    // Fetch updated data from the database
    QSqlQueryModel *model = emp.afficher();  // Assuming 'emp.afficher()' returns a QSqlQueryModel with updated data.

    // Clear any existing data in the table widget
    ui->tableWidget->clearContents();
    ui->tableWidget->setRowCount(0);

    // Set the correct column count (ID + other fields)
    ui->tableWidget->setColumnCount(10);  // 10 columns (ID, Nom, Prenom, Date, Poste, Email, Salaire, Sexe)

    // Set the column headers
    ui->tableWidget->setHorizontalHeaderLabels({"ID", "Nom", "Prenom", "Date", "Poste", "Email", "Salaire", "Sexe", "Modifier","Supprimer"});

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

    ui->triButton_2->setIcon(QIcon(isAscending
                                     ? ":/ressources/images/ascending.png"
                                     : ":/ressources/images/descending.png"));
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

//********************************************************************************************
//********************************************************************************************
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



void MainWindow::fillTableWidgetAh() {
    if (!QSqlDatabase::database().isOpen()) {
        qDebug() << "Database connection is not open!";
        return;
    }

    QSqlQueryModel *model = currentProject.afficher();
    if (model) {
        ui->tableView_2->setModel(model);
        ui->tableView_2->resizeColumnsToContents(); // Adjust column widths
        ui->tableView_2->horizontalHeader()->setStretchLastSection(true); // Stretch the last column
        ui->tableView_2->setSelectionBehavior(QAbstractItemView::SelectRows); // Select entire rows
        ui->tableView_2->setEditTriggers(QAbstractItemView::NoEditTriggers); // Disable editing

        qDebug() << "TableView updated successfully.";
    } else {
        qDebug() << "Failed to retrieve model for TableView.";
    }
}

void MainWindow::refreshTableWidgetAh() {
    fillTableWidgetAh();
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
        fillTableWidgetAh();
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
        fillTableWidgetAh();
    } else {
        QMessageBox::warning(this, "Failure", "Échec de la modification du projet.");
    }
}

void MainWindow::on_deleteProjectButton_clicked() {
    int id = ui->id_rech_2->text().toInt();
    if (currentProject.supprimer(id)) {
        QMessageBox::information(this, "Success", "Projet supprimé avec succès.");
        fillTableWidgetAh();
    } else {
        QMessageBox::warning(this, "Error", "Échec de la suppression du projet.");
    }
}

void MainWindow::on_tableView_itemClicked(const QModelIndex &index) {
    int row = index.row();

    // Récupération des valeurs
    QString statutDB = ui->tableView_2->model()->data(ui->tableView_2->model()->index(row, 5)).toString();

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
    ui->id_rech_2->setText(ui->tableView_2->model()->data(ui->tableView_2->model()->index(row, 0)).toString());
    ui->lineEdit_7->setText(ui->tableView_2->model()->data(ui->tableView_2->model()->index(row, 1)).toString());
    ui->comboBox->setCurrentText(ui->tableView_2->model()->data(ui->tableView_2->model()->index(row, 2)).toString());
    ui->lineEdit_5->setText(ui->tableView_2->model()->data(ui->tableView_2->model()->index(row, 3)).toString());
    ui->dateEdit->setDate(QDate::fromString(ui->tableView_2->model()->data(ui->tableView_2->model()->index(row, 4)).toString(), "yyyy-MM-dd"));
    ui->dateEdit_2->setDate(QDate::fromString(ui->tableView_2->model()->data(ui->tableView_2->model()->index(row, 4)).toString(), "yyyy-MM-dd"));
    ui->lineEdit_2->setText(ui->tableView_2->model()->data(ui->tableView_2->model()->index(row, 6)).toString());
    ui->lineEdit_3->setText(ui->tableView_2->model()->data(ui->tableView_2->model()->index(row, 7)).toString());
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
        ui->tableView_2->setModel(model);
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
        ui->tableView_2->setModel(model);
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
        ui->tableView_2->setModel(model);
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
        ui->tableView_2->setModel(model);
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
//////////// partie client//////////////////


//partie clients

void MainWindow::on_pushButton_openDoor_clicked()
{
    static QTime lastClickTime; // Pour déboguer les clics rapprochés
    QTime currentTime = QTime::currentTime();
    if (lastClickTime.isValid() && lastClickTime.msecsTo(currentTime) < 1000) {
        qDebug() << "Clic ignoré : trop proche du précédent (< 1s).";
        return;
    }
    lastClickTime = currentTime;

    if (isUpdatingPresence) {
        qDebug() << "Mise à jour de la présence en cours, clic ignoré.";
        return;
    }

    QString id = ui->label_id_2->text().trimmed();  // Récupérer l'ID du QLineEdit
    if (id.isEmpty()) {
        QMessageBox::warning(this, "Erreur", "L'ID est vide ! Veuillez entrer un ID valide.");
        return;
    }

    // Vérifier si l'Arduino est connecté
    if (!A.getserial()->isOpen()) {
        QMessageBox::critical(this, "Erreur", "Arduino non connecté. Vérifiez la connexion.");
        return;
    }

    // Envoyer la commande à Arduino
    A.write_to_arduino("O\n");  // Envoyer 'O' pour ouvrir
    qDebug() << "Commande 'O\\n' envoyée à Arduino pour ID:" << id;

    // Désactiver le bouton temporairement pour éviter les clics multiples
    ui->Door_2->setEnabled(false);
    QTimer::singleShot(5000, this, [this]() {
        ui->Door_2->setEnabled(true);  // Réactiver après 5s
    });

    // Mettre à jour la présence
    isUpdatingPresence = true;
    updatePresence(id);
    isUpdatingPresence = false;
}

void MainWindow::updatePresence(QString id)
{
    QSqlQuery query;
    query.prepare("SELECT presence FROM ARCHITECTES WHERE id_architecte = :id");
    query.bindValue(":id", id.toInt());

    if (!query.exec()) {
        QMessageBox::critical(this, "Erreur SQL", "Erreur lors de la vérification de la présence : " + query.lastError().text());
        return;
    }

    QString newPresence;
    if (query.next()) {
        QString currentPresence = query.value(0).toString().toLower();
        qDebug() << "Présence actuelle pour ID" << id << ":" << currentPresence;

        // Déterminer la nouvelle présence
        newPresence = (currentPresence == "present") ? "absent" : "present";

        // Mettre à jour la présence
        QSqlQuery updateQuery;
        updateQuery.prepare("UPDATE ARCHITECTES SET presence = :presence WHERE id_architecte = :id");
        updateQuery.bindValue(":presence", newPresence);
        updateQuery.bindValue(":id", id.toInt());

        if (updateQuery.exec()) {
            qDebug() << "Présence mise à jour pour ID" << id << ":" << newPresence;
            // Vérifier l'état après mise à jour
            QSqlQuery verifyQuery;
            verifyQuery.prepare("SELECT presence FROM ARCHITECTES WHERE id_architecte = :id");
            verifyQuery.bindValue(":id", id.toInt());
            if (verifyQuery.exec() && verifyQuery.next()) {
                QString verifiedPresence = verifyQuery.value(0).toString().toLower();
                qDebug() << "Présence vérifiée après mise à jour pour ID" << id << ":" << verifiedPresence;
                if (verifiedPresence != newPresence) {
                    qDebug() << "Erreur : la présence dans la base ne correspond pas à la mise à jour !";
                }
            }
            QMessageBox::information(this, "Succès", QString("Présence mise à jour pour ID %1 : %2").arg(id, newPresence));
        } else {
            qDebug() << "Erreur lors de la mise à jour de la présence :" << updateQuery.lastError().text();
            QMessageBox::critical(this, "Erreur", "Erreur lors de la mise à jour de la présence : " + updateQuery.lastError().text());
        }
    } else {
        qDebug() << "Aucun architecte trouvé avec l'ID" << id;
        QMessageBox::warning(this, "Erreur", QString("Aucun architecte trouvé avec l'ID %1.").arg(id));
    }
}

void MainWindow::fillTableWidget1() {
    qDebug() << "Executing fillTableWidget()";
    QSqlQueryModel *model = currentClient.afficher();

    if (model) {
        ui->tableView_4->setModel(model);
        ui->tableView_4->resizeColumnsToContents();
        qDebug() << "Table widget filled successfully";
    } else {
        qDebug() << "Failed to fill table widget";
    }
}

void MainWindow::on_addClientButton_clicked()
{
    if (ui->lineEdit_16->text().isEmpty()) {
        QMessageBox::warning(this, "Input Error", "Nom vide !!");
        return;
    }

    if (ui->lineEdit_21->text().isEmpty()) {
        QMessageBox::warning(this, "Input Error", "Prénom vide !!");
        return;
    }

    QString email = ui->lineEdit_19->text();
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

    QString nom = ui->lineEdit_16->text();
    QString prenom = ui->lineEdit_21->text();
    QString telephone = ui->lineEdit_20->text();
    QString adresse = ui->lineEdit_18->text();
    QString sexe = ui->comboBox_6->currentText();
    int id_projet = ui->lineEdit_15->text().toInt();


    qDebug() << "Adding Client with details:";
    qDebug() << "ID:" << id_client;
    qDebug() << "Nom:" << nom;
    qDebug() << "Prénom:" << prenom;
    qDebug() << "Email:" << email;
    qDebug() << "Telephone:" << telephone;
    qDebug() << "Adresse:" << adresse;
    qDebug() << "Sexe:" << sexe;
    qDebug() <<"id_projet"<<id_projet;


    currentClient = Clients(id_client, nom, prenom, email, telephone, adresse, sexe,id_projet);

    if (currentClient.ajouter()) {
        QMessageBox::information(this, "Success", "Client ajouté avec succès.");
        fillTableWidget1();

        ui->lineEdit_16->clear();
        ui->lineEdit_21->clear();
        ui->lineEdit_20->clear();
        ui->lineEdit_18->clear();
        ui->lineEdit_15->clear();
        ui->lineEdit_19->clear();
        ui->comboBox_6->setCurrentIndex(0);
    } else {
        QMessageBox::warning(this, "Error", "Échec de l'ajout du client.");
    }
}

void MainWindow::on_supprimerClient_clicked() {
    int id = ui->id_rech_4->text().toInt();

    if (id == 0) {
        QMessageBox::warning(this, "Input Error", "L'ID pour supprimer est vide.");
        return;
    }

    if (currentClient.supprimer(id)) {
        QMessageBox::information(this, "Success", "Client supprimé avec succès.");
        fillTableWidget1();

        ui->id_rech_4->clear();
        ui->lineEdit_16->clear();
        ui->lineEdit_21->clear();
        ui->lineEdit_20->clear();
        ui->lineEdit_18->clear();
        ui->lineEdit_15->clear();
        ui->lineEdit_19->clear();
        ui->comboBox_6->setCurrentIndex(0);
    } else {
        QMessageBox::warning(this, "Error", "Échec de la suppression du client.");
    }
}

void MainWindow::on_modifyClientButton_clicked()
{
    int id = ui->id_rech_4->text().toInt();
    if (id == 0) {
        QMessageBox::warning(this, "Input Error", "L'ID pour modifier est vide.");
        return;
    }

    QString nom = ui->lineEdit_16->text();
    QString prenom = ui->lineEdit_21->text();

    QString telephone = ui->lineEdit_20->text();

    QString adresse = ui->lineEdit_18->text();
    QString email = ui->lineEdit_19->text();
    QString sexe = ui->comboBox_6->currentText();
    int id_projet = ui->lineEdit_15->text().toInt();

    currentClient = Clients(id, nom, prenom, email, telephone, adresse, sexe,id_projet);

    if (currentClient.modifier(id)) {
        QMessageBox::information(this, "Success", "Client modifié avec succès.");
        fillTableWidget1();

        ui->id_rech_4->clear();
        ui->lineEdit_16->clear();
        ui->lineEdit_21->clear();
        ui->lineEdit_20->clear();
        ui->lineEdit_18->clear();
        ui->lineEdit_19->clear();
        ui->lineEdit_15->clear();
        ui->comboBox_6->setCurrentIndex(0);
    } else {
        QMessageBox::warning(this, "Failure", "Échec de la modification du client.");
    }
}

void MainWindow::on_tableView_itemClicked1(const QModelIndex &index)
{
    int row = index.row();

    QString id = ui->tableView_4->model()->data(ui->tableView_4->model()->index(row, 0)).toString();
    QString nom = ui->tableView_4->model()->data(ui->tableView_4->model()->index(row, 1)).toString();
    QString prenom = ui->tableView_4->model()->data(ui->tableView_4->model()->index(row, 2)).toString();
    QString telephone = ui->tableView_4->model()->data(ui->tableView_4->model()->index(row, 3)).toString();
    QString adresse = ui->tableView_4->model()->data(ui->tableView_4->model()->index(row, 4)).toString();
    QString email = ui->tableView_4->model()->data(ui->tableView_4->model()->index(row, 5)).toString();
    QString sexe = ui->tableView_4->model()->data(ui->tableView_4->model()->index(row, 6)).toString();
    QString id_projet = ui->tableView_4->model()->data(ui->tableView_4->model()->index(row, 7)).toString();

    ui->id_rech_4->setText(id);
    ui->lineEdit_16->setText(nom);
    ui->lineEdit_21->setText(prenom);
    ui->lineEdit_20->setText(telephone);
    ui->lineEdit_18->setText(adresse);
    ui->lineEdit_19->setText(email);
    ui->lineEdit_15->setText(id_projet);
    ui->comboBox_6->setCurrentText(sexe);

    // ⚠️ Envoi SMS ici automatiquement

}


void MainWindow::refreshTableWidget1() {
    QSqlQueryModel *model = currentClient.afficher();

    ui->tableView->setModel(model);
    ui->tableView->resizeColumnsToContents();
}

void MainWindow::on_annulerButton_clicked() {

    ui->lineEdit_16->clear();
    ui->lineEdit_21->clear();
    ui->lineEdit_20->clear();
    ui->lineEdit_18->clear();
    ui->lineEdit_15->clear();
    ui->lineEdit_19->clear();
    ui->comboBox_6->setCurrentIndex(0);
}

void MainWindow::on_pushButtonRecherche_clicked() {
    QString searchText = ui->id_rech_4->text().trimmed();
    QString searchCriteria = ui->comboBox_5->currentText();
    QSqlQueryModel *model = new QSqlQueryModel();
    QSqlQuery query;

    if (searchText.isEmpty()) {
        // Display all clients if no search text is provided
        query.prepare("SELECT * FROM clients");
    } else {
        // Prepare query based on selected criteria
        if (searchCriteria == "ID") {
            query.prepare("SELECT * FROM clients WHERE ID_CLIENT = :searchText");
            query.bindValue(":searchText", searchText.toInt());
        } else if (searchCriteria == "Nom") {
            query.prepare("SELECT * FROM clients WHERE LOWER(NOM) LIKE LOWER(:searchText)");
            query.bindValue(":searchText", "%" + searchText + "%");
        } else if (searchCriteria == "Prénom") {
            query.prepare("SELECT * FROM clients WHERE LOWER(PRENOM) LIKE LOWER(:searchText)");
            query.bindValue(":searchText", "%" + searchText + "%");
        } else if (searchCriteria == "Email") {
            query.prepare("SELECT * FROM clients WHERE LOWER(EMAIL) LIKE LOWER(:searchText)");
            query.bindValue(":searchText", "%" + searchText + "%");
        } else if (searchCriteria == "Téléphone") {
            query.prepare("SELECT * FROM clients WHERE TELEPHONE LIKE :searchText");
            query.bindValue(":searchText", "%" + searchText + "%");
        } else if (searchCriteria == "Adresse") {
            query.prepare("SELECT * FROM clients WHERE LOWER(ADRESSE) LIKE LOWER(:searchText)");
            query.bindValue(":searchText", "%" + searchText + "%");
        } else {
            QMessageBox::warning(this, "Search Error", "Critère de recherche invalide.");
            return;
        }
    }

    if (!query.exec()) {
        qDebug() << "Search query failed:" << query.lastError().text();
        QMessageBox::warning(this, "Search Error", "Erreur lors de l'exécution de la recherche.");
        return;
    }

    model->setQuery(query);

    // Set column headers
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Prénom"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Email"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("Téléphone"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("Adresse"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("Sexe"));

    // Display results in the table
    ui->tableView->setModel(model);
    ui->tableView->resizeColumnsToContents();

    qDebug() << "Search executed successfully with criteria:" << searchCriteria << "and text:" << searchText;
}
void MainWindow::on_trierClientButton_clicked()
{
    QString triCritere = ui->comboBox_tri_7->currentText();
    QString ordre = ui->comboBox_tri_8->currentText();

    QString queryStr = "SELECT * FROM clients ORDER BY ";

    if (triCritere == "ID") {
        queryStr += "id_client";
    } else if (triCritere == "Nom") {
        queryStr += "nom";
    } else if (triCritere == "Prenom") {
        queryStr += "prenom";
    } else if (triCritere == "Telephone") {
        queryStr += "telephone";
    } else if (triCritere == "Adresse") {
        queryStr += "adresse";
    } else if (triCritere == "Email") {
        queryStr += "email";
    } else if (triCritere == "Date d'ajout") {
        queryStr += "dateajout";
    } else {
        queryStr = "SELECT * FROM clients";  // Aucun tri choisi
    }

    // Ajouter l'ordre
    if (queryStr.contains("ORDER BY")) {
        if (ordre == "Décroissant") {
            queryStr += " DESC";
        } else {
            queryStr += " ASC";
        }
    }

    QSqlQueryModel *model = new QSqlQueryModel();
    model->setQuery(queryStr);

    if (model->lastError().isValid()) {
        qDebug() << "Erreur lors du tri (clients) :" << model->lastError().text();
    }

    // Entêtes
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Prenom"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Telephone"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("Adresse"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("Email"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("Date d'Ajout"));

    ui->tableView->setModel(model);
    ui->tableView->resizeColumnsToContents();
}

void MainWindow::on_pdfClientButton_clicked()
{
    QString filePath = QFileDialog::getSaveFileName(this, "Enregistrer le PDF", "", "PDF Files (*.pdf)");
    if (filePath.isEmpty())
        return;

    QPdfWriter writer(filePath);
    writer.setPageSize(QPageSize::A4);
    writer.setResolution(300);
    writer.setPageMargins(QMarginsF(30, 30, 30, 30));

    QPainter painter(&writer);
    if (!painter.isActive()) {
        QMessageBox::warning(this, "Erreur", "Erreur lors de la création du PDF.");
        return;
    }

    // ---- Fonts ----
    QFont titleFont("Arial", 22, QFont::Bold);
    QFont headerFont("Arial", 13, QFont::Bold);
    QFont cellFont("Arial", 11);
    QFont footerFont("Arial", 9);

    const int marginLeft = 50;
    const int marginRight = 50;
    const int padding = 10;
    int top = 100;

    QAbstractItemModel *model = ui->tableView->model();
    int cols = model->columnCount();
    int rows = model->rowCount();

    // Largeur dynamique
    int availableWidth = writer.width() - marginLeft - marginRight;
    int colWidth = availableWidth / cols;
    int rowHeight = 50;  // plus grand pour aération

    // ---- Title ----
    painter.setFont(titleFont);
    painter.setPen(QColor("#0f172a")); // bleu foncé
    painter.drawText(QRect(marginLeft, top, writer.width() - marginLeft - marginRight, 60),
                     Qt::AlignCenter, "📄 Rapport des Clients");

    top += 70;

    // ---- Date ----
    painter.setFont(cellFont);
    painter.setPen(Qt::gray);
    painter.drawText(QRect(marginLeft, top, writer.width() - marginLeft - marginRight, 30),
                     Qt::AlignRight, "📅 " + QDate::currentDate().toString("dd MMMM yyyy"));

    top += 40;

    // ---- Table Header ----
    painter.setFont(headerFont);
    painter.setPen(Qt::black);
    QColor headerColor("#93c5fd"); // bleu clair

    for (int col = 0; col < cols; ++col) {
        QRect cellRect(marginLeft + col * colWidth, top, colWidth, rowHeight);
        painter.fillRect(cellRect, headerColor);
        painter.setPen(Qt::black);
        painter.drawRect(cellRect);
        painter.drawText(cellRect.adjusted(padding, 0, -padding, 0),
                         Qt::AlignVCenter | Qt::AlignLeft,
                         model->headerData(col, Qt::Horizontal).toString());
    }

    top += rowHeight;

    // ---- Table Rows ----
    painter.setFont(cellFont);

    for (int row = 0; row < rows; ++row) {
        QColor bgColor = (row % 2 == 0) ? QColor("#f8fafc") : QColor("#e2e8f0");
        for (int col = 0; col < cols; ++col) {
            QRect cellRect(marginLeft + col * colWidth, top, colWidth, rowHeight);
            painter.fillRect(cellRect, bgColor);
            painter.setPen(Qt::gray);
            painter.drawRect(cellRect);

            painter.setPen(Qt::black);
            QString data = model->data(model->index(row, col)).toString();
            painter.drawText(cellRect.adjusted(padding, 0, -padding, 0),
                             Qt::AlignVCenter | Qt::AlignLeft, data);
        }

        top += rowHeight;

        // Page break
        if (top + rowHeight > writer.height() - 100) {
            writer.newPage();
            top = 100;
        }
    }

    // ---- Footer ----
    int footerY = writer.height() - 60;
    painter.setFont(footerFont);
    painter.setPen(QColor("#94a3b8"));
    painter.drawLine(marginLeft, footerY - 10, writer.width() - marginRight, footerY - 10);
    painter.drawText(marginLeft, footerY,
                     "🧾 Rapport généré automatiquement par ClientManager Pro");
    painter.drawText(marginLeft, footerY + 15,
                     "📧 support@clientmanager.app    © 2025");

    painter.end();

    QMessageBox::information(this, "PDF", "✅ PDF généré avec succès !");
}



void MainWindow::on_statButton1_clicked()
{
    QMap<QString, int> villeCount;
    QSqlQuery query("SELECT adresse FROM clients");

    while (query.next()) {
        QString adresse = query.value(0).toString().toLower();
        QString ville;

        if (adresse.contains("tunis")) {
            ville = "Tunis";
        } else if (adresse.contains("sfax")) {
            ville = "Sfax";
        } else if (adresse.contains("sousse")) {
            ville = "Sousse";
        } else {
            ville = "Autres";
        }

        villeCount[ville]++;
    }
    QMap<QString, QColor> villeColors = {
        {"Tunis", QColor(33, 158, 188)},   // Soft Blue
        {"Sfax", QColor(176, 196, 177)},    // Fresh Green
        {"Sousse", QColor(237, 175, 184)},  // Vibrant Orange
        {"Autres", QColor(155, 89, 182)}   // Elegant Purple
    };
    QPieSeries *series = new QPieSeries();
    int total = 0;
    for (int count : villeCount.values())
        total += count;

    for (auto it = villeCount.begin(); it != villeCount.end(); ++it) {
        double percentage = (double(it.value()) / total) * 100.0;
        QPieSlice *slice = series->append(it.key() + QString(" (%1%)").arg(percentage, 0, 'f', 1), it.value());

        slice->setLabelVisible(true);
        slice->setExploded(it.key() != "Autres");
        slice->setPen(Qt::NoPen);
        slice->setBrush(villeColors.value(it.key(), Qt::lightGray));

        // Inside your for loop for slices
        QObject::connect(slice, &QPieSlice::hovered, this, [slice](bool hovered){
            slice->setExploded(hovered);
            slice->setLabelFont(hovered ? QFont("Arial", 11, QFont::Bold) : QFont("Arial", 9));
            slice->setBrush(hovered
                                ? slice->brush().color().lighter(120)  // Slightly lighter on hover
                                : slice->brush().color().darker(100)); // Back to normal
        });

    }

    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Répartition des clients par ville");
    chart->setTitleFont(QFont("Arial", 14, QFont::Bold));
    chart->legend()->setVisible(true);
    chart->legend()->setAlignment(Qt::AlignBottom);
    chart->setBackgroundVisible(true);
    chart->setBackgroundBrush(QBrush(Qt::white));
    chart->setDropShadowEnabled(false);
    chart->setBackgroundPen(Qt::NoPen);
    chart->setAnimationOptions(QChart::AllAnimations);

    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    // Size of chart inside stat
    QSize viewSize = ui->stat_2->size();
    int chartW = viewSize.width() * 0.7;
    int chartH = viewSize.height() * 0.7;
    chartView->setFixedSize(chartW, chartH);

    if (ui->stat_2->scene()) {
        delete ui->stat_2->scene();
    }

    QGraphicsScene *scene = new QGraphicsScene(this);

    QGraphicsProxyWidget *proxy = scene->addWidget(chartView);

    // 👇 Manually set scene rect bigger than chart so we can move things freely
    int sceneWidth = viewSize.width();
    int sceneHeight = viewSize.height() + 200; // Give space to move down
    scene->setSceneRect(0, 0, sceneWidth, sceneHeight);

    // ✅ Actually move chart down
    int x = (sceneWidth - chartW) / 2;
    int y = (sceneHeight - chartH) / 2 -10 ;  // now this works!
    proxy->setPos(x, y);

    ui->stat_2->setScene(scene);
    ui->stat_2->setSceneRect(scene->sceneRect()); // 🔒 Lock the scene size

    // 🔧 Optional: Disable scrollbars or scaling
    ui->stat_2->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->stat_2->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->stat_2->setAlignment(Qt::AlignLeft | Qt::AlignTop); // avoid auto-centering
}

void MainWindow::on_btnEnvoyerSMS_clicked()
{
    int idClient = ui->id_rech_4->text().toInt();

    SMS sms;
    bool success = sms.envoyerStatutProjetAuClient(idClient);


    if (success) {
        QMessageBox::information(this, "Succès", "SMS envoyé au client !");
    } else {
        QMessageBox::warning(this, "Erreur", "Échec de l’envoi du SMS.");
    }
}
////////////// partie contracteur///////////////

void MainWindow::fillTableWidget2() {
    QSqlQueryModel *model = currentContracteur.afficher();
    if (!model) {
        qDebug() << "Failed to fetch model for tableView_2.";
        return;
    }
    ui->tableView_2contracteur->setModel(model);
    ui->tableView_2contracteur->resizeColumnsToContents();
    model->setHeaderData(7, Qt::Horizontal, QObject::tr("Date d'Ajout"));
}

void MainWindow::on_addContracteurButtoncontracteur_clicked() {
    // Input validation
    if (ui->lineEdit_2contracteur->text().isEmpty()) {
        QMessageBox::warning(this, "Input Error", "Nom est vide !");
        return;
    }
    if (ui->lineEdit_13contracteur->text().isEmpty()) {
        QMessageBox::warning(this, "Input Error", "Prenom est vide !");
        return;
    }
    QString telephone = ui->lineEdit_7contracteur->text();
    if (telephone.isEmpty()) {
        QMessageBox::warning(this, "Input Error", "Telephone est vide !");
        return;
    }
    if (!QRegularExpression("^[0-9]{8}$").match(telephone).hasMatch()) {
        QMessageBox::warning(this, "Input Error", "Le numéro de téléphone doit contenir exactement 8 chiffres !");
        return;
    }
    QString adresse = ui->lineEdit_4contracteur->text();
    if (adresse.isEmpty()) {
        QMessageBox::warning(this, "Input Error", "Adresse est vide !");
        return;
    }
    QString email = ui->lineEdit_5contracteur->text();
    if (email.isEmpty()) {
        QMessageBox::warning(this, "Input Error", "Email est vide !");
        return;
    }
    if (!QRegularExpression("^[\\w.-]+@[\\w.-]+\\.[a-zA-Z]{2,}$").match(email).hasMatch()) {
        QMessageBox::warning(this, "Input Error", "L'email doit être au format something@something.something !");
        return;
    }
    QString domaine = ui->comboBoxcontracteur->currentText();
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

    QString nom = ui->lineEdit_2contracteur->text();
    QString prenom = ui->lineEdit_13contracteur->text();
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
        fillTableWidget2();

        // Clear input fields
        ui->lineEdit_2contracteur->clear();
        ui->lineEdit_13contracteur->clear();
        ui->lineEdit_7contracteur->clear();
        ui->lineEdit_4contracteur->clear();
        ui->lineEdit_5contracteur->clear();
        ui->comboBoxcontracteur->setCurrentIndex(0);
    } else {
        QMessageBox::warning(this, "Error", "Échec de l'ajout du contracteur.");
    }
}

void MainWindow::on_supprimerContracteurcontracteur_clicked() {
    int id = ui->lineEdit_3contracteur->text().toInt();
    if (id == 0) {
        QMessageBox::warning(this, "Input Error", "L'ID pour supprimer est vide.");
        return;
    }
    if (currentContracteur.supprimer(id)) {
        currentContracteur.reassignIds();
        QMessageBox::information(this, "Success", "Contracteur supprimé avec succès.");
        fillTableWidget2();
        ui->lineEdit_3contracteur->clear();
        ui->lineEdit_2contracteur->clear();
        ui->lineEdit_13contracteur->clear();
        ui->lineEdit_7contracteur->clear();
        ui->lineEdit_4contracteur->clear();
        ui->lineEdit_5contracteur->clear();
        ui->comboBoxcontracteur->setCurrentIndex(0);
    } else {
        QMessageBox::warning(this, "Error", "Échec de la suppression du contracteur.");
    }
}

void MainWindow::on_modifyContracteurButtoncontracteur_clicked() {
    int id = ui->lineEdit_3contracteur->text().toInt();
    if (id == 0) {
        QMessageBox::warning(this, "Input Error", "L'ID pour modifier est vide.");
        return;
    }
    if (ui->lineEdit_2contracteur->text().isEmpty()) {
        QMessageBox::warning(this, "Input Error", "Nom est vide !");
        return;
    }
    if (ui->lineEdit_13contracteur->text().isEmpty()) {
        QMessageBox::warning(this, "Input Error", "Prenom est vide !");
        return;
    }
    QString telephone = ui->lineEdit_7contracteur->text();
    if (telephone.isEmpty()) {
        QMessageBox::warning(this, "Input Error", "Telephone est vide !");
        return;
    }
    if (!QRegularExpression("^[0-9]{8}$").match(telephone).hasMatch()) {
        QMessageBox::warning(this, "Input Error", "Le numéro de téléphone doit contenir exactement 8 chiffres !");
        return;
    }
    QString adresse = ui->lineEdit_4contracteur->text();
    if (adresse.isEmpty()) {
        QMessageBox::warning(this, "Input Error", "Adresse est vide !");
        return;
    }
    QString email = ui->lineEdit_5contracteur->text();
    if (email.isEmpty()) {
        QMessageBox::warning(this, "Input Error", "Email est vide !");
        return;
    }
    if (!QRegularExpression("^[\\w.-]+@[\\w.-]+\\.[a-zA-Z]{2,}$").match(email).hasMatch()) {
        QMessageBox::warning(this, "Input Error", "L'email doit être au format something@something.something !");
        return;
    }
    if (ui->comboBoxcontracteur->currentText() == "Domaine") {
        QMessageBox::warning(this, "Input Error", "Veuillez sélectionner un domaine valide !");
        return;
    }

    QString nom = ui->lineEdit_2contracteur->text();
    QString prenom = ui->lineEdit_13contracteur->text();
    QString domaine = ui->comboBoxcontracteur->currentText();

    currentContracteur.setNom(nom);
    currentContracteur.setPrenom(prenom);
    currentContracteur.setTelephone(telephone);
    currentContracteur.setAdresse(adresse);
    currentContracteur.setEmail(email);
    currentContracteur.setDomaine(domaine);

    if (currentContracteur.modifier(id)) {
        QMessageBox::information(this, "Success", "Information du contracteur modifiée avec succès.");
        fillTableWidget2();
        ui->lineEdit_3contracteur->clear();
        ui->lineEdit_2contracteur->clear();
        ui->lineEdit_13contracteur->clear();
        ui->lineEdit_7contracteur->clear();
        ui->lineEdit_4contracteur->clear();
        ui->lineEdit_5contracteur->clear();
        ui->comboBoxcontracteur->setCurrentIndex(0);
    } else {
        QMessageBox::warning(this, "Failure", "Échec de la modification des informations du contracteur.");
    }
}

void MainWindow::on_tableView_2contracteur_itemClicked(const QModelIndex &index) {
    int row = index.row();
    QAbstractItemModel *model = ui->tableView_2contracteur->model();

    // Ensure the model is valid
    if (!model) {
        qDebug() << "Model is null.";
        return;
    }

    // Populate the form fields with the selected row's data
    ui->lineEdit_3contracteur->setText(model->data(model->index(row, 0)).toString()); // ID
    ui->lineEdit_2contracteur->setText(model->data(model->index(row, 1)).toString()); // Nom
    ui->lineEdit_13contracteur->setText(model->data(model->index(row, 2)).toString()); // Prenom
    ui->lineEdit_7contracteur->setText(model->data(model->index(row, 3)).toString()); // Telephone
    ui->lineEdit_4contracteur->setText(model->data(model->index(row, 4)).toString()); // Adresse
    ui->lineEdit_5contracteur->setText(model->data(model->index(row, 5)).toString()); // Email
    ui->comboBoxcontracteur->setCurrentText(model->data(model->index(row, 6)).toString()); // Domaine

    // Load Historique into the spinBox
    ui->spinBoxcontracteur->setValue(model->data(model->index(row, 8)).toInt()); // Historique

    // Highlight the selected row in black
    for (int i = 0; i < model->rowCount(); ++i) {
        for (int j = 0; j < model->columnCount(); ++j) {
            if (i == row) {
                ui->tableView_2contracteur->model()->setData(model->index(i, j), QBrush(Qt::black), Qt::BackgroundRole);
                ui->tableView_2contracteur->model()->setData(model->index(i, j), QBrush(Qt::white), Qt::ForegroundRole);
            } else {
                ui->tableView_2contracteur->model()->setData(model->index(i, j), QBrush(Qt::NoBrush), Qt::BackgroundRole);
                ui->tableView_2contracteur->model()->setData(model->index(i, j), QBrush(Qt::black), Qt::ForegroundRole);
            }
        }
    }
}

void MainWindow::refreshTableWidget2() {
    QSqlQueryModel *model = currentContracteur.afficher();
    ui->tableView_2contracteur->setModel(model);
    ui->tableView_2contracteur->resizeColumnsToContents();
}

void MainWindow::on_annulerButtoncontracteur_clicked() {
    // Clear all input fields
    ui->lineEdit_2contracteur->clear();
    ui->lineEdit_13contracteur->clear();
    ui->lineEdit_3contracteur->clear();
    ui->lineEdit_7contracteur->clear();
    ui->lineEdit_4contracteur->clear();
    ui->lineEdit_5contracteur->clear();
    ui->comboBoxcontracteur->setCurrentIndex(0); // Reset Domaine
    ui->spinBoxcontracteur->setValue(0);         // Reset Historique
}

void MainWindow::on_comboBox_tri_2contracteur_currentIndexChanged(int index) {
    ui->tableView_2contracteur->setModel(nullptr);
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

    ui->tableView_2contracteur->setModel(model);
    ui->tableView_2contracteur->resizeColumnsToContents();
}

void MainWindow::on_chercher_2contracteur_clicked() {
    QString searchText = ui->id_rech_2contracteur->text().trimmed();
    QString searchCriteria = ui->comboBox_2contracteur->currentText();
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

    ui->tableView_2contracteur->setModel(model);
    ui->tableView_2contracteur->resizeColumnsToContents();
}

void MainWindow::on_pdf_2contracteur_clicked() {
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
    ui->graphicsViewcontracteur->setScene(scene);
    ui->graphicsViewcontracteur->show();
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

    QPixmap chartPixmap = ui->graphicsViewcontracteur->grab();
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

void MainWindow::on_generateStatisticsButtoncontracteur_clicked() {
    generateStatistics();
}

void MainWindow::on_exportStatisticsPDFButtoncontracteur_clicked() {
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
        ui->taskslistcontracteur->setModel(model);
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
        ui->treeViewcontracteur->setModel(model);
    }
}

void MainWindow::clearTreeView() {
    QStandardItemModel *model = new QStandardItemModel(this);
    ui->treeViewcontracteur->setModel(model);
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

void MainWindow::on_addtaskcontracteur_clicked() {
    QString task = ui->tasktextcontracteur->text().trimmed();
    if (task.isEmpty()) {
        QMessageBox::warning(this, "Input Error", "Task cannot be empty.");
        return;
    }

    QModelIndex index = ui->contractorlisttablecontracteur->currentIndex();
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

void MainWindow::on_completedtaskcontracteur_clicked() {
    QModelIndex index = ui->taskslistcontracteur->currentIndex();
    if (!index.isValid()) {
        QMessageBox::warning(this, "Selection Error", "Please select a task.");
        return;
    }

    QString task = index.data().toString().split(" (").first();
    QModelIndex contractorIndex = ui->contractorlisttablecontracteur->currentIndex();
    if (!contractorIndex.isValid()) {
        QMessageBox::warning(this, "Selection Error", "Please select a contractor.");
        return;
    }

    int contractorId = contractorIndex.sibling(contractorIndex.row(), 0).data().toInt();
    updateTaskStatus(contractorId, task, "Completed");
    loadTasksForContractor(contractorId);
    populateTreeView(contractorId);
}

void MainWindow::on_rmtaskcontracteur_clicked() {
    QModelIndex index = ui->taskslistcontracteur->currentIndex();
    if (!index.isValid()) {
        QMessageBox::warning(this, "Selection Error", "Please select a task.");
        return;
    }

    QString task = index.data().toString().split(" (").first();
    QModelIndex contractorIndex = ui->contractorlisttablecontracteur->currentIndex();
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

void MainWindow::on_testaffichertodocontracteur_clicked() {
    QModelIndex index = ui->contractorlisttablecontracteur->currentIndex();
    if (!index.isValid()) {
        QMessageBox::warning(this, "Selection Error", "Please select a contractor.");
        return;
    }

    int contractorId = index.sibling(index.row(), 0).data().toInt();
    loadTasksForContractor(contractorId);
}

void MainWindow::on_affichertreecontracteur_clicked() {
    QModelIndex index = ui->tableViewcontracteur->currentIndex();
    if (!index.isValid()) {
        QMessageBox::warning(this, "Selection Error", "Please select a contractor.");
        return;
    }

    int contractorId = index.sibling(index.row(), 0).data().toInt();
    populateTreeView(contractorId);
}

void MainWindow::on_contractorlisttablecontracteur_clicked(const QModelIndex &index) {
    if (!index.isValid()) return;

    int contractorId = index.sibling(index.row(), 0).data().toInt();
    loadTasksForContractor(contractorId);
    populateTreeView(contractorId);
}

/*void MainWindow::on_tabWidgetcontracteur_currentChanged(int index) {
    if (index == 2) { // To-Do List tab
        loadContractorsToTable(ui->contractorlisttablecontracteur);
    } else if (index == 3) { // Tree View tab
        loadContractorsToTable(ui->tableViewcontracteur);
    } else if (index == 4) { // Architect tab
        loadArchitectsToListView();
        updatePresenceView();
    }
}*/

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

    ui->achitectviewcontracteur->setModel(model);
}

/*void MainWindow::readArduinoData()
{
    QByteArray data = ArdCont.read_from_arduino();
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
    ui->presenceviewcontracteur->setModel(model);

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
    ui->presenceviewcontracteur->setModel(model);

    // Debug log to confirm the number of entries
    qDebug() << "Presence view updated with" << model->rowCount() << "entries.";
}

void MainWindow::on_assignCardcontracteur_clicked()
{
    QModelIndex index = ui->achitectviewcontracteur->currentIndex();
    if (!index.isValid()) {
        QMessageBox::warning(this, "Selection Error", "Please select an architect.");
        return;
    }

    QString selectedArchitect = index.data().toString();
    int architectId = selectedArchitect.split(" - ").first().toInt();

    QString cardId = ArdCont.read_from_arduino().trimmed(); // Read RFID card ID
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
            ArdCont.write_to_arduino("OPEN_DOOR"); // Send command to open the door
        }
        updatePresenceView();
    } else {
        QMessageBox::warning(this, "Error", "Failed to update presence.");
    }
}

void MainWindow::on_togglePresencecontracteur_clicked()
{
    QModelIndex index = ui->achitectviewcontracteur->currentIndex();
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
}*/

void MainWindow::on_pushButton_6contracteur_clicked() {
    // Assuming your work is in the "Contracteurs" tab (index 4 in the QTabWidget)
    ui->tabWidgetcontracteur->setCurrentIndex(4);
}

///////////////////////////// contrat/////////////////////////



void MainWindow::populateTableWidget(QSqlQueryModel* model) {
    qDebug() << "Populating table widget with model";  // Debug message
    ui->tableWidgetcontrat->setRowCount(model->rowCount());
    ui->tableWidgetcontrat->setColumnCount(model->columnCount());
    ui->tableWidgetcontrat->setHorizontalHeaderLabels({
        "ID Contrat", "Montant Total", "Date Début", "Date Fin", "Statut Paiement", "ID Projet", "ID Client"
    });


    for (int row = 0; row < model->rowCount(); ++row) {
        for (int col = 0; col < model->columnCount(); ++col) {
            QTableWidgetItem* item = new QTableWidgetItem(model->data(model->index(row, col)).toString());
            ui->tableWidgetcontrat->setItem(row, col, item);
        }
    }
}


void MainWindow::afficherContrats()
{
    contrats c;
    QSqlQueryModel* model = c.afficher();

    ui->tableWidgetcontrat->setRowCount(model->rowCount());
    ui->tableWidgetcontrat->setColumnCount(model->columnCount());

    // Optionnel : définir les en-têtes de colonnes selon la base
    for (int col = 0; col < model->columnCount(); ++col) {
        ui->tableWidgetcontrat->setHorizontalHeaderItem(col, new QTableWidgetItem(model->headerData(col, Qt::Horizontal).toString()));
    }

    // Remplir le tableau
    for (int row = 0; row < model->rowCount(); ++row) {
        for (int col = 0; col < model->columnCount(); ++col) {
            QString data = model->data(model->index(row, col)).toString();
            ui->tableWidgetcontrat->setItem(row, col, new QTableWidgetItem(data));
        }
    }

    delete model; // Libérer la mémoire si ce n'est pas utilisé ailleurs
}

void MainWindow::handleKeypadInput() {
    QByteArray data = A.read_from_arduino();
    if (!data.isEmpty()) {
        QString idProjet = QString(data).trimmed();
        QSqlQuery query;
        query.prepare("SELECT ECHEANCE FROM PROJETS WHERE ID_PROJET = :id");
        query.bindValue(":id", idProjet);

        if (query.exec()) {
            if (query.next()) {
                QDate dateEcheance = query.value(0).toDate();
                QDate dateActuelle = QDate::currentDate();
                int joursRestants = dateActuelle.daysTo(dateEcheance);

                if (joursRestants <= 30) {
                    A.write_to_arduino("2"); // rouge + buzzer
                    QMessageBox::critical(this, "Échéance proche", "Attention : échéance dans " + QString::number(joursRestants) + " jours.");
                } else {
                    A.write_to_arduino("1"); // verte
                    QMessageBox::information(this, "Échéance", "Encore " + QString::number(joursRestants) + " jours restants.");
                }
            } else {
                A.write_to_arduino("3"); // orangé
                QMessageBox::warning(this, "Projet inexistant", "Aucun projet avec cet ID.");
            }
        } else {
            QMessageBox::critical(this, "Erreur SQL", "Erreur lors de l'exécution de la requête.");
        }
    }
}




void MainWindow::on_ajoutercontrat_clicked() {
    qDebug() << "Ajout du contrat";  // Debug message

    contrats c(ui->id_contrat->text().toInt(), ui->montantcontrat->text().toDouble(),
               ui->date_debutcontrat->date().toString("yyyy-MM-dd"),
               ui->date_fincontrat->date().toString("yyyy-MM-dd"),
               ui->statutcontrat->currentText(), ui->iclient_contrat->text().toInt(), ui->iprojet_contrat->text().toInt());

    // Check if data is correct
    qDebug() << "ID: " << ui->id_contrat->text().toInt();
    qDebug() << "Montant: " << ui->montantcontrat->text().toDouble();

    if (c.ajouter()) {
        QMessageBox::information(this, "Success", "Contrat ajouté avec succès.");
        populateTableWidget(currentContrat.afficher());
    } else {
        QMessageBox::critical(this, "Error", "Erreur lors de l'ajout du contrat.");
    }
}


void MainWindow::on_modifiercontrat_clicked() {
    contrats c(ui->id_contrat->text().toInt(), ui->montantcontrat->text().toDouble(),
               ui->date_debutcontrat->date().toString("yyyy-MM-dd"),
               ui->date_fincontrat->date().toString("yyyy-MM-dd"),
               ui->statutcontrat->currentText(), ui->iclient_contrat->text().toInt(), ui->iprojet_contrat->text().toInt());

    if (c.modifier(ui->id_contrat->text().toInt())) {
        QMessageBox::information(this, "Succès", "Contrat modifié avec succès.");
        populateTableWidget(currentContrat.afficher());
    } else {
        QMessageBox::critical(this, "Erreur", "Échec de la modification.");
    }
}

void MainWindow::on_supprimercontrat_clicked() {
    int id = ui->id_contrat->text().toInt();
    if (currentContrat.supprimer(id)) {
        QMessageBox::information(this, "Succès", "Contrat supprimé.");
        populateTableWidget(currentContrat.afficher());
    } else {
        QMessageBox::critical(this, "Erreur", "Échec de suppression.");
    }
}
void MainWindow::on_tableWidgetcontrat_cellClicked(int row, int column)
{
    QString id = ui->tableWidgetcontrat->item(row, 0)->text();
    QString montant = ui->tableWidgetcontrat->item(row, 1)->text();
    QDate date_Debut = QDate::fromString(ui->tableWidgetcontrat->item(row, 2)->text(), "yyyy-MM-dd");
    QDate date_Fin = QDate::fromString(ui->tableWidgetcontrat->item(row, 3)->text(), "yyyy-MM-dd");
    QString statut = ui->tableWidgetcontrat->item(row, 4)->text();
    QString id_Projet = ui->tableWidgetcontrat->item(row, 5)->text();
    QString id_client = ui->tableWidgetcontrat->item(row, 6)->text();

    ui->id_contrat->setText(id);
    ui->montantcontrat->setText(montant);
    ui->date_debutcontrat->setDate(date_Debut);
    ui->date_fincontrat->setDate(date_Fin);
    ui->statutcontrat->setCurrentText(statut);
    ui->iprojet_contrat->setText(id_Projet);
    ui->iclient_contrat->setText(id_client);
}
void MainWindow::on_tributtoncontrat_clicked() {
    QString critere = ui->tricontrat->currentText();
    QSqlQueryModel *triModel = currentContrat.trier(critere);
    populateTableWidget(triModel);
}
void MainWindow::on_cherchercontrat_clicked() {
    QString idText = ui->id_rechcontrat->text();
    if (idText.isEmpty()) {
        QMessageBox::warning(this, "Champ vide", "Veuillez entrer un ID.");
        return;
    }

    int id = idText.toInt();
    QSqlQueryModel* resultModel = currentContrat.rechercher(id);
    if (resultModel->rowCount() == 0) {
        QMessageBox::information(this, "Aucun résultat", "Aucun contrat trouvé pour cet ID.");
    }

    populateTableWidget(resultModel);
}
void MainWindow::on_statscontrat_clicked() {
    QMap<QString, int> stats = currentContrat.statistiquesStatut();

    QPieSeries *series = new QPieSeries();

    int total = 0;
    for (auto count : stats.values()) total += count;

    for (auto it = stats.begin(); it != stats.end(); ++it) {
        if (it.value() > 0) {
            double percent = (double)it.value() / total * 100.0;
            series->append(it.key() + QString(" (%1%)").arg(percent, 0, 'f', 1), it.value());
        }
    }

    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Répartition des Statuts de Paiement");
    chart->legend()->setAlignment(Qt::AlignRight);

    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    QMainWindow *statsWindow = new QMainWindow(this);
    statsWindow->setWindowTitle("Statistiques Paiement");
    statsWindow->setCentralWidget(chartView);
    statsWindow->resize(600, 400);
    statsWindow->show();
}

void MainWindow::on_exportercontrat_clicked() {
    QString fileName = QFileDialog::getSaveFileName(this, "Exporter en PDF", "", "*.pdf");

    if (fileName.isEmpty())
        return;

    QPdfWriter pdfWriter(fileName);
    pdfWriter.setPageSize(QPageSize(QPageSize::A4));
    pdfWriter.setResolution(300);

    QPainter painter(&pdfWriter);
    painter.setFont(QFont("Times", 24)); // Texte plus grand (24pt)

    int margin = 80;                  // Plus de marge
    int x = margin;
    int y = margin + 50;              // Décalage pour le titre
    int rowHeight = 80;               // Augmenter encore la hauteur des lignes
    int columnWidth = 300;            // Largeur des colonnes plus large

    // Dessiner le titre au centre
    painter.setFont(QFont("Times", 28)); // Taille plus grande pour le titre
    QString title = "Liste des Contrats";
    painter.drawText(pdfWriter.width() / 2 - painter.fontMetrics().horizontalAdvance(title) / 2, y, title);
    y += 100; // Décalage après le titre

    QSqlQueryModel* model = currentContrat.afficher();

    int cols = model->columnCount();
    int rows = model->rowCount();

    // Calcul de la largeur totale pour centrer les données
    int totalWidth = cols * columnWidth;
    int centerX = (pdfWriter.width() - totalWidth) / 2;

    // Dessiner les en-têtes avec couleur
    painter.setFont(QFont("Times", 18)); // Taille plus petite pour les en-têtes
    for (int col = 0; col < cols; ++col) {
        QString header = model->headerData(col, Qt::Horizontal).toString();
        QRect rect(centerX + col * columnWidth, y, columnWidth, rowHeight);

        painter.setBrush(QBrush(Qt::lightGray)); // Couleur de fond des en-têtes
        painter.drawRect(rect);

        painter.setPen(QPen(Qt::black)); // Couleur du texte
        painter.drawText(rect.adjusted(10, 10, -10, -10), Qt::AlignLeft | Qt::AlignVCenter, header);
    }

    y += rowHeight;

    // Contenu des contrats avec plus d'espace entre chaque ligne
    painter.setFont(QFont("Times", 16)); // Police un peu plus petite pour les données
    for (int row = 0; row < rows; ++row) {
        for (int col = 0; col < cols; ++col) {
            QString data = model->data(model->index(row, col)).toString();
            QRect rect(centerX + col * columnWidth, y, columnWidth, rowHeight);
            painter.setBrush(QBrush(Qt::white)); // Couleur de fond des données
            painter.drawRect(rect);
            painter.setPen(QPen(Qt::black)); // Couleur du texte
            painter.drawText(rect.adjusted(10, 10, -10, -10), Qt::AlignLeft | Qt::AlignVCenter, data);
        }
        y += rowHeight;

        // Nouvelle page si besoin
        if (y + rowHeight > pdfWriter.height() - margin) {
            pdfWriter.newPage();
            y = margin + 50;

            // Redessiner le titre centré
            painter.setFont(QFont("Times", 28));
            painter.drawText(pdfWriter.width() / 2 - painter.fontMetrics().horizontalAdvance(title) / 2, y, title);
            y += 100;

            // Redessiner l'en-tête
            for (int col = 0; col < cols; ++col) {
                QString header = model->headerData(col, Qt::Horizontal).toString();
                QRect rect(centerX + col * columnWidth, y, columnWidth, rowHeight);
                painter.setBrush(QBrush(Qt::lightGray)); // Couleur de fond des en-têtes
                painter.drawRect(rect);
                painter.setPen(QPen(Qt::black)); // Couleur du texte
                painter.drawText(rect.adjusted(10, 10, -10, -10), Qt::AlignLeft | Qt::AlignVCenter, header);
            }
            y += rowHeight;
        }
    }

    painter.end();
    QMessageBox::information(this, "PDF", "Exportation terminée avec succès !");
}










void MainWindow::on_pushButton_email_clicked()
{
    QString subject = "Mise à jour importante - Contrats Innovarch";
    QString body = "Bonjour,\n\n"
                   "Nous vous rappelons que la date de fin de votre contrat approche. Celui-ci prendra fin dans une semaine.\n\n"
                   "Nous vous invitons à prendre les dispositions nécessaires.\n\n"
                   "Cordialement,\n"
                   "L’équipe Innovarch";


    mailer mail;
    int result = mail.sendEmail("youssef.bensaid@esprit.tn", subject, body); // ← mets ton adresse

    if (result == 0) {
        QMessageBox::information(this, "Succès", "Email envoyé avec succès !");
    } else {
        QMessageBox::critical(this, "Erreur", "Échec de l'envoi de l'email.");
    }
}




///////////// ons maram//////////////////
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

void MainWindow::on_pushButton_cl_clicked()
{
    ui->mainStack->setCurrentIndex(4);

}

void MainWindow::on_pushButton_4_clicked()
{
    ui->mainStack->setCurrentIndex(4);

}
void MainWindow::on_pushButton_ct_clicked()
{
    ui->mainStack->setCurrentIndex(5);

}

void MainWindow::on_pushButton_6_clicked()
{
    ui->mainStack->setCurrentIndex(5);

}
void MainWindow::on_pushButton_5_clicked()
{
    ui->mainStack->setCurrentIndex(6);

}
void MainWindow::on_pushButton_contrats_clicked()
{
    ui->mainStack->setCurrentIndex(6);

}


/////////////bibi

void MainWindow::on_pushButton_proj_clicked()
{
    ui->mainStack->setCurrentIndex(3);

}


void MainWindow::on_pushButton_3_clicked()
{
    ui->mainStack->setCurrentIndex(3);

}


void MainWindow::on_pushButton_8_clicked()
{
    ui->mainStack->setCurrentIndex(2);

}


void MainWindow::on_pushButton_11_clicked()
{
    ui->mainStack->setCurrentIndex(0);

}

void MainWindow::on_pushButton_9_clicked()
{
    ui->mainStack->setCurrentIndex(4);

}
void MainWindow::on_pushButton_13_clicked()
{
    ui->mainStack->setCurrentIndex(5);

}
void MainWindow::on_pushButton_12_clicked()
{
    ui->mainStack->setCurrentIndex(6);

}

//////////selim
void MainWindow::on_pushButton_21_clicked()
{
    ui->mainStack->setCurrentIndex(2);

}


void MainWindow::on_pushButton_cl_3_clicked()
{
    ui->mainStack->setCurrentIndex(4);

}


void MainWindow::on_pushButton_contrats_3_clicked()
{
    ui->mainStack->setCurrentIndex(6);

}


void MainWindow::on_pushButton_ct_3_clicked()
{
    ui->mainStack->setCurrentIndex(5);

}

void MainWindow::on_pushButton_proj_3_clicked()
{
    ui->mainStack->setCurrentIndex(3);

}

void MainWindow::on_pushButton_r_3_clicked()
{
    ui->mainStack->setCurrentIndex(0);

}
////////// med hedi///////

void MainWindow::on_pushButton_24_clicked()
{
    ui->mainStack->setCurrentIndex(2);

}


void MainWindow::on_pushButton_cl_6_clicked()
{
    ui->mainStack->setCurrentIndex(4);

}


void MainWindow::on_pushButton_contrats_6_clicked()
{
    ui->mainStack->setCurrentIndex(6);

}


void MainWindow::on_pushButton_ct_6_clicked()
{
    ui->mainStack->setCurrentIndex(5);

}

void MainWindow::on_pushButton_proj_6_clicked()
{
    ui->mainStack->setCurrentIndex(3);

}

void MainWindow::on_pushButton_r_6_clicked()
{
    ui->mainStack->setCurrentIndex(0);

}
//////////// desa/////////////
void MainWindow::on_pushButton_25_clicked()
{
    ui->mainStack->setCurrentIndex(2);

}


void MainWindow::on_pushButton_cl_7_clicked()
{
    ui->mainStack->setCurrentIndex(4);

}


void MainWindow::on_pushButton_contrats_7_clicked()
{
    ui->mainStack->setCurrentIndex(6);

}


void MainWindow::on_pushButton_ct_7_clicked()
{
    ui->mainStack->setCurrentIndex(5);

}

void MainWindow::on_pushButton_proj_7_clicked()
{
    ui->mainStack->setCurrentIndex(3);

}

void MainWindow::on_pushButton_r_7_clicked()
{
    ui->mainStack->setCurrentIndex(0);

}
