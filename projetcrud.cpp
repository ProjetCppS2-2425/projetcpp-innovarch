#include "projetcrud.h"
#include <QDebug>
#include <QSqlError>
#include <QFile>
#include <QIODevice>
#include <QTextStream>
#include <QPdfWriter>
#include <QPainter>
#include <QPageSize>

// Constructeurs
ProjetCRUD::ProjetCRUD() {}

ProjetCRUD::ProjetCRUD(int id, QString nom, QString type, double budget, QString echeance, QString statut, int id_architecte, int id_contracteur) {
    this->id_projet = id;
    this->nom = nom;
    this->type = type;
    this->budget = budget;
    this->echeance = echeance;
    this->statut = statut;
    this->id_architecte = id_architecte;
    this->id_contracteur = id_contracteur;
}

// Ajouter un projet
bool ProjetCRUD::ajouter() {
    QSqlQuery query;
    query.exec("SELECT MAX(ID_PROJET) FROM projets");
    int new_id = 1;
    if (query.next()) {
        new_id = query.value(0).toInt() + 1;
    }

    query.prepare("INSERT INTO projets (ID_PROJET, NOM_PROJET, TYPE_PROJET, BUDGET, ECHEANCE, STATUT) "
                  "VALUES (:id, :nom, :type, :budget, TO_DATE(:echeance, 'YYYY-MM-DD'), :statut)");
    query.bindValue(":id", new_id);
    query.bindValue(":nom", nom);
    query.bindValue(":type", type);
    query.bindValue(":budget", budget);
    query.bindValue(":echeance", echeance);
    query.bindValue(":statut", statut);

    if (!query.exec()) {
        qDebug() << "Error adding project:" << query.lastError().text();
        return false;
    }
    return true;
}

// Afficher les projets
QSqlQueryModel * ProjetCRUD::afficher() {
    QSqlQueryModel * model = new QSqlQueryModel();
    model->setQuery("SELECT ID_PROJET, NOM_PROJET, TYPE_PROJET, BUDGET, ECHEANCE, "
                    "CASE "
                    "WHEN STATUT = '0' THEN 'En cours' "
                    "WHEN STATUT = '1' THEN 'Terminé' "
                    "ELSE 'Autre' "  // Default to 'Autre' if the value is unexpected
                    "END AS STATUT "
                    "FROM projets");

    // Set column headers for better readability
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Type"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Budget"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("Échéance"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("Statut"));

    if (model->lastError().isValid()) {
        qDebug() << "Error in afficher(): " << model->lastError().text();
    } else {
        qDebug() << "afficher() query executed successfully.";
        qDebug() << "Number of rows fetched: " << model->rowCount();
    }

    return model;
}

// Modifier un projet
bool ProjetCRUD::modifier(int id) {
    QSqlQuery query;
    query.prepare("UPDATE projets SET NOM_PROJET = :nom, TYPE_PROJET = :type, BUDGET = :budget, "
                  "ECHEANCE = TO_DATE(:echeance, 'YYYY-MM-DD'), STATUT = :statut WHERE ID_PROJET = :id");
    query.bindValue(":id", id);
    query.bindValue(":nom", nom);
    query.bindValue(":type", type);
    query.bindValue(":budget", budget);
    query.bindValue(":echeance", echeance);
    query.bindValue(":statut", statut);

    return query.exec();
}

// Supprimer un projet
bool ProjetCRUD::supprimer(int id) {
    QSqlQuery query;
    query.prepare("DELETE FROM projets WHERE ID_PROJET = :id");
    query.bindValue(":id", id);

    return query.exec();
}

// Trier les projets
QSqlQueryModel *ProjetCRUD::trier(const QString &critere, const QString &ordre) {
    QSqlQueryModel *model = new QSqlQueryModel();
    QString query = QString("SELECT ID_PROJET, NOM_PROJET, TYPE_PROJET, BUDGET, ECHEANCE, STATUT FROM projets ORDER BY %1 %2")
                        .arg(critere, ordre);
    model->setQuery(query);

    if (model->lastError().isValid()) {
        qDebug() << "Error in trier(): " << model->lastError().text();
    } else {
        qDebug() << "Tri effectué avec succès. Nombre de lignes : " << model->rowCount();
    }
    return model;
}

// Rechercher un projet par ID
QSqlQueryModel *ProjetCRUD::rechercher(const QString &keyword) {
    QSqlQueryModel *model = new QSqlQueryModel();
    QString query = QString("SELECT ID_PROJET, NOM_PROJET, TYPE_PROJET, BUDGET, ECHEANCE, STATUT FROM projets WHERE ID_PROJET LIKE '%%1%'").arg(keyword);
    model->setQuery(query);

    if (model->lastError().isValid()) {
        qDebug() << "Error in rechercher(): " << model->lastError().text();
    } else {
        qDebug() << "Recherche effectuée avec succès. Nombre de lignes : " << model->rowCount();
    }

    return model;
}

QSqlQueryModel *ProjetCRUD::rechercherAvance(const QString &colonne, const QString &valeur) {
    QSqlQueryModel *model = new QSqlQueryModel();
    QString query = QString("SELECT ID_PROJET, NOM_PROJET, TYPE_PROJET, BUDGET, ECHEANCE, STATUT "
                            "FROM projets WHERE %1 LIKE '%%2%'").arg(colonne, valeur);
    model->setQuery(query);

    if (model->lastError().isValid()) {
        qDebug() << "Error in rechercherAvance(): " << model->lastError().text();
    } else {
        qDebug() << "Advanced search executed successfully. Rows fetched: " << model->rowCount();
    }

    return model;
}

QSqlQueryModel *ProjetCRUD::rechercherParCritere(const QString &colonne, const QString &valeur) {
    QSqlQueryModel *model = new QSqlQueryModel();
    QString query = QString("SELECT ID_PROJET, NOM_PROJET, TYPE_PROJET, BUDGET, ECHEANCE, STATUT "
                            "FROM projets WHERE %1 LIKE '%%2%'").arg(colonne, valeur);
    model->setQuery(query);

    if (model->lastError().isValid()) {
        qDebug() << "Error in rechercherParCritere(): " << model->lastError().text();
    } else {
        qDebug() << "Search by criteria executed successfully. Rows fetched: " << model->rowCount();
    }

    return model;
}

// Importer les projets depuis un fichier PDF
bool ProjetCRUD::importerPDF(const QString &filePath) {
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly)) {
        qDebug() << "Failed to open file for reading:" << filePath;
        return false;
    }

    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine();
        // Logique pour traiter chaque ligne du fichier PDF
        qDebug() << "Read line:" << line;
    }
    file.close();
    return true;
}

// Exporter les projets en PDF
bool ProjetCRUD::exporterPDF(const QString &filePath) {
    QPdfWriter writer(filePath);
    writer.setPageSize(QPageSize(QPageSize::A4));
    writer.setTitle("Liste des Projets");
    writer.setCreator("Application ProjetCRUD");

    QPainter painter(&writer);
    if (!painter.isActive()) {
        qDebug() << "Failed to open PDF writer.";
        return false;
    }

    // Set up fonts and margins
    QFont titleFont("Arial", 16, QFont::Bold);
    QFont contentFont("Arial", 10);
    int margin = 50;
    int y = margin;

    // Draw the title
    painter.setFont(titleFont);
    painter.drawText(margin, y, "Liste des Projets");
    y += 40;

    // Draw table headers
    painter.setFont(contentFont);
    painter.drawText(margin, y, "ID");
    painter.drawText(margin + 100, y, "Nom");
    painter.drawText(margin + 250, y, "Type");
    painter.drawText(margin + 400, y, "Budget");
    painter.drawText(margin + 500, y, "Echeance");
    painter.drawText(margin + 650, y, "Statut");
    y += 20;

    // Draw a line under the headers
    painter.drawLine(margin, y, writer.width() - margin, y);
    y += 20;

    // Fetch data from the database
    QSqlQuery query("SELECT ID_PROJET, NOM_PROJET, TYPE_PROJET, BUDGET, ECHEANCE, STATUT FROM projets");
    while (query.next()) {
        if (y > writer.height() - margin) {
            writer.newPage();
            y = margin;
        }

        QString id = query.value(0).toString();
        QString nom = query.value(1).toString();
        QString type = query.value(2).toString();
        QString budget = query.value(3).toString();
        QString echeance = query.value(4).toString();
        QString statut = query.value(5).toString();

        // Draw each row of data
        painter.drawText(margin, y, id);
        painter.drawText(margin + 100, y, nom);
        painter.drawText(margin + 250, y, type);
        painter.drawText(margin + 400, y, budget);
        painter.drawText(margin + 500, y, echeance);
        painter.drawText(margin + 650, y, statut);
        y += 20;
    }

    painter.end();
    qDebug() << "PDF exporté avec succès.";
    return true;
}

QMap<QString, int> ProjetCRUD::getStatutStatistics()
{
    QMap<QString, int> stats;
    QSqlQuery query("SELECT STATUT, COUNT(*) FROM projets GROUP BY STATUT");

    while (query.next()) {
        QString statut = query.value(0).toString();
        int count = query.value(1).toInt();
        stats[statut] = count;
    }

    return stats;
}

// Getters et Setters
int ProjetCRUD::getId() const { return id_projet; }
void ProjetCRUD::setId(int id) { this->id_projet = id; }

QString ProjetCRUD::getNom() const { return nom; }
void ProjetCRUD::setNom(const QString &nom) { this->nom = nom; }

QString ProjetCRUD::getType() const { return type; }
void ProjetCRUD::setType(const QString &type) { this->type = type; }

double ProjetCRUD::getBudget() const { return budget; }
void ProjetCRUD::setBudget(double budget) { this->budget = budget; }

QString ProjetCRUD::getEcheance() const { return echeance; }
void ProjetCRUD::setEcheance(const QString &date) { this->echeance = date; }

QString ProjetCRUD::getStatut() const { return statut; }
void ProjetCRUD::setStatut(const QString &statut) { this->statut = statut; }

int ProjetCRUD::getIdArchitecte() const { return id_architecte; }
void ProjetCRUD::setIdArchitecte(int id) { this->id_architecte = id; }

int ProjetCRUD::getIdContracteur() const { return id_contracteur; }
void ProjetCRUD::setIdContracteur(int id) { this->id_contracteur = id; }
