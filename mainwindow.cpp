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

<<<<<<< Updated upstream
=======

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

void MainWindow::on_pushButton_contrats_clicked()
{
    ui->mainStack->setCurrentIndex(4);

}
void MainWindow::on_pushButton_11_clicked()
{
    ui->mainStack->setCurrentIndex(0);

}

>>>>>>> Stashed changes
