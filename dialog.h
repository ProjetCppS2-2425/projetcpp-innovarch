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

private slots:
    void on_loginButton_clicked();

private:
    Ui::Dialog *ui;

    // Méthodes
    bool checkPassword(int id, const QString &password);
    QString getEmployeName(int id);
    QString getUserPosition(int id);
    void showError(const QString &message);
    void showSuccess(const QString &message);
};

#endif // DIALOG_H
