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
#include <QDebug>  // Ajout de qDebug
#include <QtCharts/QChartView>
#include <QtCharts/QPieSeries>
#include <QtCharts/QChart>
#include "mailer.h"
#include <QPdfWriter>
#include <QPainter>
#include <QFileDialog>
#include <QSqlQueryModel>
#include <QSqlRecord>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "arduino.h"
#include <QDate>
#include <QSqlQuery>
#include <QDebug>





void MainWindow::populateTableWidget(QSqlQueryModel* model) {
    qDebug() << "Populating table widget with model";  // Debug message
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
    connect(ui->btnAfficher, &QPushButton::clicked, this, &MainWindow::afficherContrats);
    A.connect_arduino();

    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &MainWindow::handleKeypadInput);
    timer->start(500); // vérifie toutes les 500ms





    // Correct signal-slot connections
    connect(ui->tableWidget, &QTableWidget::cellClicked, this, &MainWindow::on_tableWidget_cellClicked);
    connect(ui->tributton, &QPushButton::clicked, this, &MainWindow::on_tributton_clicked);
    connect(ui->chercher, &QPushButton::clicked, this, &MainWindow::on_chercher_clicked);
    connect(ui->pushbutton_Email, &QPushButton::clicked, this, &MainWindow::on_pushButton_email_clicked);
    connect(ui->exporter, &QPushButton::clicked, this, &MainWindow::on_exporter_clicked);










}
MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::afficherContrats()
{
    contrats c;
    QSqlQueryModel* model = c.afficher();

    ui->tableWidget->setRowCount(model->rowCount());
    ui->tableWidget->setColumnCount(model->columnCount());

    // Optionnel : définir les en-têtes de colonnes selon la base
    for (int col = 0; col < model->columnCount(); ++col) {
        ui->tableWidget->setHorizontalHeaderItem(col, new QTableWidgetItem(model->headerData(col, Qt::Horizontal).toString()));
    }

    // Remplir le tableau
    for (int row = 0; row < model->rowCount(); ++row) {
        for (int col = 0; col < model->columnCount(); ++col) {
            QString data = model->data(model->index(row, col)).toString();
            ui->tableWidget->setItem(row, col, new QTableWidgetItem(data));
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




void MainWindow::on_ajouter_clicked() {
    qDebug() << "Ajout du contrat";  // Debug message

    contrats c(ui->id->text().toInt(), ui->montant->text().toDouble(),
               ui->date_debut->date().toString("yyyy-MM-dd"),
               ui->date_fin->date().toString("yyyy-MM-dd"),
               ui->status_2->currentText(), ui->iclient_2->text().toInt(), ui->iclient->text().toInt());

    // Check if data is correct
    qDebug() << "ID: " << ui->id->text().toInt();
    qDebug() << "Montant: " << ui->montant->text().toDouble();

    if (c.ajouter()) {
        QMessageBox::information(this, "Success", "Contrat ajouté avec succès.");
        populateTableWidget(currentContrat.afficher());
    } else {
        QMessageBox::critical(this, "Error", "Erreur lors de l'ajout du contrat.");
    }
}


void MainWindow::on_modifier_clicked() {
    contrats c(ui->id->text().toInt(), ui->montant->text().toDouble(),
               ui->date_debut->date().toString("yyyy-MM-dd"),
               ui->date_fin->date().toString("yyyy-MM-dd"),
               ui->status_2->currentText(), ui->iclient_2->text().toInt(), ui->iclient->text().toInt());

    if (c.modifier(ui->id->text().toInt())) {
        QMessageBox::information(this, "Succès", "Contrat modifié avec succès.");
        populateTableWidget(currentContrat.afficher());
    } else {
        QMessageBox::critical(this, "Erreur", "Échec de la modification.");
    }
}

void MainWindow::on_supprimer_clicked() {
    int id = ui->id->text().toInt();
    if (currentContrat.supprimer(id)) {
        QMessageBox::information(this, "Succès", "Contrat supprimé.");
        populateTableWidget(currentContrat.afficher());
    } else {
        QMessageBox::critical(this, "Erreur", "Échec de suppression.");
    }
}
void MainWindow::on_tableWidget_cellClicked(int row, int column)
{
    QString id = ui->tableWidget->item(row, 0)->text();
    QString montant = ui->tableWidget->item(row, 1)->text();
    QDate date_Debut = QDate::fromString(ui->tableWidget->item(row, 2)->text(), "yyyy-MM-dd");
    QDate date_Fin = QDate::fromString(ui->tableWidget->item(row, 3)->text(), "yyyy-MM-dd");
    QString statut = ui->tableWidget->item(row, 4)->text();
    QString id_Projet = ui->tableWidget->item(row, 5)->text();
    QString id_client = ui->tableWidget->item(row, 6)->text();

    ui->id->setText(id);
    ui->montant->setText(montant);
    ui->date_debut->setDate(date_Debut);
    ui->date_fin->setDate(date_Fin);
    ui->status_2->setCurrentText(statut);
    ui->iclient->setText(id_Projet);
    ui->iclient_2->setText(id_client);
}
void MainWindow::on_tributton_clicked() {
    QString critere = ui->tricombobox->currentText();
    QSqlQueryModel *triModel = currentContrat.trier(critere);
    populateTableWidget(triModel);
}
void MainWindow::on_chercher_clicked() {
    QString idText = ui->id_rech->text();
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
void MainWindow::on_stats_clicked() {
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

void MainWindow::on_exporter_clicked() {
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

