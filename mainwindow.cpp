#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QSqlError>
#include <QDebug>
#include <QPdfWriter>
#include <QPainter>
#include <QFileDialog>
#include <QMessageBox>
#include <QtCharts>
#include <QChartView>
#include <QPieSeries>
#include <QSqlQuery>
#include <QMap>
#include "sms.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->tableView, &QTableView::clicked, this, &MainWindow::on_tableView_itemClicked);
    connect(ui->ajouter, &QPushButton::clicked, this, &MainWindow::on_addClientButton_clicked);
    connect(ui->annuler, &QPushButton::clicked, this, &MainWindow::on_annulerButton_clicked);
    connect(ui->supprimer, &QPushButton::clicked, this, &MainWindow::on_supprimerClient_clicked);
    connect(ui->modifier, &QPushButton::clicked, this, &MainWindow::on_modifyClientButton_clicked);
    connect(ui->chercher_2, &QPushButton::clicked, this, &MainWindow::on_pushButtonRecherche_clicked);
    connect(ui->TrierButton, &QPushButton::clicked, this, &MainWindow::on_trierClientButton_clicked);
    connect(ui->pdf_2, &QPushButton::clicked, this, &MainWindow::on_pdfClientButton_clicked);
    connect(ui->statButton, &QPushButton::clicked, this, &MainWindow::on_statButton_clicked);
    connect(ui->sms, &QPushButton::clicked, this, &MainWindow::on_btnEnvoyerSMS_clicked);





    qDebug() << "Calling fillTableWidget() at startup";
    fillTableWidget();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::fillTableWidget() {
    qDebug() << "Executing fillTableWidget()";
    QSqlQueryModel *model = currentClient.afficher();

    if (model) {
        ui->tableView->setModel(model);
        ui->tableView->resizeColumnsToContents();
        qDebug() << "Table widget filled successfully";
    } else {
        qDebug() << "Failed to fill table widget";
    }
}

void MainWindow::on_addClientButton_clicked()
{
    if (ui->lineEdit_2->text().isEmpty()) {
        QMessageBox::warning(this, "Input Error", "Nom vide !!");
        return;
    }

    if (ui->lineEdit_4->text().isEmpty()) {
        QMessageBox::warning(this, "Input Error", "Prénom vide !!");
        return;
    }

    QString email = ui->lineEdit_6->text();
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

    QString nom = ui->lineEdit_2->text();
    QString prenom = ui->lineEdit_4->text();
    QString telephone = ui->lineEdit_7->text();
    QString adresse = ui->lineEdit_5->text();
    QString sexe = ui->comboBox->currentText();
    int id_projet = ui->lineEdit->text().toInt();


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
        fillTableWidget();

        ui->lineEdit_2->clear();
        ui->lineEdit_4->clear();
        ui->lineEdit_6->clear();
        ui->lineEdit_7->clear();
        ui->lineEdit_5->clear();
        ui->lineEdit->clear();
        ui->comboBox->setCurrentIndex(0);
    } else {
        QMessageBox::warning(this, "Error", "Échec de l'ajout du client.");
    }
}

void MainWindow::on_supprimerClient_clicked() {
    int id = ui->id_rech_2->text().toInt();

    if (id == 0) {
        QMessageBox::warning(this, "Input Error", "L'ID pour supprimer est vide.");
        return;
    }

    if (currentClient.supprimer(id)) {
        QMessageBox::information(this, "Success", "Client supprimé avec succès.");
        fillTableWidget();

        ui->id_rech_2->clear();
        ui->lineEdit_2->clear();
        ui->lineEdit_4->clear();
        ui->lineEdit_6->clear();
        ui->lineEdit_7->clear();
        ui->lineEdit_5->clear();
        ui->lineEdit->clear();
        ui->comboBox->setCurrentIndex(0);
    } else {
        QMessageBox::warning(this, "Error", "Échec de la suppression du client.");
    }
}

void MainWindow::on_modifyClientButton_clicked()
{
    int id = ui->id_rech_2->text().toInt();
    if (id == 0) {
        QMessageBox::warning(this, "Input Error", "L'ID pour modifier est vide.");
        return;
    }

    QString nom = ui->lineEdit_2->text();
    QString prenom = ui->lineEdit_4->text();

    QString telephone = ui->lineEdit_7->text();

    QString adresse = ui->lineEdit_5->text();
    QString email = ui->lineEdit_6->text();
    QString sexe = ui->comboBox->currentText();
    int id_projet = ui->lineEdit->text().toInt();

    currentClient = Clients(id, nom, prenom, email, telephone, adresse, sexe,id_projet);

    if (currentClient.modifier(id)) {
        QMessageBox::information(this, "Success", "Client modifié avec succès.");
        fillTableWidget();

        ui->id_rech_2->clear();
        ui->lineEdit_2->clear();
        ui->lineEdit_4->clear();
        ui->lineEdit_6->clear();
        ui->lineEdit_7->clear();
        ui->lineEdit_5->clear();
        ui->lineEdit->clear();
        ui->comboBox->setCurrentIndex(0);
    } else {
        QMessageBox::warning(this, "Failure", "Échec de la modification du client.");
    }
}

void MainWindow::on_tableView_itemClicked(const QModelIndex &index)
{
    int row = index.row();

    QString id = ui->tableView->model()->data(ui->tableView->model()->index(row, 0)).toString();
    QString nom = ui->tableView->model()->data(ui->tableView->model()->index(row, 1)).toString();
    QString prenom = ui->tableView->model()->data(ui->tableView->model()->index(row, 2)).toString();
    QString telephone = ui->tableView->model()->data(ui->tableView->model()->index(row, 3)).toString();
    QString adresse = ui->tableView->model()->data(ui->tableView->model()->index(row, 4)).toString();
    QString email = ui->tableView->model()->data(ui->tableView->model()->index(row, 5)).toString();
    QString sexe = ui->tableView->model()->data(ui->tableView->model()->index(row, 6)).toString();
    QString id_projet = ui->tableView->model()->data(ui->tableView->model()->index(row, 7)).toString();

    ui->id_rech_2->setText(id);
    ui->lineEdit_2->setText(nom);
    ui->lineEdit_4->setText(prenom);
    ui->lineEdit_7->setText(telephone);
    ui->lineEdit_5->setText(adresse);
    ui->lineEdit_6->setText(email);
    ui->lineEdit->setText(id_projet);
    ui->comboBox->setCurrentText(sexe);

    // ⚠️ Envoi SMS ici automatiquement

}


void MainWindow::refreshTableWidget() {
    QSqlQueryModel *model = currentClient.afficher();

    ui->tableView->setModel(model);
    ui->tableView->resizeColumnsToContents();
}

void MainWindow::on_annulerButton_clicked() {
    ui->lineEdit_2->clear();
    ui->lineEdit_4->clear();
    ui->lineEdit_6->clear();
    ui->lineEdit_7->clear();
    ui->lineEdit_5->clear();
    ui->lineEdit->clear();
    ui->comboBox->setCurrentIndex(0);
}

void MainWindow::on_pushButtonRecherche_clicked() {
    QString searchText = ui->id_rech_2->text().trimmed();
    QString searchCriteria = ui->comboBox_2->currentText();
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
    QString triCritere = ui->comboBox_tri_2->currentText();
    QString ordre = ui->comboBox_tri_3->currentText();

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



void MainWindow::on_statButton_clicked()
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
    QSize viewSize = ui->stat->size();
    int chartW = viewSize.width() * 0.7;
    int chartH = viewSize.height() * 0.7;
    chartView->setFixedSize(chartW, chartH);

    if (ui->stat->scene()) {
        delete ui->stat->scene();
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

    ui->stat->setScene(scene);
    ui->stat->setSceneRect(scene->sceneRect()); // 🔒 Lock the scene size

    // 🔧 Optional: Disable scrollbars or scaling
    ui->stat->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->stat->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->stat->setAlignment(Qt::AlignLeft | Qt::AlignTop); // avoid auto-centering
}

void MainWindow::on_btnEnvoyerSMS_clicked()
{
    int idClient = ui->id_rech_2->text().toInt();

    SMS sms;
    bool success = sms.envoyerStatutProjetAuClient(idClient);


    if (success) {
        QMessageBox::information(this, "Succès", "SMS envoyé au client !");
    } else {
        QMessageBox::warning(this, "Erreur", "Échec de l’envoi du SMS.");
    }
}



