#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QRandomGenerator>
#include <QDate>
#include "architechtes.h"
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

QMap<QString, int> Architecte::getCongeStats() const {
    QMap<QString, int> stats;
    QSqlQuery query;

    // Requête sur les états de congés
    query.prepare("SELECT LOWER(etat), COUNT(*) FROM CONGE GROUP BY LOWER(etat)");

    if (!query.exec()) {
        qCritical() << "Erreur SQL :" << query.lastError().text()
                    << "\nRequête :" << query.lastQuery();
        return stats;
    }

    // Initialiser les compteurs
    stats["accepté"] = 0;
    stats["refusé"] = 0;

    // Lecture des résultats
    while (query.next()) {
        QString etat = query.value(0).toString().trimmed().toLower();
        int count = query.value(1).toInt();

        if (etat.contains("accept")) {
            stats["accepté"] += count;
        } else if (etat.contains("refus")) {
            stats["refusé"] += count;
        } else {
            qDebug() << "État de congé non reconnu:" << query.value(0).toString();
        }
    }


    qDebug() << "[DEBUG] Congés acceptés:" << stats["ACCEPTÉ"]
             << " - Congés refusés:" << stats["REFUSÉ"];

    return stats;
}

bool Architecte::fetchById(int id) {
    QSqlQuery query;
    query.prepare("SELECT nom, prenom, email, sexe, date_embauche, salaire, poste "
                  "FROM architectes WHERE id_architecte = :id");
    query.bindValue(":id", id);

    if (!query.exec()) {
        qDebug() << "Erreur de recherche :" << query.lastError().text();
        return false;
    }

    if (query.next()) {
        nom = query.value(0).toString();
        prenom = query.value(1).toString();
        email = query.value(2).toString();
        sexe = query.value(3).toString();
        date_embauche = query.value(4).toDate();
        salaire = query.value(5).toFloat();
        poste = query.value(6).toString();
        return true;
    }

    return false;
}
QString Architecte::generateLeaveDecision() {
    // Variables pour stocker le nombre d'architectes totaux et d'architectes non en congé
    int totalArchitectes = 0;
    int architectesNotOnLeave = 0;

    // Requête pour obtenir le nombre total d'architectes
    QSqlQuery query;

    // Compter le nombre total d'architectes dans ARCHITECTES
    query.prepare("SELECT COUNT(*) FROM ARCHITECTES");
    if (query.exec() && query.next()) {
        totalArchitectes = query.value(0).toInt();
    } else {
        qDebug() << "Erreur lors de la récupération du nombre d'architectes:" << query.lastError().text();
        return "Erreur de calcul des architectes.";
    }
    qDebug() << "total architectes:" << totalArchitectes;

    // Compter les architectes qui ne sont pas en congé dans CONGE
    // Supposons que `ETAT` est le champ dans la table `CONGE` qui indique l'état du congé (ex. 'Non' pour non en congé)
    query.prepare("SELECT COUNT(*) FROM CONGE WHERE ETAT != 'En congé' AND ID_EMP IN (SELECT ID_EMP FROM ARCHITECTES)");
    if (query.exec() && query.next()) {
        architectesNotOnLeave = query.value(0).toInt();
    } else {
        qDebug() << "Erreur lors de la récupération des architectes non en congé:" << query.lastError().text();
        return "Erreur de calcul des architectes non en congé.";
    }
    qDebug() << "architectes on leave:" << architectesNotOnLeave;

    // Calcul du pourcentage d'architectes non en congé
    if (totalArchitectes == 0) {
        return "Aucun architecte disponible pour calculer.";
    }

    float percentageNotOnLeave = (float)architectesNotOnLeave / totalArchitectes * 100;
    float percentageWork = 100 - percentageNotOnLeave;
    qDebug() << "percentage:" << percentageNotOnLeave;
    qDebug() << "percentage work:" << percentageWork;

    // Décision selon le seuil de 70%
    if (percentageWork >= 70) {
        return "Tu peux accepter le congé.";
    } else {
        return "N'accepte pas le congé.";
    }
}

bool Architecte::ajouterconge(const QString &id_emp,
                              const QString &nom,
                              const QString &prenom,
                              const QString &email,
                              const QString &raison,
                              const QString &poste,
                              const QDate &date_dep,
                              const QDate &date_fin)
{
    int id_conge = generateIdentifiant(); // Utilise ta fonction dans Architecte pour générer un ID
    QString conseilMessage = generateLeaveDecision(); // Générer une consigne (conseil)

    QSqlQuery query;
    query.prepare("INSERT INTO conge (ID_CONGE, ID_EMP, NOM, PRENOM, EMAIL, RAISON, POSTE, DATE_D, DATE_F, CONSEIG, TYPE_CONGE, ETAT) "
                  "VALUES (:id_conge, :id_emp, :nom, :prenom, :email, :raison, :poste, :date_d, :date_f, :conseig, :type_conge, :etat)");

    // Liaison des valeurs
    query.bindValue(":id_conge", id_conge);
    query.bindValue(":id_emp", id_emp);
    query.bindValue(":nom", nom);
    query.bindValue(":prenom", prenom);
    query.bindValue(":email", email);
    query.bindValue(":raison", raison);
    query.bindValue(":poste", poste);
    query.bindValue(":date_d", date_dep);
    query.bindValue(":date_f", date_fin);
    query.bindValue(":conseig", conseilMessage);
    query.bindValue(":type_conge", "Congé annuel");
    query.bindValue(":etat", "En attente");

    if (!query.exec()) {
        qDebug() << "Erreur lors de l'ajout du congé :" << query.lastError().text();
        return false;
    }

    return true;
}
bool Architecte::updateCongeStatus(const QString& id_conge, const QString& new_status)
{
    QSqlQuery query;
    query.prepare("UPDATE conge SET \"ETAT\" = :etat WHERE \"ID_CONGE\" = :id");
    query.bindValue(":etat", new_status.toUpper());
    query.bindValue(":id", id_conge);

    if(!query.exec()) {
        qCritical() << "Échec de la requête UPDATE :" << query.lastError().text();
        qCritical() << "Requête :" << query.lastQuery();
        qCritical() << "Valeurs :" << id_conge << "/" << new_status;
        return false;
    }

    // Vérifier qu'une ligne a bien été modifiée
    return query.numRowsAffected() == 1;
}


