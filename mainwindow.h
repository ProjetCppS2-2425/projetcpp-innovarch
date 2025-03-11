#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "contracteur.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_ajouter_clicked();
    void on_modifier_clicked();
    void on_supprimer_clicked();
    void on_refreshButton_clicked();
    void on_tableView_tri_2_currentIndexChanged(int index); // Add this line

private:
    Ui::MainWindow *ui;
    Contracteur currentContracteur;
};

#endif // MAINWINDOW_H