#include "gestionressources.h"
#include "IconDelegate.h"
#include <QStandardItemModel>
#include <QTableView>
#include <QHeaderView>
#include <QFont>
#include <QFile>
#include <QSqlQuery>
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
#include <QPdfWriter>
#include <QApplication>
#include <QObject>
#include <QMessageBox>
GestionRessources::GestionRessources()
    : id_ressource(0), quantite(0), fournisseur(0), prix(0.0), nom(""), categorie(""), etat(""), date_achat(QDate()), date_entretien(QDate())
{
}
GestionRessources::GestionRessources(int id, int quantite, int fournisseur, double prix, QString nom, QString categorie, QString etat, QDate date_achat, QDate date_entretien)
    : id_ressource(id), quantite(quantite), fournisseur(fournisseur), prix(prix), nom(nom), categorie(categorie), etat(etat), date_achat(date_achat), date_entretien(date_entretien)
{
}
QSqlQueryModel* GestionRessources::afficher()
{
    QSqlQueryModel* model = new QSqlQueryModel();
    model->setQuery(R"(
        SELECT
            ID_RESSOURCE AS "ID",
            NOM_RESSOURCE AS "Nom",
            CATEGORIE AS "Catégorie",
            QUANTITE AS "Quantité",
            TO_CHAR(DATE_ACHAT, 'YYYY-MM-DD') AS "Date d'Achat", -- Format the date
            PRIX AS "Coût",
            TO_CHAR(DATE_DERNIER_ENTRETIEN, 'YYYY-MM-DD') AS "Dernier Entretien",
            ETAT AS "État",
            CAST(FOURNISSEUR AS VARCHAR(50)) AS "Fournisseur", ID_ARCH as "ID Arch",
            '' AS "Modifier",
            '' AS "Supprimer"
        FROM RESSOURCES
    )");
    if (model->lastError().isValid()) {
        qDebug() << "Query error in afficher:" << model->lastError().text();
    }
    return model;
}

bool GestionRessources::ajouterRessource(QString nom, int quantite, QString categorie, int fournisseur, QDate date_achat, QString etat, double prix, QDate date_entretien)
{
    QSqlQuery query;
    query.prepare("INSERT INTO RESSOURCES (NOM_RESSOURCE, QUANTITE, CATEGORIE, FOURNISSEUR, DATE_ACHAT, ETAT, PRIX, DATE_DERNIER_ENTRETIEN) "
                  "VALUES (:nom, :quantite, :categorie, :fournisseur, :date_achat, :etat, :prix, :date_entretien)");
    query.bindValue(":nom", nom);
    query.bindValue(":quantite", quantite);
    query.bindValue(":categorie", categorie);
    query.bindValue(":fournisseur", fournisseur);
    query.bindValue(":date_achat", date_achat);
    query.bindValue(":etat", etat);
    query.bindValue(":prix", prix);
    query.bindValue(":date_entretien", date_entretien);
    if (!query.exec()) {
        qDebug() << "Erreur lors de l'ajout de la ressource:" << query.lastError().text();
        return false;
    }
    return true;
}

void GestionRessources::supprimerRessource(int id)
{
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(nullptr, "Confirmation", "Voulez-vous supprimer cette ressource?",
                                  QMessageBox::Yes | QMessageBox::No);
    if (reply == QMessageBox::Yes) {
        QSqlQuery query;
        query.prepare("DELETE FROM RESSOURCES WHERE ID_RESSOURCE = :id");
        query.bindValue(":id", id);
        afficher();
        if (query.exec()) {
            QMessageBox::information(nullptr, "Succès", "Ressource supprimée !");
        } else {
            QMessageBox::critical(nullptr, "Erreur", "Échec de la suppression.");
        }
    }
}
void GestionRessources::rechercheRessource(const QString& searchText, const QString& searchCriteria, QSqlQueryModel* model)
{
    if (!QSqlDatabase::database().isOpen()) {
        return;
    }
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
        ID_ARCH AS "ID Architecte"
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
        ID_ARCH AS "ID Architecte"
        FROM RESSOURCES WHERE QUANTITE = :value)";
        query.prepare(queryStr);
        query.bindValue(":value", searchText.toInt());
    }
    else if (searchCriteria == "Date d'achat") {
        QDate dateAjout = QDate::fromString(searchText, "yyyy-MM-dd");
        if (!dateAjout.isValid()) {
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
        ID_ARCH AS "ID Architecte"
        FROM RESSOURCES WHERE DATE_ACHAT = :value)";
        query.prepare(queryStr);
        query.bindValue(":value", dateAjout);
    }
    if (query.exec()) {
        model->setQuery(std::move(query));
    }
}
QPixmap GestionRessources::genererGraph()
{
    QStringList categories;
    QBarSet *set = new QBarSet("Quantité");
    QSqlQuery query("SELECT CATEGORIE, SUM(QUANTITE) FROM RESSOURCES GROUP BY CATEGORIE");
    QString topCategory;
    int maxValue = -1;

    // Fetch data from the database
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
    // Handle the case where there is no data
    if (set->count() == 0) {
        QPixmap placeholder(800, 600);
        placeholder.fill(Qt::white);
        QPainter p(&placeholder);
        p.setPen(Qt::black);
        p.setFont(QFont("Arial", 16));
        p.drawText(placeholder.rect(), Qt::AlignCenter, "Aucune donnée disponible");
        return placeholder;
    }
    set->setColor(QColor(78, 23, 100));
    // Create the bar series and chart
    QBarSeries *series = new QBarSeries();
    series->append(set);
    series->setBarWidth(0.4);

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
bool GestionRessources::updateRessource(int id, const QString &nom, int quantite, const QString &categorie,
                                        int fournisseur, const QDate &dateAchat, const QString &etat,
                                        double prix, const QDate &dateEntretien)
{
    QSqlQuery query;
    query.prepare("UPDATE RESSOURCES SET "
                  "NOM_RESSOURCE = :nom, QUANTITE = :quantite, CATEGORIE = :categorie, "
                  "FOURNISSEUR = :fournisseur, DATE_ACHAT = :dateAchat, ETAT = :etat, "
                  "PRIX = :prix, DATE_DERNIER_ENTRETIEN = :dateEntretien "
                  "WHERE ID_RESSOURCE = :id");

    query.bindValue(":nom", nom);
    query.bindValue(":quantite", quantite);
    query.bindValue(":categorie", categorie);
    query.bindValue(":fournisseur", fournisseur);
    query.bindValue(":dateAchat", dateAchat);
    query.bindValue(":etat", etat);
    query.bindValue(":prix", prix);
    query.bindValue(":dateEntretien", dateEntretien);
    query.bindValue(":id", id);

    if (query.exec()) {
        QMessageBox::information(nullptr, "Succès", "Ressource modifiée !");
        return true;
    } else {
        QMessageBox::critical(nullptr, "Erreur", "Échec de la modification !");
        return false;
    }
}

void GestionRessources::load(int id, QString& nom, int& quantite, QString& categorie, int& fournisseur, QDate& dateAchat, QString& etat, double& prix, QDate& dateEntretien)
{
    QSqlQuery query;
    query.prepare("SELECT NOM_RESSOURCE, QUANTITE, CATEGORIE, FOURNISSEUR, DATE_ACHAT, ETAT, PRIX, DATE_DERNIER_ENTRETIEN "
                  "FROM RESSOURCES WHERE ID_RESSOURCE = :id");
    query.bindValue(":id", id);

    if (query.exec() && query.next()) {
        nom = query.value(0).toString();
        quantite = query.value(1).toInt();
        categorie = query.value(2).toString();
        fournisseur = query.value(3).toInt();
        dateAchat = query.value(4).toDate();
        etat = query.value(5).toString();
        prix = query.value(6).toDouble();
        dateEntretien = query.value(7).toDate();
    } else {
        qDebug() << "Failed to load resource with ID:" << id << query.lastError().text();
    }
}

QPieSeries* GestionRessources::stat()
{
    QSqlQuery query;
    query.prepare("SELECT categorie, SUM(quantite) FROM RESSOURCES GROUP BY categorie");

    if (!query.exec()) {
        qDebug() << "Database query failed: " << query.lastError();
        return nullptr;
    }
    QPieSeries* series = new QPieSeries();
    while (query.next()) {
        QString category = query.value(0).toString();
        int count = query.value(1).toInt();
        series->append(category, count);
    }
    series->setHoleSize(0.4); // Set the hole size for a donut look
    return series;
}
QList<QPair<QString, QString>> GestionRessources::checkAlerts()
{
    QList<QPair<QString, QString>> alerts;

    QSqlQuery query;
    query.prepare("SELECT NOM_RESSOURCE, QUANTITE, DATE_DERNIER_ENTRETIEN FROM RESSOURCES"); // Adjust to your table name

    if (query.exec()) {
        QDate today = QDate::currentDate();

        while (query.next()) {
            QString nom = query.value(0).toString();
            int quantite = query.value(1).toInt();
            QDate date_entretien = query.value(2).toDate();

            if (quantite < 5) {
                alerts.append(qMakePair(QString("⚠️ Stock bas pour la ressource '%1'").arg(nom), "low_stock"));
            }

            if (date_entretien.isValid() && date_entretien <= today.addDays(3)) {
                alerts.append(qMakePair(QString("🔧 Entretien bientôt dû pour '%1'").arg(nom), "maintenance_due"));
            }
        }
    } else {
        qDebug() << "Erreur lors de l'exécution de la requête de vérification des alertes:" << query.lastError();
    }

    return alerts;
}



