#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "projetcrud.h"
#include "ui_mainwindow.h"  // Include the generated UI header
#include <QNetworkAccessManager>  // For API calls
#include <QNetworkReply>          // Handle API responses
#include <QJsonDocument>          // Parse JSON from OpenAI
#include <QJsonObject>            // Construct JSON payloads

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
    void on_pushButton_ASK_clicked();
    void displayProjectStats();  // Pour afficher les statistiques
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
    void handleChatbotResponse(); // Handle API responses

private:
    Ui::MainWindow *ui;  // Pointer to access UI elements
    ProjetCRUD currentProject;
    void fillTableWidget();
    void on_statButton_clicked();
    void on_importPDFButton_clicked();
    void on_advancedSearchButton_clicked();
    void on_searchByCriteriaButton_clicked();
    QString getResponse(const QString &question); // Added missing declaration
    QNetworkAccessManager *networkManager; // For API requests
    const QString chatbotApiUrl = "https://generativelanguage.googleapis.com/v1/models/gemini-1.5-pro:generateContent";
    const QString chatbotApiKey = "AIzaSyAOoQot44v63-w_UejM2QGNQIan_Eoa6AI";
    void sendChatbotRequest(const QString &userMessage); // Send user input to API
};

#endif // MAINWINDOW_H
