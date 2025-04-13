#include "dialog.h"
#include "qtimer.h"
#include "ui_dialog.h"
#include "mainwindow.h"
#include <QDebug>
#include <QSqlQuery>
#include <QMessageBox>

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    connect(ui->loginbutton, &QPushButton::clicked, this, &Dialog::on_loginButton_clicked);
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::on_loginButton_clicked()
{
    QString strId = ui->id->text().trimmed();
    QString password = ui->password->text().trimmed();

    // Validation des champs
    if(strId.isEmpty() || password.isEmpty()) {
        showError("Veuillez remplir tous les champs");
        return;
    }

    // Conversion de l'ID
    bool ok;
    int id = strId.toInt(&ok);
    if(!ok) {
        showError("L'identifiant doit être un nombre");
        return;
    }

    // Vérification des identifiants
    if(checkPassword(id, password)) {
        QString fullName = getEmployeName(id);
        showSuccess("Bienvenue " + fullName);

        MainWindow *mainWindow = new MainWindow();
        mainWindow->show();
        this->close();
    }
    else {
        showError("Identifiant ou mot de passe incorrect");
    }
}

bool Dialog::checkPassword(int id, const QString &password)
{
    QSqlQuery query;
    query.prepare("SELECT MOT_DE_PASSE FROM ARCHITECTES WHERE ID_ARCHITECTE = :id");
    query.bindValue(":id", id);

    if(query.exec() && query.next()) {
        QString dbPassword = query.value("MOT_DE_PASSE").toString();
        return (dbPassword == password);
    }
    return false;
}

QString Dialog::getEmployeName(int id)
{
    QSqlQuery query;
    query.prepare("SELECT NOM, PRENOM FROM ARCHITECTES WHERE ID_ARCHITECTE = :id");
    query.bindValue(":id", id);

    if(query.exec() && query.next()) {
        return query.value("PRENOM").toString() + " " + query.value("NOM").toString();
    }
    return "Utilisateur inconnu";
}

void Dialog::showError(const QString &message)
{
    ui->label_3->setText(message);
    ui->label_3->setStyleSheet("color: red;");
    QTimer::singleShot(3000, ui->label_3, &QLabel::clear);
}

void Dialog::showSuccess(const QString &message)
{
    ui->label_3->setText(message);
    ui->label_3->setStyleSheet("color: green;");
    QTimer::singleShot(3000, ui->label_3, &QLabel::clear);
}
