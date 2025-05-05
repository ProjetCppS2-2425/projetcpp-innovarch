#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSqlQueryModel>
#include "contrats.h"
#include "arduino.h"
#include <QTimer>

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
    void afficherContrats();
    void on_modifier_clicked();
    void on_supprimer_clicked();
    void on_tributton_clicked();
    void on_chercher_clicked();
    void on_stats_clicked();
    void on_pushButton_email_clicked();
    void on_exporter_clicked();
    void handleKeypadInput();

    void on_tableWidget_cellClicked(int row, int column);




private:
    Ui::MainWindow *ui;
    contrats currentContrat;
    Arduino A;
    QTimer *timer;
      // Timer pour lecture série
    QString buffer;
};

#endif // MAINWINDOW_H
