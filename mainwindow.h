#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSqlQueryModel>
#include "contrats.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void populateTableWidget(QSqlQueryModel* model);

private slots:
    void on_ajouter_clicked();
    void on_modifier_clicked();
    void on_supprimer_clicked();
    void on_rechercher_clicked();
    void on_trier_clicked();
    void on_exporter_pdf_clicked();
    void on_statistiques_clicked();

private:
    Ui::MainWindow *ui;
    contrats currentContrat;
};

#endif // MAINWINDOW_H
