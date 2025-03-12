#include "GestionRessources.h"
#include "IconDelegate.h"
#include "ui_GestionRessources.h"
#include <QStandardItemModel>
#include <QTableView>
#include <QFont>
#include <QSqlError>
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
    //connect(ui->exportPdf, &QPushButton::clicked, this, &GestionRessources::exporterPDF);
    connect(ui->triButton, &QPushButton::clicked, this, &GestionRessources::trierRessources);
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

/*void GestionRessources::exporterPDF()
{

}*/
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
    ui->tableView->setModel(proxyModel);
    ui->tableView->setSortingEnabled(true);
    ui->tableView->setItemDelegateForColumn(10, new IconDelegate(this));
    ui->tableView->setItemDelegateForColumn(11, new IconDelegate(this));
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableView->horizontalHeader()->setDefaultAlignment(Qt::AlignCenter);
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


