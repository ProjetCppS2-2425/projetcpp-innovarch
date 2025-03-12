#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QRandomGenerator>
#include <QDate>
#include "architechtes.h"

Architecte::Architecte() {
    id_architecte = 0;
    nom = "";
    prenom = "";
    email = "";
    mot_de_passe = "";
    sexe = "";
    date_embauche = QDate();
    salaire = 0.0;
}

Architecte::Architecte(int id_architecte, float salaire, QString nom, QString prenom, QString email, QString mot_de_passe, QString sexe, QDate date_embauche) {
    this->id_architecte = id_architecte;
    this->salaire = salaire;
    this->nom = nom;
    this->prenom = prenom;
    this->email = email;
    this->mot_de_passe = mot_de_passe;
    this->sexe = sexe;
    this->date_embauche = date_embauche;
}

int Architecte::generateIdentifiant() {
    int identifiant = 0;
    for (int i = 0; i < 4; i++) {
        identifiant = identifiant * 10 + QRandomGenerator::global()->bounded(10);
    }
    return identifiant;
}

QString Architecte::generateNumericPassword() {
    QString password;
    for (int i = 0; i < 8; ++i) {
        password.append(QString::number(QRandomGenerator::global()->bounded(10)));
    }
    return password;
}

bool Architecte::ajouter() {
    int id_a = generateIdentifiant();
    QString generatedPassword = generateNumericPassword();

    QSqlQuery query;
    query.prepare("INSERT INTO architectes (id_architecte, nom, prenom, email, poste, mot_de_passe, sexe, date_embauche, salaire) "
                  "VALUES (:id_a, :nom, :prenom, :email, :poste, :mdp, :sexe, :date_embauche, :salaire)");

    query.bindValue(":id_a", id_a);
    query.bindValue(":nom", nom);
    query.bindValue(":prenom", prenom);
    query.bindValue(":email", email);
    query.bindValue(":poste", poste); // Column "poste" instead of "specialite"
    query.bindValue(":mdp", generatedPassword); // Column "mot_de_passe" in Oracle
    query.bindValue(":sexe", sexe);
    query.bindValue(":date_embauche", date_embauche.toString("yyyy-MM-dd"));
    query.bindValue(":salaire", salaire);

    qDebug() << "Ajout de l'architecte avec les informations suivantes:";
    qDebug() << "ID:" << id_a;
    qDebug() << "Nom:" << nom;
    qDebug() << "Prénom:" << prenom;
    qDebug() << "Email:" << email;
    qDebug() << "Poste:" << poste;
    qDebug() << "Mot de passe:" << generatedPassword;
    qDebug() << "Sexe:" << sexe;
    qDebug() << "Date d'embauche:" << date_embauche.toString("yyyy-MM-dd");
    qDebug() << "Salaire:" << salaire;

    if (!query.exec()) {
        qDebug() << "Erreur lors de l'ajout de l'architecte:" << query.lastError().text();
        return false;
    }

    return true;
}

bool Architecte::idExists(QString id) {
    bool ok;
    int idInt = id.toInt(&ok);  // Try converting to integer

    if (!ok || id.isEmpty()) {  // Ensure the ID is a valid integer and not empty
        qDebug() << "ID is not a valid integer or is empty.";
        return false;
    }

    QSqlQuery query;
    query.prepare("SELECT COUNT(*) FROM architectes WHERE id_architecte = :id");
    query.bindValue(":id", idInt);  // Bind as integer if needed

    if (query.exec() && query.next()) {
        return query.value(0).toInt() > 0;
    } else {
        qDebug() << "Erreur lors de la vérification de l'existence de l'ID:" << query.lastError().text();
    }

    return false;
}

bool Architecte::supprimer(QString id_a) {
    QSqlQuery query;
    query.prepare("DELETE FROM architectes WHERE id_architecte = :id_a");
    query.bindValue(":id_a", id_a);
    return query.exec();  // Execute the query and return the result
}

QSqlQueryModel* Architecte::afficher() {
    QSqlQueryModel* model = new QSqlQueryModel();
    model->setQuery("SELECT id_architecte, nom, prenom, email, poste, sexe, date_embauche, salaire FROM architectes"); // Exclude password for security

    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID_Architecte"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Prénom"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Email"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("Poste"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("Sexe"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("Date d'embauche"));
    model->setHeaderData(7, Qt::Horizontal, QObject::tr("Salaire"));

    return model;
}

bool Architecte::modifier(QString nom, QString prenom, QString sexe, QString email, float salaire, QString poste, QDate date_embauche, QString id) {
    QString id_input = id.trimmed();  // Trim whitespace from ID input

    bool ok;
    int id_architecte = id_input.toInt(&ok);  // Try converting to integer

    if (!ok || id_input.isEmpty()) {  // Ensure the ID is a valid integer and not empty
        qDebug() << "Échec: L'ID fourni n'est pas un entier valide ou est vide.";
        return false;
    }

    // Check if the ID exists
    if (!idExists(id_input)) {
        qDebug() << "Échec: L'ID" << id_input << "n'existe pas dans la base de données.";
        return false;
    }

    QStringList updateFields;

    if (!nom.isEmpty()) updateFields << "nom = :nom";
    if (!prenom.isEmpty()) updateFields << "prenom = :prenom";
    if (!sexe.isEmpty()) updateFields << "sexe = :sexe";
    if (!email.isEmpty()) updateFields << "email = :email";
    if (salaire > 0) updateFields << "salaire = :salaire";
    if (!poste.isEmpty()) updateFields << "poste = :poste";
    if (date_embauche.isValid()) updateFields << "date_embauche = :date_embauche";

    if (updateFields.isEmpty()) {
        qDebug() << "Aucun champ à mettre à jour.";
        return false;
    }

    // Construct the SQL query
    QString queryString = "UPDATE architectes SET " + updateFields.join(", ") + " WHERE id_architecte = :id";

    QSqlQuery query;
    query.prepare(queryString);

    // Bind values dynamically
    if (!nom.isEmpty()) query.bindValue(":nom", nom);
    if (!prenom.isEmpty()) query.bindValue(":prenom", prenom);
    if (!sexe.isEmpty()) query.bindValue(":sexe", sexe);
    if (!email.isEmpty()) query.bindValue(":email", email);
    if (salaire > 0) query.bindValue(":salaire", salaire);
    if (!poste.isEmpty()) query.bindValue(":poste", poste);
    if (date_embauche.isValid()) query.bindValue(":date_embauche", date_embauche.toString("yyyy-MM-dd"));
    query.bindValue(":id", id_architecte);

    // Debugging: Print the query
    qDebug() << "Requête SQL de modification:" << queryString;
    qDebug() << "Valeurs liées:" << "ID:" << id_architecte << " Nom:" << nom << " Prénom:" << prenom
             << " Sexe:" << sexe << " Email:" << email << " Salaire:" << salaire
             << " Poste:" << poste << " Date d'embauche:" << date_embauche.toString("yyyy-MM-dd");

    // Execute the query
    if (!query.exec()) {
        qDebug() << "Échec de la mise à jour:" << query.lastError().text();
        return false;
    }

    // Check if the update affected any row
    if (query.numRowsAffected() == 0) {
        qDebug() << "Aucune ligne n'a été mise à jour. Vérifiez l'ID.";
        return false;
    }

    return true;
}
