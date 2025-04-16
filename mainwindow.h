#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "projetcrud.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_addProjectButton_clicked();
    void on_modifyProjectButton_clicked();
    void on_deleteProjectButton_clicked();
    void on_tableView_itemClicked(const QModelIndex &index);
    void refreshTableWidget();
    void on_cancelButton_clicked();
    void on_sortButton_clicked();
    void on_searchButton_clicked();
    void on_exportPDFButton_clicked();
    void on_showStatsButton_clicked();
    void on_stat1_2_clicked();

private:
    Ui::MainWindow *ui;
    ProjetCRUD currentProject;
    void fillTableWidget();
    void on_statButton_clicked();
    void on_importPDFButton_clicked();
    void on_advancedSearchButton_clicked();
    void on_searchByCriteriaButton_clicked();
};

#endif // MAINWINDOW_H
