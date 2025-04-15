#ifndef ARCHITECTE_H
#define ARCHITECTE_H

#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QDate>

class Architecte
{
private:
    int id_architecte;
    float salaire;
    QString nom;
    QString prenom, email, poste, mot_de_passe, sexe; // Renamed "mdp" -> "mot_de_passe"


public:
    Architecte();
    Architecte(int, float, QString, QString, QString, QString, QString, QDate);
    QDate date_embauche;
    int generateIdentifiant();
    QString generateNumericPassword();
    bool idExists(QString id);
    bool supprimer(QString id_a);
    QMap<QString, int> getCongeStats() const;
    bool fetchById(int id);
     QSqlQueryModel *afficherconge();
     bool updateCongeStatus(const QString& id_conge, const QString& new_status);

    // Getters
    int getIdArchitecte() { return id_architecte; }
    float getSalaire() { return salaire; }
    QString getNom() { return nom; }
    QString getPrenom() { return prenom; }
    QString getEmail() { return email; }
    QString getPoste() { return poste; }
    QString getMotDePasse() { return mot_de_passe; }
    QString getSexe() { return sexe; }
    QDate getDateEmbauche() const { return date_embauche; }

    // Setters
    void setIdArchitecte(int id) { id_architecte = id; }
    void setSalaire(float sal) { salaire = sal; }
    void setNom(QString n) { nom = n; }
    void setPrenom(QString pre) { prenom = pre; }
    void setEmail(QString mail) { email = mail; }
    void setPoste(QString post) { poste = post; }
    void setSexe(QString sex) { sexe = sex; }
    void setMotDePasse(QString pass) { mot_de_passe = pass; }
    void setDateEmbauche(QDate date) { date_embauche = date; }

    // Méthodes
    bool ajouter();
    QSqlQueryModel *afficher();
    QString generateLeaveDecision();
    bool ajouterconge(const QString &id_emp,
                      const QString &nom,
                      const QString &prenom,
                      const QString &email,
                      const QString &raison,
                      const QString &poste,
                      const QDate &date_dep,
                      const QDate &date_fin);

    bool modifier(QString nom, QString prenom, QString sexe, QString email, float salaire, QString poste, QDate date_embauche, QString id);


};

#endif // ARCHITECTE_H
