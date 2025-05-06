#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QSqlQuery>

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = nullptr);
    ~Dialog();

    // Ajout d'un signal pour transmettre les infos utilisateur
signals:
    void userAuthenticated(int userId, const QString& userRole);  // Nouveau signal

private slots:
    void on_loginButton_clicked();

private:
    Ui::Dialog *ui;

    // Méthodes
    bool checkPassword(int id, const QString &password);
    QString getEmployeName(int id);
    QString getEmployePoste(int id);  // Supposons que c'est cette méthode qui retourne le rôle
    void showError(const QString &message);
    void showSuccess(const QString &message);

    // Ajout pour stocker temporairement l'ID utilisateur
    int m_currentUserId;  // Nouveau membre
};

#endif // DIALOG_H
