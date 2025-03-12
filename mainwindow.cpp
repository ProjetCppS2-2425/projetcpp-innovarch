#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QStandardItemModel>
#include <QTableView>
#include <QFont>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Create the model
    QStandardItemModel *model = new QStandardItemModel(0, 6, this);  // 0 rows, 6 columns (including category)

    // Set headers
    model->setHeaderData(0, Qt::Horizontal, "Produit");
    model->setHeaderData(1, Qt::Horizontal, "Quantité");
    model->setHeaderData(2, Qt::Horizontal, "Prix");
    model->setHeaderData(3, Qt::Horizontal, "Catégorie");
    model->setHeaderData(4, Qt::Horizontal, "Modifier");
    model->setHeaderData(5, Qt::Horizontal, "Supprimer");

    // Set bold font for headers
    QFont boldFont;
    boldFont.setBold(true);
    for (int i = 0; i < 6; ++i) {
        model->setHeaderData(i, Qt::Horizontal, model->headerData(i, Qt::Horizontal).toString(), Qt::DisplayRole);
        model->setHeaderData(i, Qt::Horizontal, boldFont, Qt::FontRole);
    }

    // Add some example data with categories and prices in DT
    model->insertRow(0);
    model->setData(model->index(0, 0), "Chaise");
    model->setData(model->index(0, 1), 10);
    model->setData(model->index(0, 2), "150 DT");
    model->setData(model->index(0, 3), "Mobilier");
    model->setData(model->index(0, 4), "✏️");  // Modifier icon (pen)
    model->setData(model->index(0, 5), "🗑️");  // Supprimer icon (bin)

    model->insertRow(1);
    model->setData(model->index(1, 0), "Table");
    model->setData(model->index(1, 1), 5);
    model->setData(model->index(1, 2), "300 DT");
    model->setData(model->index(1, 3), "Mobilier");
    model->setData(model->index(1, 4), "✏️");
    model->setData(model->index(1, 5), "🗑️");

    model->insertRow(2);
    model->setData(model->index(2, 0), "Stylo");
    model->setData(model->index(2, 1), 100);
    model->setData(model->index(2, 2), "5 DT");
    model->setData(model->index(2, 3), "Fournitures de bureau");
    model->setData(model->index(2, 4), "✏️");
    model->setData(model->index(2, 5), "🗑️");

    model->insertRow(3);
    model->setData(model->index(3, 0), "Ordinateur portable");
    model->setData(model->index(3, 1), 20);
    model->setData(model->index(3, 2), "2000 DT");
    model->setData(model->index(3, 3), "Électronique");
    model->setData(model->index(3, 4), "✏️");
    model->setData(model->index(3, 5),"🗑️");

    model->insertRow(4);
    model->setData(model->index(4, 0), "Cahier");
    model->setData(model->index(4, 1), 50);
    model->setData(model->index(4, 2), "10 DT");
    model->setData(model->index(4, 3), "Fournitures de bureau");
    model->setData(model->index(4, 4), "✏️");
    model->setData(model->index(4, 5), "🗑️");

    // Set the model to your QTableView
    ui->tableView->setModel(model);  // Assuming tableView is your QTableView object in the UI

    // Set the size of the QTableView (621x371)
    ui->tableView->setFixedSize(621, 371);
}

MainWindow::~MainWindow()
{
    delete ui;
}
