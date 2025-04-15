#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QSqlError>
#include <QMessageBox>
#include "architechtes.h"
#include <QRegularExpression>
#include <QRegularExpressionValidator>
#include <QDebug>
#include <QtCharts/QPieSeries>
#include <QtCharts/QPieSlice>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QChartView>
#include <QtCharts/QChart>
#include <QSqlQuery>
#include <QDebug>
#include <QGraphicsScene>
#include <QPainter>
#include <QColor>
#include <QtCharts/QChartView>
#include <QtCharts/QChart>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QBarCategoryAxis>  // Assurez-vous que cette ligne est présente
#include <QtCharts/QValueAxis>
#include <QtCharts/QChartView>
#include <QtCharts/QPieSeries>
#include <QtCharts/QPieSlice>
#include <QtCharts>
#include <QPdfWriter>
#include <QPainter>
#include <QFileDialog>
#include <QMessageBox>
#include <QTableWidget>
#include "dialog.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent, const QString &userRole)
    : QMainWindow(parent),
      ui(new Ui::MainWindow),
      m_userRole(userRole)
{
    ui->setupUi(this);
    setupTabsBasedOnRole();

    // Remplir le tableau avec les données au chargement de la fenêtre
    fillTableWidget();
    connect(ui->tableWidget, &QTableWidget::itemClicked, this, &MainWindow::on_tableWidget_itemClicked);

    connect(ui->ajouter, &QPushButton::clicked, this, &MainWindow::on_addEmployeeButton_clicked);
    connect(ui->annuler, &QPushButton::clicked, this, &MainWindow::on_supprimerEmploye_clicked);
    connect(ui->refresh, &QPushButton::clicked, this, &MainWindow::on_refreshButton_clicked);
    connect(ui->modifier, &QPushButton::clicked, this, &MainWindow::on_modifyEmployeeButton_clicked);
    connect(ui->chercher_2, &QPushButton::clicked, this, &MainWindow::on_rechercherButton_clicked);
    connect(ui->comboBox_tri_3, QOverload<int>::of(&QComboBox::currentIndexChanged),
                this, &MainWindow::on_comboBox_tri_3_currentIndexChanged);
    connect(ui->pdf_2, &QPushButton::clicked, this, &MainWindow::on_pdf_2_clicked);

    // Appeler la fonction pour afficher les statistiques des genres
    displayGenderStatistics();
}
void MainWindow::setupTabsBasedOnRole()
{
    QTabWidget* mainTabWidget = findChild<QTabWidget*>("aceuille_2");
    if (!mainTabWidget) {
        qWarning() << "Main TabWidget not found!";
        return;
    }

    if (m_userRole != "Directeur") {
        // Keep only the "Statistique et demande de congés" tab
        for (int i = mainTabWidget->count() - 1; i >= 0; --i) {
            if (mainTabWidget->widget(i)->objectName() != "tab_7") {
                mainTabWidget->removeTab(i);
            }
        }
    }
}
MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::fillTableWidget() {
    // Assuming 'emp.afficher()' returns a QSqlQueryModel with data in the correct order.
    QSqlQueryModel *model = emp.afficher();  // Fetch the data from the database.

    // Clear any existing data in the table widget
    ui->tableWidget->clearContents();
    ui->tableWidget->setRowCount(0);

    // Set the correct column count (ID + other fields)
    ui->tableWidget->setColumnCount(8);  // 8 columns (ID, Nom, Prenom, Date, Poste, Email, Salaire, Sexe)

    // Set the column headers
    ui->tableWidget->setHorizontalHeaderLabels({"ID", "Nom", "Prenom", "Date", "Poste", "Email", "Salaire", "Sexe"});

    // Loop through the model and populate the table widget
    for (int row = 0; row < model->rowCount(); ++row) {
        ui->tableWidget->insertRow(row);

        // Fetch and set each column's data in the right column of the table
        ui->tableWidget->setItem(row, 0, new QTableWidgetItem(model->data(model->index(row, 0)).toString())); // ID
        ui->tableWidget->setItem(row, 1, new QTableWidgetItem(model->data(model->index(row, 1)).toString())); // Nom
        ui->tableWidget->setItem(row, 2, new QTableWidgetItem(model->data(model->index(row, 2)).toString())); // Prenom
        ui->tableWidget->setItem(row, 3, new QTableWidgetItem(model->data(model->index(row, 6)).toString())); // Date
        ui->tableWidget->setItem(row, 4, new QTableWidgetItem(model->data(model->index(row, 4)).toString())); // Poste
        ui->tableWidget->setItem(row, 5, new QTableWidgetItem(model->data(model->index(row, 3)).toString())); // Email
        ui->tableWidget->setItem(row, 6, new QTableWidgetItem(model->data(model->index(row, 7)).toString())); // Salaire
        ui->tableWidget->setItem(row, 7, new QTableWidgetItem(model->data(model->index(row, 5)).toString())); // Sexe
    }

    // Resize the columns to fit the content
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
void MainWindow::displayGenderStatistics() {
    // 1. Récupération des données
    QMap<QString, int> stats = emp.getGenderStats();

    // Déclarer maleCount et femaleCount AVANT de les utiliser
    int maleCount = stats.value("m", 0);  // Déclaration correcte
    int femaleCount = stats.value("f", 0); // Déclaration correcte
    int total = maleCount + femaleCount;

    qDebug() << "[Debug] Hommes:" << maleCount << "| Femmes:" << femaleCount;

    if(total == 0) {
        QGraphicsScene *scene = new QGraphicsScene();
        QLabel *label = new QLabel("Aucune donnée disponible\n(Vérifiez la connexion à la base)");
        label->setAlignment(Qt::AlignCenter);
        label->setStyleSheet("font-size: 14px; color: #FF0000;");
        scene->addWidget(label);
        ui->pie->setScene(scene);
        return;
    }

    // 4. Création du diagramme
    QPieSeries *series = new QPieSeries();

    // 5. Ajout des tranches avec style
    if(maleCount > 0) {
        QPieSlice *maleSlice = series->append("Hommes", maleCount);
        maleSlice->setColor(QColor("#3498db")); // Bleu
        maleSlice->setLabelVisible(true);
    }

    if(femaleCount > 0) {
        QPieSlice *femaleSlice = series->append("Femmes", femaleCount);
        femaleSlice->setColor(QColor("#e74c3c")); // Rouge
        femaleSlice->setLabelVisible(true);
    }

    // 6. Configuration des labels
    for(QPieSlice *slice : series->slices()) {
        double percentage = (slice->value() / total) * 100.0;
        slice->setLabel(QString("%1% (%L2)")
                       .arg(percentage, 0, 'f', 1)
                       .arg(slice->value()));
        slice->setLabelArmLengthFactor(0.3);
        slice->setLabelFont(QFont("Arial", 10));
    }

    // 7. Création du graphique
    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Répartition des genres");
    chart->legend()->setAlignment(Qt::AlignRight);
    chart->setAnimationOptions(QChart::AllAnimations);

    // 8. Intégration dans l'interface
    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    chartView->setMinimumSize(600, 450); // Taille augmentée

    QGraphicsScene *scene = new QGraphicsScene();
    scene->addWidget(chartView);
    ui->pie->setScene(scene);
    ui->pie->show();
}
void MainWindow::on_rechercherButton_clicked() {
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

}
void MainWindow::on_comboBox_tri_3_currentIndexChanged(int index) {
    const int DATE_COLUMN = 3; // Colonne de la date dans le QTableWidget

    Qt::SortOrder order = Qt::DescendingOrder; // Par défaut : décroissant

    if (index == 1) { // Si "Date croissante" est sélectionné
        order = Qt::AscendingOrder;
    }

    ui->tableWidget->sortItems(DATE_COLUMN, order);
}

void MainWindow::on_pdf_2_clicked()
{
    QString filePath = QFileDialog::getSaveFileName(this, "Enregistrer le PDF", "", "*.pdf");
    if (filePath.isEmpty()) return;
    if (!filePath.endsWith(".pdf")) filePath += ".pdf";

    QPdfWriter pdfWriter(filePath);
    pdfWriter.setPageSize(QPageSize(QPageSize::A4));
    pdfWriter.setResolution(300);
    pdfWriter.setPageMargins(QMargins(50, 50, 50, 50));

    QPainter painter(&pdfWriter);
    if (!painter.isActive()) {
        QMessageBox::warning(this, "Erreur", "Impossible de créer le fichier PDF.");
        return;
    }

    // Title
    QFont titleFont("Arial", 24, QFont::Bold);
    painter.setFont(titleFont);
    painter.setPen(QColor(128, 0, 128));
    painter.drawText(QRect(0, 0, pdfWriter.width(), 100), Qt::AlignCenter, "Liste des Architectes");

    // Layout settings
    QFont contentFont("Arial", 10);
    painter.setFont(contentFont);
    painter.setPen(Qt::black);

    int yOffset = 130;
    int rowHeight = 55; // slightly larger for more space

    QStringList headers = {"ID", "Nom", "Prénom", "Date", "Poste", "Email", "Salaire", "Sexe"};
    int columnCount = headers.size();

    int totalWidth = pdfWriter.width() - 100;  // Use full width of the page
    QVector<int> columnWidths = {
        static_cast<int>(totalWidth * 0.06),  // ID
        static_cast<int>(totalWidth * 0.10),  // Nom
        static_cast<int>(totalWidth * 0.10),  // Prénom
        static_cast<int>(totalWidth * 0.08),  // Date
        static_cast<int>(totalWidth * 0.14),  // Poste (wider now)
        static_cast<int>(totalWidth * 0.30),  // Email (much wider)
        static_cast<int>(totalWidth * 0.12),  // Salaire
        static_cast<int>(totalWidth * 0.10)   // Sexe
    };

    int leftMargin = 50;

    // Header row
    painter.setBrush(QColor(220, 220, 220));
    painter.drawRect(leftMargin - 5, yOffset, totalWidth + 10, rowHeight);
    painter.setBrush(Qt::NoBrush);
    painter.setPen(QColor(0, 102, 204));
    painter.setFont(QFont("Arial", 11, QFont::Bold));

    int x = leftMargin;
    for (int col = 0; col < columnCount; ++col) {
        painter.drawText(x + 2, yOffset + 2, columnWidths[col] - 4, rowHeight - 4, Qt::AlignCenter, headers[col]);
        x += columnWidths[col];
    }

    yOffset += rowHeight;
    painter.setFont(contentFont);
    painter.setPen(Qt::black);

    // Table data rows
    for (int row = 0; row < ui->tableWidget->rowCount(); ++row) {
        x = leftMargin;
        QStringList rowData;

        for (int col = 0; col < columnCount; ++col) {
            QString cellText = ui->tableWidget->item(row, col) ? ui->tableWidget->item(row, col)->text() : "";
            rowData.append(cellText);
        }

        if (row % 2 == 0) {
            painter.fillRect(QRect(leftMargin - 5, yOffset, totalWidth + 10, rowHeight), QColor(245, 245, 245));
        }

        for (int col = 0; col < columnCount; ++col) {
            painter.drawRect(x, yOffset, columnWidths[col], rowHeight);
            painter.drawText(QRect(x + 4, yOffset + 2, columnWidths[col] - 8, rowHeight - 4),
                             Qt::AlignLeft | Qt::AlignVCenter, rowData[col]);
            x += columnWidths[col];
        }

        yOffset += rowHeight;

        if (yOffset + rowHeight > pdfWriter.height() - 50) {
            pdfWriter.newPage();
            yOffset = 100;

            x = leftMargin;
            painter.setBrush(QColor(220, 220, 220));
            painter.drawRect(leftMargin - 5, yOffset, totalWidth + 10, rowHeight);
            painter.setBrush(Qt::NoBrush);
            painter.setPen(QColor(0, 102, 204));
            painter.setFont(QFont("Arial", 11, QFont::Bold));
            for (int col = 0; col < columnCount; ++col) {
                painter.drawText(x + 2, yOffset + 2, columnWidths[col] - 4, rowHeight - 4, Qt::AlignCenter, headers[col]);
                x += columnWidths[col];
            }
            yOffset += rowHeight;
            painter.setFont(contentFont);
            painter.setPen(Qt::black);
        }
    }

    painter.end();
    QMessageBox::information(this, "Succès", "Le fichier PDF a été exporté avec succès !");
}
