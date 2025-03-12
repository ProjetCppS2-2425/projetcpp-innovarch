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

private:
    Ui::MainWindow *ui;
    ProjetCRUD currentProject;
};

#endif // MAINWINDOW_H
