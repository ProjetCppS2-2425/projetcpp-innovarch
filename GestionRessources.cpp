#include "GestionRessources.h"
#include "IconDelegate.h"
#include "ui_GestionRessources.h"
#include <QStandardItemModel>
#include <QTableView>
#include <QFont>
#include <QtCharts/QChartView>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QBarCategoryAxis>
#include <QtCharts/QValueAxis>
#include <QSqlError>
#include <QRandomGenerator>
#include <QtCharts/QPieSeries>
#include <QtCharts/QPieSlice>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsProxyWidget>
#include <QtCharts/QLegendMarker>
GestionRessources::GestionRessources(QWidget *parent):QMainWindow(parent), ui(new Ui::GestionRessources)
{
    ui->setupUi(this);
    ui->triButton->setIcon(QIcon(":/ressources/images/ascending.png"));
    afficherRessources();
    connect(ui->ajouter, &QPushButton::clicked, this, &GestionRessources::ajouterRessource);
    connect(ui->modifier, &QPushButton::clicked, this, &GestionRessources::updateRessource);
    connect(ui->annuler, &QPushButton::clicked, this, &GestionRessources::annulerAjout);
    connect(ui->chercher, &QPushButton::clicked, this, &GestionRessources::rechercheRessource);
    connect(ui->triCb, &QComboBox::currentTextChanged, this, &GestionRessources::trierRessources);
    connect(ui->exportPdf, &QPushButton::clicked, this, &GestionRessources::exporterPDF);
    connect(ui->triButton, &QPushButton::clicked, this, &GestionRessources::trierRessources);
    //connect(ui->statpb, &QPushButton::clicked, this, &GestionRessources::stat);
    connect(ui->tableView, &QTableView::clicked, this, &GestionRessources::handleTableClick);

}

GestionRessources::~GestionRessources()
{
    delete ui;
}

void GestionRessources::ajouterRessource()
{
    if (!validateComboBoxes()||!validateTextFields()||!validateDateFields()||!validateNumFields())
    {return;}
    QSqlQuery query;
    query.prepare("INSERT INTO RESSOURCES (NOM_RESSOURCE, QUANTITE, CATEGORIE, FOURNISSEUR, DATE_ACHAT, ETAT, PRIX, DATE_DERNIER_ENTRETIEN) "
                  "VALUES (:nom, :quantite, :categorie, :fournisseur, :date_achat, :etat, :prix, :date_entretien)");
    query.bindValue(":nom", ui->nomRessource->text());
    query.bindValue(":quantite", ui->quantiteRessource->text().toInt());
    query.bindValue(":categorie", ui->categorieRessource->currentText());
    query.bindValue(":fournisseur", ui->fournisseurRessource->text().toInt());
    query.bindValue(":date_achat", ui->dateAjout->date());
    query.bindValue(":etat", ui->etatRessource->currentText());
    query.bindValue(":prix", ui->coutRessource->text().toDouble());
    query.bindValue(":date_entretien", ui->dateEntretien->date());

    if (query.exec()) {
        //QMessageBox::information(this, "Succès", "Ressource ajoutée !");
        afficherRessources();
        annulerAjout();
    } else {
        QMessageBox::critical(this, "Erreur", "Échec de l'ajout.");
    }
}
void GestionRessources::load(int id)
{
    qDebug() << "Loading resource for editing, ID:" << id;
    QSqlQuery query;
    query.prepare("SELECT * FROM RESSOURCES WHERE ID_RESSOURCE = :id");
    query.bindValue(":id", id);

    if (query.exec() && query.next()) {
        ui->nomRessource->setText(query.value("NOM_RESSOURCE").toString());
        ui->quantiteRessource->setText(query.value("QUANTITE").toString());
        ui->categorieRessource->setCurrentText(query.value("CATEGORIE").toString());
        ui->fournisseurRessource->setText(query.value("FOURNISSEUR").toString());
        ui->dateAjout->setDate(query.value("DATE_ACHAT").toDate());
        ui->coutRessource->setText(query.value("PRIX").toString());
        ui->dateEntretien->setDate(query.value("DATE_DERNIER_ENTRETIEN").toDate());
        ui->etatRessource->setCurrentText(query.value("ETAT").toString());
        m_currentResourceId = id;
    } else {
        qDebug() << "Query executed but no data found for ID:" << id;
        //QMessageBox::critical(this, "Erreur", "Impossible de charger les données de la ressource.");
    }
}
void GestionRessources::updateRessource()
{
    if (m_currentResourceId == 0) {
        QMessageBox::warning(this, "Erreur", "Aucune ressource sélectionnée.");
        return;
    }
    qDebug() << "Updating resource with ID:" << m_currentResourceId;
    QSqlQuery query;
    query.prepare("UPDATE RESSOURCES SET NOM_RESSOURCE=:nom, QUANTITE=:quantite, CATEGORIE=:categorie, "
                  "FOURNISSEUR=:fournisseur, DATE_ACHAT=:date_achat, ETAT=:etat, PRIX=:prix, DATE_DERNIER_ENTRETIEN=:date_entretien "
                  "WHERE ID_RESSOURCE=:id");

    query.bindValue(":id", m_currentResourceId);
    query.bindValue(":nom", ui->nomRessource->text());
    query.bindValue(":quantite", ui->quantiteRessource->text().toInt());
    query.bindValue(":categorie", ui->categorieRessource->currentText());
    query.bindValue(":fournisseur", ui->fournisseurRessource->text().toInt());
    query.bindValue(":date_achat", ui->dateAjout->date());
    query.bindValue(":etat", ui->etatRessource->currentText());
    query.bindValue(":prix", ui->coutRessource->text().toDouble());
    query.bindValue(":date_entretien", ui->dateEntretien->date());

    if (query.exec()) {
        QMessageBox::information(this, "Succès", "Ressource modifiée avec succès !");
        afficherRessources();  // Refresh the table or resource list
        annulerAjout();
    } else {
        qDebug() << "Error updating resource:" << query.lastError().text();
        QMessageBox::critical(this, "Erreur", "Échec de la modification !");
    }
}

void GestionRessources::annulerAjout()
{
    ui->nomRessource->clear();
    ui->quantiteRessource->clear();
    ui->categorieRessource->setCurrentIndex(0);
    ui->fournisseurRessource->clear();
    ui->dateAjout->clear();
    ui->etatRessource->setCurrentIndex(0);
    ui->coutRessource->clear();
    ui->dateEntretien->clear();
}
void GestionRessources::supprimerRessource(int id)
{
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Confirmation", "Voulez-vous supprimer cette ressource?",
                                  QMessageBox::Yes | QMessageBox::No);
    if (reply == QMessageBox::Yes) {
        QSqlQuery query;
        query.prepare("DELETE FROM RESSOURCES WHERE ID_RESSOURCE = :id");
        query.bindValue(":id", id);
        if (query.exec()) {
            QMessageBox::information(this, "Succès", "Ressource supprimée !");
            afficherRessources();
        } else {
            QMessageBox::critical(this, "Erreur", "Échec de la suppression.");
        }
    }
}
void GestionRessources::rechercheRessource()
{
    qDebug() << "Recherche function triggered!";
    if (!QSqlDatabase::database().isOpen()) {
        qDebug() << "Database is not open!";
        return;
    }

    QString searchText = ui->recherche->text().trimmed();
    QString searchCriteria = ui->rechercheCb->currentText();
    QString queryStr;
    QSqlQuery query;

    if (searchCriteria == "ID") {
        queryStr =R"(
        SELECT
        ID_RESSOURCE AS "ID",
        NOM_RESSOURCE AS "Nom",
        CATEGORIE AS "Catégorie",
        QUANTITE AS "Quantité",
        TO_CHAR(DATE_ACHAT, 'YYYY-MM-DD') AS "Date d'Achat",
        PRIX AS "Coût",
        TO_CHAR(DATE_DERNIER_ENTRETIEN, 'YYYY-MM-DD') AS "Dernier Entretien",
        ETAT AS "État",
        CAST(FOURNISSEUR AS VARCHAR(50)) AS "Fournisseur",
        ID_ARCH AS "ID Architecte",
        '' AS "Modifier",
        '' AS "Supprimer"
        FROM RESSOURCES WHERE ID_RESSOURCE = :value)";
        query.prepare(queryStr);
        query.bindValue(":value", searchText.toInt());
    }
    else if (searchCriteria == "Quantité") {
        queryStr =R"(
        SELECT
        ID_RESSOURCE AS "ID",
        NOM_RESSOURCE AS "Nom",
        CATEGORIE AS "Catégorie",
        QUANTITE AS "Quantité",
        TO_CHAR(DATE_ACHAT, 'YYYY-MM-DD') AS "Date d'Achat",
        PRIX AS "Coût",
        TO_CHAR(DATE_DERNIER_ENTRETIEN, 'YYYY-MM-DD') AS "Dernier Entretien",
        ETAT AS "État",
        CAST(FOURNISSEUR AS VARCHAR(50)) AS "Fournisseur",
        ID_ARCH AS "ID Architecte",
        '' AS "Modifier",
        '' AS "Supprimer"
        FROM RESSOURCES WHERE QUANTITE = :value)";
        query.prepare(queryStr);
        query.bindValue(":value", searchText.toInt());
    }
    else if (searchCriteria == "Date d'achat") {
        QDate dateAjout = QDate::fromString(searchText, "yyyy-MM-dd");
        if (!dateAjout.isValid()) {
            qDebug() << "Invalid date format!";
            return;
        }
        queryStr =R"(
        SELECT
        ID_RESSOURCE AS "ID",
        NOM_RESSOURCE AS "Nom",
        CATEGORIE AS "Catégorie",
        QUANTITE AS "Quantité",
        TO_CHAR(DATE_ACHAT, 'YYYY-MM-DD') AS "Date d'Achat",
        PRIX AS "Coût",
        TO_CHAR(DATE_DERNIER_ENTRETIEN, 'YYYY-MM-DD') AS "Dernier Entretien",
        ETAT AS "État",
        CAST(FOURNISSEUR AS VARCHAR(50)) AS "Fournisseur",
        ID_ARCH AS "ID Architecte",
        '' AS "Modifier",
        '' AS "Supprimer"
        FROM RESSOURCES WHERE DATE_ACHAT = :value)";
        query.prepare(queryStr);
        query.bindValue(":value", dateAjout);
    }

    // Execute the query and populate the model
    if (query.exec()) {
        QSqlQueryModel *model = new QSqlQueryModel();
        model->setQuery(std::move(query));
        ui->tableView->setModel(model);
        ui->recherche->clear();
        ui->rechercheCb->setCurrentIndex(0);
    } else {
        qDebug() << "Error executing search query:" << query.lastError().text();
    }
}
void GestionRessources::trierRessources()
{
    QString criteria = ui->triCb->currentText();
    int i = 0;
    if (criteria == "Date d'achat") {
        i = 4;
    } else if (criteria == "Quantité") {
        i = 3;
    } else if (criteria == "Coût") {
        i = 5;
    }
    Qt::SortOrder order = isAscending ? Qt::AscendingOrder : Qt::DescendingOrder;
    isAscending = !isAscending;
    proxyModel->sort(i, order);
    ui->triButton->setIcon(QIcon(isAscending ? ":/ressources/images/ascending.png" : ":/ressources/images/descending.png"));
}
void GestionRessources::exporterPDF()
{
    QString fileName = QFileDialog::getSaveFileName(this, "Enregistrer le PDF", "", "PDF Files (*.pdf)");
    if (fileName.isEmpty())
        return;

    QPdfWriter pdf(fileName);
    pdf.setPageSize(QPageSize(QPageSize::A4));
    pdf.setResolution(300);

    QPainter painter(&pdf);
    int y = 80;

    QPixmap logo(":/ressources/images/Logo.png");
    if (!logo.isNull()) {
        painter.drawPixmap(-40, -40, logo.scaledToHeight(220, Qt::SmoothTransformation));
    }

    // 🕓 Current Date (top-right)
    QFont dateFont("Helvetica", 11, QFont::Normal);
    painter.setFont(dateFont);
    QString dateStr = QDate::currentDate().toString("dd/MM/yyyy");
    painter.drawText(pdf.width() - 300, 50, "📅 " + dateStr);

    // Title
    QFont titleFont("Helvetica", 18, QFont::Bold);
    painter.setFont(titleFont);
    painter.drawText(QRect(0, y, pdf.width(), 100), Qt::AlignCenter, "Rapport des Ressources");
    y += 260;

    // Chart
    QPixmap chartPixmap = genererGraph();
    if (!chartPixmap.isNull()) {
        int chartWidth = pdf.width() - 120;
        QPixmap scaledChart = chartPixmap.scaledToWidth(chartWidth, Qt::SmoothTransformation);
        painter.drawPixmap(60, y, scaledChart);
        y += scaledChart.height() + 120;
    }

    QSqlQuery query;
    // Low Stock Section
    painter.setFont(QFont("Helvetica", 13, QFont::Bold));
    painter.setPen(QPen(Qt::darkRed));
    painter.drawText(60, y, "⚠ Ressources en faible stock (< 10)");
    y += 80;

    painter.setFont(QFont("Helvetica", 11));
    painter.setPen(Qt::black);

    if (query.exec("SELECT NOM_RESSOURCE, CATEGORIE, QUANTITE, FOURNISSEUR FROM RESSOURCES WHERE QUANTITE < 10")) {
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
    // 📊 Moyenne des quantités par catégorie
    if (query.exec("SELECT AVG(total) FROM (SELECT SUM(QUANTITE) AS total FROM RESSOURCES GROUP BY CATEGORIE)")) {
        if (query.next()) {
            double moyenne = query.value(0).toDouble();
            painter.setFont(QFont("Helvetica", 11));
            painter.setPen(Qt::darkMagenta);
            painter.drawText(60, y, QString("📊 Moyenne des quantités par catégorie : %1").arg(QString::number(moyenne, 'f', 2)));
            y += 80;
        }
    }
    // 📌 Number of suppliers
    if (query.exec("SELECT COUNT(DISTINCT FOURNISSEUR) FROM RESSOURCES")) {
        if (query.next()) {
            int fournisseurs = query.value(0).toInt();
            painter.setPen(Qt::black);
            painter.setFont(QFont("Helvetica", 11));
            painter.drawText(60, y, QString("📌 Nombre de fournisseurs enregistrés : %1").arg(fournisseurs));
            y += 80;
        }
    }

    // Total count
    y += 20;
    painter.setPen(Qt::black);
    painter.drawLine(50, y, pdf.width() - 50, y);
    y += 60;

    if (query.exec("SELECT COUNT(*) FROM RESSOURCES")) {
        if (query.next()) {
            int total = query.value(0).toInt();
            painter.drawText(60, y, QString("📦 Nombre total de ressources: %1").arg(total));
        }
    }
    y += 80;
    // 💡 Weekly Tip
    QStringList tips = {
        "💡 Conseil du jour: Rangez les ressources technologiques dans un endroit sec pour prolonger leur durée de vie.",
        "💡 Conseil du jour: Faites tourner les stocks pour utiliser d’abord les anciennes ressources.",
        "💡 Conseil du jour: Organisez les ressources par catégorie pour un accès rapide.",
        "💡 Conseil du jour: Effectuez une vérification mensuelle de l’état des ressources.",
        "💡 Conseil du jour: Conservez une trace numérique des entrées et sorties de stock."
    };
    QString tip = tips.at(QRandomGenerator::global()->bounded(tips.size()));
    painter.setFont(QFont("Helvetica", 11));
    painter.setPen(Qt::darkYellow);
    painter.drawText(60, y, tip);

    painter.end();
    QMessageBox::information(this, "PDF", "PDF généré avec succès !");
}


QPixmap GestionRessources::genererGraph()
{
    QStringList categories;
    QBarSet *set = new QBarSet("Quantité");
    QSqlQuery query("SELECT CATEGORIE, SUM(QUANTITE) FROM RESSOURCES GROUP BY CATEGORIE");

    QString topCategory;
    int maxValue = -1;

    while (query.next()) {
        QString cat = query.value(0).toString();
        int val = query.value(1).toInt();
        categories << cat;
        *set << val;

        if (val > maxValue) {
            maxValue = val;
            topCategory = cat;
        }
    }

    if (set->count() == 0) {
        QPixmap placeholder(800, 600);
        placeholder.fill(Qt::white);
        QPainter p(&placeholder);
        p.setPen(Qt::black);
        p.setFont(QFont("Arial", 16));
        p.drawText(placeholder.rect(), Qt::AlignCenter, "Aucune donnée disponible");
        return placeholder;
    }

    QBarSeries *series = new QBarSeries();
    series->append(set);
    set->setColor(QColor("#4e1764"));
    series->setBarWidth(0.3);

    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Utilisation totale par catégorie");
    chart->legend()->setVisible(true);
    chart->legend()->setAlignment(Qt::AlignBottom);
    chart->setBackgroundBrush(Qt::white);

    // Fonts and visuals
    QFont titleFont("Arial", 20, QFont::Bold);
    chart->setTitleFont(titleFont);

    QBarCategoryAxis *axisX = new QBarCategoryAxis();
    axisX->append(categories);
    QFont axisFont("Arial", 14);
    axisX->setLabelsFont(axisFont);
    chart->addAxis(axisX, Qt::AlignBottom);
    series->attachAxis(axisX);

    QValueAxis *axisY = new QValueAxis();
    axisY->setTitleText("Quantité");
    axisY->setTitleFont(axisFont);
    axisY->setLabelsFont(axisFont);
    chart->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisY);

    QChartView chartView(chart);
    chartView.setRenderHint(QPainter::Antialiasing);
    chartView.resize(1600, 1000);
    chartView.show();
    chartView.repaint();
    QApplication::processEvents();

    QPixmap pixmap(chartView.size());
    pixmap.fill(Qt::white);
    QPainter painter(&pixmap);
    chartView.render(&painter);
    painter.end();

    return pixmap;
}

/*QChartView* GestionRessources::stat()
{
    QPieSeries *series = new QPieSeries();

    QSqlQuery query("SELECT CATEGORIE, SUM(QUANTITE) FROM RESSOURCES GROUP BY CATEGORIE");
    int total = 0;
    QVector<QPair<QString, int>> data;

    while (query.next()) {
        QString categorie = query.value(0).toString();
        int quantite = query.value(1).toInt();
        if (quantite > 0) {
            total += quantite;
            data.append(qMakePair(categorie, quantite));
        }
    }

    if (data.isEmpty()) {
        return nullptr;
    }

    // 🎨 Custom colors for slices (add more if needed)
    QStringList colors = {"#4e1764", "#1b9aaa", "#e2c044", "#f18f01", "#c73e1d", "#6a0572"};
    int colorIndex = 0;

    for (const auto &pair : data) {
        qreal percent = static_cast<qreal>(pair.second) / total;
        QPieSlice *slice = series->append(pair.first, pair.second);

        // Optional: Only show % inside the chart
        slice->setLabel(QString("%1%").arg(int(percent * 100)));
        slice->setLabelVisible(true);

        // Apply pretty colors
        QColor color = QColor(colors[colorIndex % colors.size()]);
        slice->setBrush(color);
        slice->setPen(QPen(Qt::white, 2));
        colorIndex++;
    }

    series->setHoleSize(0.45); // donut size
    series->setPieSize(0.90);  // shrink overall if needed

    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Répartition des catégories de ressources 📊");
    chart->setTitleFont(QFont("Helvetica", 13, QFont::Bold));
    chart->legend()->setAlignment(Qt::AlignRight);
    chart->legend()->setFont(QFont("Helvetica", 10));
    chart->legend()->setLabelColor(Qt::black);
    chart->setAnimationOptions(QChart::SeriesAnimations);
    chart->setBackgroundBrush(QColor("#f7f7f7")); // soft background

    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    chartView->setMinimumSize(800, 500);

    return chartView;
}*/
void GestionRessources::on_statpb_clicked()
{
    QSqlQuery query;
    query.prepare("SELECT categorie,SUM (quantite) FROM RESSOURCES GROUP BY categorie");

    if (!query.exec()) {
        qDebug() << "Database query failed: " << query.lastError();
        return;
    }

    // Create a map to store the categories and their resource counts
    QMap<QString, int> categories;

    // Fetch data from the query and store it in the categories map
    while (query.next()) {
        QString category = query.value(0).toString();
        int count = query.value(1).toInt();
        categories[category] = count;
    }

    // Calculate the total number of resources (sum of counts across all categories)
    int total = 0;
    for (auto value : categories.values()) {
        total += value;
    }
    // Create the pie series (donut)
    QPieSeries *series = new QPieSeries();
    // Append each category with its total expense as value
    for (auto it = categories.begin(); it != categories.end(); ++it) {
        series->append(it.key(), it.value());
    }
    series->setHoleSize(0.4); // Set the hole size for a donut look

    // Set percentage labels on the slices (only percentages)
    for (int i = 0; i < series->count(); i++) {
        QPieSlice *slice = series->slices().at(i);
        double percentage = (slice->value() / total) * 100.0;
        // Set slice label to only show the percentage (e.g., "25.3%")
        slice->setLabel(QString("%1%").arg(QString::number(percentage, 'f', 1)));
        slice->setLabelVisible(true);
        slice->setLabelFont(QFont("Arial", 12, QFont::Bold));
        connect(slice, &QPieSlice::hovered, [slice](bool state) {
            // When hovered, explode the slice
            slice->setExploded(state);
            // Optionally adjust the explode distance (e.g., 10% of the radius)
            slice->setExplodeDistanceFactor(state ? 0.1 : 0);
        });
    }

    // Apply custom colors to the slices
    QList<QColor> colors = { QColor("#4e1764"), QColor("#a83279"), QColor("#fcb045"), QColor("#6dd5ed") };
    for (int i = 0; i < series->count(); i++) {
        QPieSlice *slice = series->slices().at(i);
        slice->setBrush(colors.at(i % colors.size()));
    }

    // Create the chart and add the series
    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Statistiques Des Catégories");
    chart->setTitleFont(QFont("Arial", 18, QFont::Bold));
    chart->setBackgroundBrush(QBrush(Qt::white));

    // Set up the legend (we want it to display only category names)
    chart->legend()->setVisible(true);
    chart->legend()->setAlignment(Qt::AlignRight);
    chart->legend()->setFont(QFont("Arial", 12));

    // Update the legend markers to display only the category names.
    QList<QLegendMarker*> legendMarkers = chart->legend()->markers(series);
    for (int i = 0; i < legendMarkers.size(); i++) {
        // Set each legend marker's label to the corresponding category name.
        // We assume that the order in categories.keys() matches the slice order.
        legendMarkers.at(i)->setLabel(categories.keys().at(i));
    }
    // Create the chart view
    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    chartView->setMinimumSize(550, 400); // Adjust to a readable size

    // Create a graphics scene and add the chart view
    QGraphicsScene *scene = new QGraphicsScene();
    scene->addWidget(chartView);

    // Set the scene for the QGraphicsView (acceuil2)
    QSizeF size = chartView->size();
    scene->setSceneRect(-22, 0, size.width() + 50, size.height());
    ui->acceuil2->setScene(scene);
}

void GestionRessources::afficherRessources()
{
    QSqlQueryModel *model = new QSqlQueryModel();
    QSqlDatabase db = QSqlDatabase::database();
    if (!db.isOpen()) {
        qDebug() << "Database is not open!";
        return;
    }
    model->setQuery(R"(
    SELECT
        ID_RESSOURCE AS "ID",
        NOM_RESSOURCE AS "Nom",
        CATEGORIE AS "Catégorie",
        QUANTITE AS "Quantité",
        TO_CHAR(DATE_ACHAT, 'YYYY-MM-DD') AS "Date d'Achat",
        PRIX AS "Coût",
        TO_CHAR(DATE_DERNIER_ENTRETIEN, 'YYYY-MM-DD') AS "Dernier Entretien",
        ETAT AS "État",
        CAST(FOURNISSEUR AS VARCHAR(50)) AS "Fournisseur",
        ID_ARCH AS "ID Architecte",
        '' AS "Modifier",
        '' AS "Supprimer"
    FROM RESSOURCES
)");
    proxyModel = new QSortFilterProxyModel(this);
    proxyModel->setSourceModel(model);
    proxyModel->setSortCaseSensitivity(Qt::CaseInsensitive);
    ui->tableView->setModel(proxyModel); //refresh
    ui->tableView->setSortingEnabled(true);
    ui->tableView->setItemDelegateForColumn(10, new IconDelegate(this));
    ui->tableView->setItemDelegateForColumn(11, new IconDelegate(this));
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableView->horizontalHeader()->setDefaultAlignment(Qt::AlignCenter);
}
void GestionRessources::handleTableClick(const QModelIndex &index)
{
    if (!index.isValid()) return;

    int id = proxyModel->data(proxyModel->index(index.row(), 0)).toInt();

    if (index.column() == 10) {
        load(id);
    }
    else if (index.column() == 11) {
        supprimerRessource(id);
    }
}
//Controle de saisie
bool GestionRessources::validateComboBoxes() {
    if (ui->categorieRessource->currentIndex() == 0) {  // No item selected
        ui->categorieRessource->setStyleSheet("QComboBox { border: 2px solid red; }");
        QMessageBox::warning(this, "Validation Error", "La catégorie doit être sélectionnée.");
        return false;
    } else {
        ui->categorieRessource->setStyleSheet("");  // Reset border
    }
    if (ui->etatRessource->currentIndex() == 0) {  // No item selected
        ui->etatRessource->setStyleSheet("QComboBox { border: 2px solid red; }");
        QMessageBox::warning(this, "Validation Error", "L'état doit être sélectionné.");
        return false;
    } else {
        ui->etatRessource->setStyleSheet("");  // Reset border
    }
    return true;
}

bool GestionRessources::validateDateFields() {
    QDate dateAchat = ui->dateAjout->date();
    if (dateAchat.isValid() && dateAchat > QDate::currentDate()) {
        QMessageBox::warning(this, "Validation Error", "La date d'achat ne peut pas être dans le futur.");
        return false;
    }

    QDate dateEntretien = ui->dateEntretien->date();
    if (dateEntretien.isValid() && dateEntretien > QDate::currentDate()) {
        QMessageBox::warning(this, "Validation Error", "La date de dernier entretien ne peut pas être dans le futur.");
        return false;
    }

    return true;
}

bool GestionRessources::validateTextFields() {
    if (ui->nomRessource->text().isEmpty()) {
        QMessageBox::warning(this, "Validation Error", "Le nom de la ressource ne peut pas être vide.");
        return false;
    }
    if (ui->categorieRessource->currentText().isEmpty()) {
        QMessageBox::warning(this, "Validation Error", "La catégorie ne peut pas être vide.");
        return false;
    }
    if (ui->etatRessource->currentText().isEmpty()) {
        QMessageBox::warning(this, "Validation Error", "L'état ne peut pas être vide.");
        return false;
    }
    return true;
}

bool GestionRessources::validateNumFields() {
    bool ok;
    int quantite = ui->quantiteRessource->text().toInt(&ok);
    if (!ok || quantite <= 0) {
        ui->quantiteRessource->setStyleSheet("QLineEdit { border: 2px solid red; }");
        QMessageBox::warning(this, "Validation Error", "La quantité doit être un nombre entier positif.");
        return false;
    } else {
        ui->quantiteRessource->setStyleSheet("");  // Reset border if valid
    }

    long fournisseur = ui->fournisseurRessource->text().toLong(&ok);
    QString fournisseurStr = ui->fournisseurRessource->text();
    if (!ok || fournisseurStr.length() != 8 || fournisseur <= 0) {  // Ensure exactly 8 digits
        ui->fournisseurRessource->setStyleSheet("QLineEdit { border: 2px solid red; }");
        QMessageBox::warning(this, "Validation Error", "Le fournisseur doit être un numéro valide de 8 chiffres.");
        return false;
    } else {
        ui->fournisseurRessource->setStyleSheet("");  // Reset border if valid
    }

    double prix = ui->coutRessource->text().toDouble(&ok);
    if (!ok || prix <= 0.0) {
        ui->coutRessource->setStyleSheet("QLineEdit { border: 2px solid red; }");
        QMessageBox::warning(this, "Validation Error", "Le prix doit être un nombre valide supérieur à zéro.");
        return false;
    } else {
        ui->coutRessource->setStyleSheet("");  // Reset border if valid
    }

    return true;
}


