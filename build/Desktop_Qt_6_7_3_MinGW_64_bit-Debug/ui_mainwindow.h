/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDateEdit>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableView>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QTabWidget *demande_conge_2;
    QWidget *tab_8;
    QWidget *tab_37;
    QWidget *widget_9;
    QPushButton *annuler_histo_2;
    QLineEdit *id_conge_2;
    QPushButton *rechercher_2;
    QTableView *historique_2;
    QLabel *label_185;
    QWidget *tab_38;
    QTableView *afficher_conge_2;
    QLabel *label_186;
    QWidget *widget_10;
    QPushButton *annule_conge_2;
    QLabel *label_10;
    QPushButton *recherche_conge_2;
    QLineEdit *id_emp_5;
    QTabWidget *aceuille_2;
    QWidget *tab_6;
    QWidget *widget_6;
    QLabel *label_146;
    QDateEdit *date_debut;
    QLineEdit *id;
    QLabel *label_155;
    QLineEdit *montant;
    QLabel *label_149;
    QLabel *label_160;
    QLabel *label_162;
    QPushButton *modifier;
    QPushButton *ajouter;
    QPushButton *annuler;
    QDateEdit *date_fin;
    QLabel *label_163;
    QLineEdit *iclient_2;
    QLineEdit *iclient;
    QLabel *label_147;
    QLabel *label_148;
    QLabel *label_157;
    QComboBox *status_2;
    QLabel *label_156;
    QWidget *widget_7;
    QLineEdit *id_rech;
    QPushButton *chercher_2;
    QPushButton *supprimer;
    QLabel *label_166;
    QComboBox *comboBox_tri_3;
    QTableWidget *tableWidget;
    QPushButton *pdf_3;
    QWidget *tab_7;
    QGraphicsView *pie_2;
    QGraphicsView *bar_2;
    QFrame *frame;
    QLabel *label;
    QWidget *layoutWidget_2;
    QVBoxLayout *verticalLayout;
    QPushButton *pushButton;
    QPushButton *pushButton_4;
    QPushButton *pushButton_3;
    QPushButton *pushButton_2;
    QPushButton *pushButton_5;
    QPushButton *pushButton_6;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(1397, 817);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        demande_conge_2 = new QTabWidget(centralwidget);
        demande_conge_2->setObjectName("demande_conge_2");
        demande_conge_2->setGeometry(QRect(430, 1050, 1451, 801));
        demande_conge_2->setStyleSheet(QString::fromUtf8("background-color:#F8EDEB;\n"
""));
        tab_8 = new QWidget();
        tab_8->setObjectName("tab_8");
        demande_conge_2->addTab(tab_8, QString());
        tab_37 = new QWidget();
        tab_37->setObjectName("tab_37");
        widget_9 = new QWidget(tab_37);
        widget_9->setObjectName("widget_9");
        widget_9->setGeometry(QRect(20, 100, 1081, 71));
        widget_9->setStyleSheet(QString::fromUtf8("/* QLineEdit styling */\n"
"QLineEdit {\n"
"    background-color: #f0f0f0;\n"
"    border: 1px solid #5c5c5c;\n"
"    border-radius: 5px;         /* Corrected property and added border-radius */\n"
"    padding: 5px;\n"
"    font-size: 14px;\n"
"    color: #333333;\n"
"}\n"
"\n"
"QLineEdit:hover {\n"
"    border: 1px solid #0078d7;\n"
"}\n"
"\n"
"QLineEdit:focus {\n"
"    border: 1px solid #3b5998;\n"
"    background-color: #ffffff;\n"
"}\n"
"\n"
"/* QDateEdit styling */\n"
"QDateEdit {\n"
"    background-color: #f0f0f0;\n"
"    border: 1px solid #5c5c5c;\n"
"    padding: 5px;\n"
"    font-size: 14px;\n"
"    color: #333333;\n"
"    border-radius: 5px;         /* Add border-radius for rounded corners */\n"
"}\n"
"\n"
"QDateEdit::drop-down {\n"
"    subcontrol-origin: padding;\n"
"    subcontrol-position: top right;\n"
"    width: 20px;\n"
"    border-left: 1px solid #5c5c5c;\n"
"}\n"
"\n"
"/* QComboBox styling */\n"
"QComboBox {\n"
"    background-color: #f0f0f0;\n"
"    border: 1px solid #5c5c5c;\n"
"    padd"
                        "ing: 5px;\n"
"    font-size: 14px;\n"
"    color: #333333;\n"
"    border-radius: 5px;         /* Add border-radius for rounded corners */\n"
"}\n"
"\n"
"QComboBox::drop-down {\n"
"    subcontrol-origin: padding;\n"
"    subcontrol-position: top right;\n"
"    width: 20px;\n"
"    border-left: 1px solid #5c5c5c;\n"
"}\n"
"\n"
"/* QPushButton styling */\n"
"QPushButton {\n"
"    color: black;\n"
"    border: 1px solid #5c5c5c;\n"
"    padding: 5px 15px;\n"
"    font-size: 14px;\n"
"    border-radius: 5px;         /* Add border-radius for rounded corners */\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"    background-color: rgb(252, 246, 243);\n"
"}\n"
"\n"
"QPushButton:pressed {\n"
"    background-color: #C0C0C0; /* Change background color when pressed */\n"
"    border: 1px solid black; /* Change border color when pressed */\n"
"}\n"
"\n"
"QPushButton:disabled {\n"
"    background-color: #C0C0C0;\n"
"    color: #a0a0a0;\n"
"    border: 1px solid #d3d3d3;\n"
"}\n"
"\n"
"/* QCheckBox styling */\n"
"QCheckBox {\n"
"    "
                        "spacing: 5px;\n"
"    font-size: 14px;\n"
"    color: #333333;\n"
"}\n"
"\n"
"QCheckBox::indicator {\n"
"    width: 16px;\n"
"    height: 16px;\n"
"}\n"
"\n"
"/* QLabel styling */\n"
"QLabel {\n"
"    font-size: 14px;\n"
"    color: #333333;\n"
"    padding: 5px;\n"
"    border: none; /* Remove border if not needed */\n"
"    border-radius: 5px;         /* Add border-radius for rounded corners */\n"
"}\n"
""));
        annuler_histo_2 = new QPushButton(widget_9);
        annuler_histo_2->setObjectName("annuler_histo_2");
        annuler_histo_2->setGeometry(QRect(350, 20, 151, 29));
        annuler_histo_2->setStyleSheet(QString::fromUtf8("QPushButton#modifier2 {\n"
"    background-color: rgb(255, 255, 255);\n"
"\n"
"	border: 2px solid #9f86c0 ;/* Default thicker border */\n"
"    border-radius: 5px;\n"
"}\n"
"\n"
"QPushButton#modifier2:hover {\n"
"    background-color: #9f86c0; \n"
"}"));
        id_conge_2 = new QLineEdit(widget_9);
        id_conge_2->setObjectName("id_conge_2");
        id_conge_2->setGeometry(QRect(10, 20, 181, 31));
        id_conge_2->setStyleSheet(QString::fromUtf8("QLineEdit {\n"
"    border: 2px solid #4e1764;  /* Default thicker border */\n"
"    border-radius: 5px;\n"
"    background-color: white;  /* Ensure background stays white */\n"
"    padding: 4px;  /* Adjust padding for better spacing */\n"
"}\n"
"\n"
"QLineEdit:focus {\n"
"    border: 3px solid #9f86c0;  /* Highlight border when focused */\n"
"    background-color: white;  /* Keep background white */\n"
"}\n"
""));
        rechercher_2 = new QPushButton(widget_9);
        rechercher_2->setObjectName("rechercher_2");
        rechercher_2->setGeometry(QRect(200, 20, 141, 29));
        rechercher_2->setStyleSheet(QString::fromUtf8("QPushButton#chercher_2 {\n"
"    background-color: rgb(255, 255, 255);\n"
"	border: 2px solid #9f86c0 ;/* Default thicker border */\n"
"    border-radius: 5px;\n"
"}"));
        historique_2 = new QTableView(tab_37);
        historique_2->setObjectName("historique_2");
        historique_2->setGeometry(QRect(15, 190, 1091, 421));
        historique_2->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        label_185 = new QLabel(tab_37);
        label_185->setObjectName("label_185");
        label_185->setGeometry(QRect(330, 10, 521, 91));
        QFont font;
        font.setBold(true);
        font.setItalic(true);
        label_185->setFont(font);
        label_185->setStyleSheet(QString::fromUtf8("/* QLabel styling */\n"
"QLabel {\n"
"    background: white;          /* Set background to white */\n"
"    color: #333333;             /* Text color */\n"
"    font-size: 25px;            /* Font size */\n"
"    padding: 5px;               /* Padding around the text */\n"
"    border: 2px solid #4e1764;  /* Optional: Add a border */\n"
"    border-radius: 14px;\n"
"}\n"
"\n"
""));
        demande_conge_2->addTab(tab_37, QString());
        tab_38 = new QWidget();
        tab_38->setObjectName("tab_38");
        afficher_conge_2 = new QTableView(tab_38);
        afficher_conge_2->setObjectName("afficher_conge_2");
        afficher_conge_2->setGeometry(QRect(10, 180, 1101, 401));
        afficher_conge_2->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        label_186 = new QLabel(tab_38);
        label_186->setObjectName("label_186");
        label_186->setGeometry(QRect(340, 10, 431, 71));
        label_186->setFont(font);
        label_186->setStyleSheet(QString::fromUtf8("/* QLabel styling */\n"
"QLabel {\n"
"    background: white;          /* Set background to white */\n"
"    color: #333333;             /* Text color */\n"
"    font-size: 25px;            /* Font size */\n"
"    padding: 5px;               /* Padding around the text */\n"
"    border: 2px solid #4e1764;  /* Optional: Add a border */\n"
"    border-radius: 14px;\n"
"}\n"
""));
        widget_10 = new QWidget(tab_38);
        widget_10->setObjectName("widget_10");
        widget_10->setGeometry(QRect(10, 100, 1101, 71));
        widget_10->setStyleSheet(QString::fromUtf8("/* QLineEdit styling */\n"
"QLineEdit {\n"
"    background-color: #f0f0f0;\n"
"    border: 1px solid #5c5c5c;\n"
"    border-radius: 5px;         /* Corrected property and added border-radius */\n"
"    padding: 5px;\n"
"    font-size: 14px;\n"
"    color: #333333;\n"
"}\n"
"\n"
"QLineEdit:hover {\n"
"    border: 1px solid #0078d7;\n"
"}\n"
"\n"
"QLineEdit:focus {\n"
"    border: 1px solid #3b5998;\n"
"    background-color: #ffffff;\n"
"}\n"
"\n"
"/* QDateEdit styling */\n"
"QDateEdit {\n"
"    background-color: #f0f0f0;\n"
"    border: 1px solid #5c5c5c;\n"
"    padding: 5px;\n"
"    font-size: 14px;\n"
"    color: #333333;\n"
"    border-radius: 5px;         /* Add border-radius for rounded corners */\n"
"}\n"
"\n"
"QDateEdit::drop-down {\n"
"    subcontrol-origin: padding;\n"
"    subcontrol-position: top right;\n"
"    width: 20px;\n"
"    border-left: 1px solid #5c5c5c;\n"
"}\n"
"\n"
"/* QComboBox styling */\n"
"QComboBox {\n"
"    background-color: #f0f0f0;\n"
"    border: 1px solid #5c5c5c;\n"
"    padd"
                        "ing: 5px;\n"
"    font-size: 14px;\n"
"    color: #333333;\n"
"    border-radius: 5px;         /* Add border-radius for rounded corners */\n"
"}\n"
"\n"
"QComboBox::drop-down {\n"
"    subcontrol-origin: padding;\n"
"    subcontrol-position: top right;\n"
"    width: 20px;\n"
"    border-left: 1px solid #5c5c5c;\n"
"}\n"
"\n"
"/* QPushButton styling */\n"
"QPushButton {\n"
"    color: black;\n"
"    border: 1px solid #5c5c5c;\n"
"    padding: 5px 15px;\n"
"    font-size: 14px;\n"
"    border-radius: 5px;         /* Add border-radius for rounded corners */\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"    background-color: rgb(252, 246, 243);\n"
"}\n"
"\n"
"QPushButton:pressed {\n"
"    background-color: #C0C0C0; /* Change background color when pressed */\n"
"    border: 1px solid black; /* Change border color when pressed */\n"
"}\n"
"\n"
"QPushButton:disabled {\n"
"    background-color: #C0C0C0;\n"
"    color: #a0a0a0;\n"
"    border: 1px solid #d3d3d3;\n"
"}\n"
"\n"
"/* QCheckBox styling */\n"
"QCheckBox {\n"
"    "
                        "spacing: 5px;\n"
"    font-size: 14px;\n"
"    color: #333333;\n"
"}\n"
"\n"
"QCheckBox::indicator {\n"
"    width: 16px;\n"
"    height: 16px;\n"
"}\n"
"\n"
"/* QLabel styling */\n"
"QLabel {\n"
"    font-size: 14px;\n"
"    color: #333333;\n"
"    padding: 5px;\n"
"    border: none; /* Remove border if not needed */\n"
"    border-radius: 5px;         /* Add border-radius for rounded corners */\n"
"}\n"
""));
        annule_conge_2 = new QPushButton(widget_10);
        annule_conge_2->setObjectName("annule_conge_2");
        annule_conge_2->setGeometry(QRect(500, 21, 151, 29));
        annule_conge_2->setStyleSheet(QString::fromUtf8("QPushButton#modifier2 {\n"
"    background-color: rgb(255, 255, 255);\n"
"\n"
"	border: 2px solid #9f86c0 ;/* Default thicker border */\n"
"    border-radius: 5px;\n"
"}\n"
"\n"
"QPushButton#modifier2:hover {\n"
"    background-color: #9f86c0; \n"
"}"));
        label_10 = new QLabel(widget_10);
        label_10->setObjectName("label_10");
        label_10->setGeometry(QRect(10, 10, 181, 51));
        recherche_conge_2 = new QPushButton(widget_10);
        recherche_conge_2->setObjectName("recherche_conge_2");
        recherche_conge_2->setGeometry(QRect(350, 21, 141, 29));
        recherche_conge_2->setStyleSheet(QString::fromUtf8("QPushButton#modifier2 {\n"
"    background-color: rgb(255, 255, 255);\n"
"\n"
"	border: 2px solid #9f86c0 ;/* Default thicker border */\n"
"    border-radius: 5px;\n"
"}\n"
"\n"
"QPushButton#modifier2:hover {\n"
"    background-color: #9f86c0; \n"
"}"));
        id_emp_5 = new QLineEdit(widget_10);
        id_emp_5->setObjectName("id_emp_5");
        id_emp_5->setGeometry(QRect(160, 21, 181, 31));
        id_emp_5->setStyleSheet(QString::fromUtf8("QLineEdit {\n"
"    border: 2px solid #4e1764;  /* Default thicker border */\n"
"    border-radius: 5px;\n"
"    background-color: white;  /* Ensure background stays white */\n"
"    padding: 4px;  /* Adjust padding for better spacing */\n"
"}\n"
"\n"
"QLineEdit:focus {\n"
"    border: 3px solid #9f86c0;  /* Highlight border when focused */\n"
"    background-color: white;  /* Keep background white */\n"
"}\n"
""));
        demande_conge_2->addTab(tab_38, QString());
        aceuille_2 = new QTabWidget(centralwidget);
        aceuille_2->setObjectName("aceuille_2");
        aceuille_2->setGeometry(QRect(200, 20, 1741, 761));
        aceuille_2->setStyleSheet(QString::fromUtf8("background-color:#F8EDEB;\n"
""));
        tab_6 = new QWidget();
        tab_6->setObjectName("tab_6");
        widget_6 = new QWidget(tab_6);
        widget_6->setObjectName("widget_6");
        widget_6->setGeometry(QRect(20, 110, 311, 471));
        widget_6->setStyleSheet(QString::fromUtf8("/* QWidget styling */\n"
"QWidget {\n"
"    border: 2px solid #4e1764;  /* Set border width and color */\n"
"    padding: 10px;              /* Set padding inside the widget */\n"
"	border-radius: 5px;\n"
"}\n"
"\n"
"/* QLineEdit styling */\n"
"QLineEdit {\n"
"    background-color: #f0f0f0;\n"
"    border: 1px solid #5c5c5c;\n"
"    border-radius: 5px;         /* Corrected property and added border-radius */\n"
"    padding: 5px;\n"
"    font-size: 14px;\n"
"    color: #333333;\n"
"}\n"
"\n"
"QLineEdit:hover {\n"
"    border: 1px solid #0078d7;\n"
"}\n"
"\n"
"QLineEdit:focus {\n"
"    border: 1px solid #3b5998;\n"
"    background-color: #ffffff;\n"
"}\n"
"\n"
"/* QDateEdit styling */\n"
"QDateEdit {\n"
"    background-color: #f0f0f0;\n"
"    border: 1px solid #5c5c5c;\n"
"    padding: 5px;\n"
"    font-size: 14px;\n"
"    color: #333333;\n"
"    border-radius: 5px;         /* Add border-radius for rounded corners */\n"
"}\n"
"\n"
"QDateEdit::drop-down {\n"
"    subcontrol-origin: padding;\n"
"    subcontrol-po"
                        "sition: top right;\n"
"    width: 20px;\n"
"    border-left: 1px solid #5c5c5c;\n"
"}\n"
"\n"
"/* QComboBox styling */\n"
"QComboBox {\n"
"    background-color: #f0f0f0;\n"
"    border: 1px solid #5c5c5c;\n"
"    padding: 5px;\n"
"    font-size: 14px;\n"
"    color: #333333;\n"
"    border-radius: 5px;         /* Add border-radius for rounded corners */\n"
"}\n"
"\n"
"QComboBox::drop-down {\n"
"    subcontrol-origin: padding;\n"
"    subcontrol-position: top right;\n"
"    width: 20px;\n"
"    border-left: 1px solid #5c5c5c;\n"
"}\n"
"\n"
"/* QPushButton styling */\n"
"QPushButton {\n"
"    color: black;\n"
"    border: 1px solid #5c5c5c;\n"
"    padding: 5px 15px;\n"
"    font-size: 14px;\n"
"    border-radius: 5px;         /* Add border-radius for rounded corners */\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"    background-color: rgb(252, 246, 243);\n"
"}\n"
"\n"
"QPushButton:pressed {\n"
"    background-color: #C0C0C0; /* Change background color when pressed */\n"
"    border: 1px solid black; /* Change border "
                        "color when pressed */\n"
"}\n"
"\n"
"QPushButton:disabled {\n"
"    background-color: #C0C0C0;\n"
"    color: #a0a0a0;\n"
"    border: 1px solid #d3d3d3;\n"
"}\n"
"\n"
"/* QCheckBox styling */\n"
"QCheckBox {\n"
"    spacing: 5px;\n"
"    font-size: 14px;\n"
"    color: #333333;\n"
"}\n"
"\n"
"QCheckBox::indicator {\n"
"    width: 16px;\n"
"    height: 16px;\n"
"}\n"
"\n"
"/* QLabel styling */\n"
"QLabel {\n"
"    font-size: 14px;\n"
"    color: #333333;\n"
"    padding: 5px;\n"
"    border: none; /* Remove border if not needed */\n"
"    border-radius: 5px;         /* Add border-radius for rounded corners */\n"
"}\n"
""));
        label_146 = new QLabel(widget_6);
        label_146->setObjectName("label_146");
        label_146->setGeometry(QRect(10, 9, 171, 41));
        label_146->setStyleSheet(QString::fromUtf8(""));
        date_debut = new QDateEdit(widget_6);
        date_debut->setObjectName("date_debut");
        date_debut->setGeometry(QRect(10, 190, 131, 31));
        date_debut->setStyleSheet(QString::fromUtf8("\n"
"    border: 2px solid #4e1764;  /* Default thicker border */\n"
"    border-radius: 5px;\n"
"    background-color: white;  /* Ensure background stays white */\n"
"\n"
"\n"
"\n"
""));
        id = new QLineEdit(widget_6);
        id->setObjectName("id");
        id->setGeometry(QRect(10, 40, 131, 31));
        id->setStyleSheet(QString::fromUtf8("QLineEdit {\n"
"    border: 2px solid #4e1764;  /* Default thicker border */\n"
"    border-radius: 5px;\n"
"    background-color: white;  /* Ensure background stays white */\n"
"    padding: 4px;  /* Adjust padding for better spacing */\n"
"}\n"
"\n"
"QLineEdit:focus {\n"
"    border: 3px solid #9f86c0;  /* Highlight border when focused */\n"
"    background-color: white;  /* Keep background white */\n"
"}\n"
""));
        label_155 = new QLabel(widget_6);
        label_155->setObjectName("label_155");
        label_155->setGeometry(QRect(10, 220, 131, 41));
        montant = new QLineEdit(widget_6);
        montant->setObjectName("montant");
        montant->setGeometry(QRect(10, 350, 141, 31));
        montant->setStyleSheet(QString::fromUtf8("QLineEdit {\n"
"    border: 2px solid #4e1764;  /* Default thicker border */\n"
"    border-radius: 5px;\n"
"    background-color: white;  /* Ensure background stays white */\n"
"    padding: 4px;  /* Adjust padding for better spacing */\n"
"}\n"
"\n"
"QLineEdit:focus {\n"
"    border: 3px solid #9f86c0;  /* Highlight border when focused */\n"
"    background-color: white;  /* Keep background white */\n"
"}\n"
""));
        label_149 = new QLabel(widget_6);
        label_149->setObjectName("label_149");
        label_149->setGeometry(QRect(10, 90, 161, 21));
        label_149->setStyleSheet(QString::fromUtf8("font: 9pt \"Segoe UI\";"));
        label_160 = new QLabel(widget_6);
        label_160->setObjectName("label_160");
        label_160->setGeometry(QRect(10, 150, 141, 35));
        label_160->setStyleSheet(QString::fromUtf8(""));
        label_162 = new QLabel(widget_6);
        label_162->setObjectName("label_162");
        label_162->setGeometry(QRect(10, 310, 101, 31));
        label_162->setStyleSheet(QString::fromUtf8(""));
        modifier = new QPushButton(widget_6);
        modifier->setObjectName("modifier");
        modifier->setGeometry(QRect(110, 420, 85, 31));
        modifier->setStyleSheet(QString::fromUtf8("QPushButton#modifier {\n"
"	border-color: rgb(78, 23, 100);\n"
"    background-color:  #4e1764;  /* Vibrant mauve */\n"
"    border: none;\n"
"    font-size: 13.1px;\n"
"    font-weight: bold;\n"
"	color: white;\n"
"}\n"
"\n"
"QPushButton#modifier:hover {\n"
"    background-color: #9f86c0;  /* Softer pinkish mauve on hover */\n"
"}\n"
"\n"
"QPushButton#modifier:pressed {\n"
"    background-color: #9f86c0;  /* Darker when clicked */\n"
"}\n"
""));
        ajouter = new QPushButton(widget_6);
        ajouter->setObjectName("ajouter");
        ajouter->setGeometry(QRect(220, 420, 78, 31));
        ajouter->setStyleSheet(QString::fromUtf8("QPushButton#ajouter {\n"
"	border-color: rgb(78, 23, 100);\n"
"    background-color:  #4e1764;  /* Vibrant mauve */\n"
"   border: none;\n"
"    font-size: 13.1px;\n"
"    font-weight: bold;\n"
"	color: white;\n"
"}\n"
"\n"
"QPushButton#ajouter:hover {\n"
"    background-color: #9f86c0;  /* Softer pinkish mauve on hover */\n"
"}\n"
"\n"
"QPushButton#ajouter:pressed {\n"
"    background-color: #9f86c0;  /* Darker when clicked */\n"
"}\n"
""));
        annuler = new QPushButton(widget_6);
        annuler->setObjectName("annuler");
        annuler->setGeometry(QRect(10, 420, 81, 31));
        annuler->setStyleSheet(QString::fromUtf8("QPushButton#annuler {\n"
"	border-color: rgb(78, 23, 100);\n"
"    background-color:  #4e1764;  /* Vibrant mauve */\n"
"    border: none;\n"
"    font-size: 13.1px;\n"
"    font-weight: bold;\n"
"	color: white;\n"
"}\n"
"\n"
"QPushButton#annuler:hover {\n"
"    background-color: #9f86c0;  /* Softer pinkish mauve on hover */\n"
"}\n"
"\n"
"QPushButton#annuler:pressed {\n"
"    background-color: #9f86c0;  /* Darker when clicked */\n"
"}\n"
""));
        date_fin = new QDateEdit(widget_6);
        date_fin->setObjectName("date_fin");
        date_fin->setGeometry(QRect(160, 190, 131, 31));
        date_fin->setStyleSheet(QString::fromUtf8("\n"
"    border: 2px solid #4e1764;  /* Default thicker border */\n"
"    border-radius: 5px;\n"
"    background-color: white;  /* Ensure background stays white */\n"
"\n"
"\n"
"\n"
""));
        label_163 = new QLabel(widget_6);
        label_163->setObjectName("label_163");
        label_163->setGeometry(QRect(160, 150, 141, 35));
        label_163->setStyleSheet(QString::fromUtf8(""));
        iclient_2 = new QLineEdit(widget_6);
        iclient_2->setObjectName("iclient_2");
        iclient_2->setGeometry(QRect(10, 120, 131, 31));
        iclient_2->setStyleSheet(QString::fromUtf8("QLineEdit {\n"
"    border: 2px solid #4e1764;  /* Default thicker border */\n"
"    border-radius: 5px;\n"
"    background-color: white;  /* Ensure background stays white */\n"
"    padding: 4px;  /* Adjust padding for better spacing */\n"
"}\n"
"\n"
"QLineEdit:focus {\n"
"    border: 3px solid #9f86c0;  /* Highlight border when focused */\n"
"    background-color: white;  /* Keep background white */\n"
"}\n"
""));
        iclient = new QLineEdit(widget_6);
        iclient->setObjectName("iclient");
        iclient->setGeometry(QRect(160, 120, 131, 31));
        iclient->setStyleSheet(QString::fromUtf8("QLineEdit {\n"
"    border: 2px solid #4e1764;  /* Default thicker border */\n"
"    border-radius: 5px;\n"
"    background-color: white;  /* Ensure background stays white */\n"
"    padding: 4px;  /* Adjust padding for better spacing */\n"
"}\n"
"\n"
"QLineEdit:focus {\n"
"    border: 3px solid #9f86c0;  /* Highlight border when focused */\n"
"    background-color: white;  /* Keep background white */\n"
"}\n"
""));
        label_147 = new QLabel(widget_6);
        label_147->setObjectName("label_147");
        label_147->setGeometry(QRect(10, 80, 141, 41));
        label_147->setStyleSheet(QString::fromUtf8(""));
        label_148 = new QLabel(widget_6);
        label_148->setObjectName("label_148");
        label_148->setGeometry(QRect(160, 80, 141, 41));
        label_148->setStyleSheet(QString::fromUtf8(""));
        label_157 = new QLabel(widget_6);
        label_157->setObjectName("label_157");
        label_157->setGeometry(QRect(10, 230, 151, 31));
        label_157->setStyleSheet(QString::fromUtf8(""));
        status_2 = new QComboBox(widget_6);
        status_2->addItem(QString());
        status_2->addItem(QString());
        status_2->addItem(QString());
        status_2->setObjectName("status_2");
        status_2->setGeometry(QRect(10, 270, 131, 31));
        status_2->setStyleSheet(QString::fromUtf8("\n"
"    border: 2px solid #4e1764;  /* Default thicker border */\n"
"    border-radius: 5px;\n"
"    background-color: white;  /* Ensure background stays white */\n"
"\n"
"\n"
"\n"
""));
        label_156 = new QLabel(tab_6);
        label_156->setObjectName("label_156");
        label_156->setGeometry(QRect(30, 70, 221, 51));
        label_156->setFont(font);
        label_156->setStyleSheet(QString::fromUtf8("/* QLabel styling */\n"
"QLabel {\n"
"    background: white;          /* Set background to white */\n"
"    color: #333333;             /* Text color */\n"
"    font-size: 25px;            /* Font size */\n"
"    padding: 5px;               /* Padding around the text */\n"
"    border: 2px solid #4e1764;  /* Optional: Add a border */\n"
"    border-radius: 14px;\n"
"}\n"
""));
        widget_7 = new QWidget(tab_6);
        widget_7->setObjectName("widget_7");
        widget_7->setGeometry(QRect(350, 110, 911, 571));
        widget_7->setStyleSheet(QString::fromUtf8("/* QLineEdit styling */\n"
"QLineEdit {\n"
"    background-color: #f0f0f0;\n"
"    border: 1px solid #5c5c5c;\n"
"    border-radius: 5px;         /* Corrected property and added border-radius */\n"
"    padding: 5px;\n"
"    font-size: 14px;\n"
"    color: #333333;\n"
"}\n"
"\n"
"QLineEdit:hover {\n"
"    border: 1px solid #0078d7;\n"
"}\n"
"\n"
"QLineEdit:focus {\n"
"    border: 1px solid #3b5998;\n"
"    background-color: #ffffff;\n"
"}\n"
"\n"
"/* QDateEdit styling */\n"
"QDateEdit {\n"
"    background-color: #f0f0f0;\n"
"    border: 1px solid #5c5c5c;\n"
"    padding: 5px;\n"
"    font-size: 14px;\n"
"    color: #333333;\n"
"    border-radius: 5px;         /* Add border-radius for rounded corners */\n"
"}\n"
"\n"
"QDateEdit::drop-down {\n"
"    subcontrol-origin: padding;\n"
"    subcontrol-position: top right;\n"
"    width: 20px;\n"
"    border-left: 1px solid #5c5c5c;\n"
"}\n"
"\n"
"/* QComboBox styling */\n"
"QComboBox {\n"
"    background-color: #f0f0f0;\n"
"    border: 1px solid #5c5c5c;\n"
"    padd"
                        "ing: 5px;\n"
"    font-size: 14px;\n"
"    color: #333333;\n"
"    border-radius: 5px;         /* Add border-radius for rounded corners */\n"
"}\n"
"\n"
"QComboBox::drop-down {\n"
"    subcontrol-origin: padding;\n"
"    subcontrol-position: top right;\n"
"    width: 20px;\n"
"    border-left: 1px solid #5c5c5c;\n"
"}\n"
"\n"
"/* QPushButton styling */\n"
"QPushButton {\n"
"    color: black;\n"
"    border: 1px solid #5c5c5c;\n"
"    padding: 5px 15px;\n"
"    font-size: 14px;\n"
"    border-radius: 5px;         /* Add border-radius for rounded corners */\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"    background-color: rgb(252, 246, 243);\n"
"}\n"
"\n"
"QPushButton:pressed {\n"
"    background-color: #C0C0C0; /* Change background color when pressed */\n"
"    border: 1px solid black; /* Change border color when pressed */\n"
"}\n"
"\n"
"QPushButton:disabled {\n"
"    background-color: #C0C0C0;\n"
"    color: #a0a0a0;\n"
"    border: 1px solid #d3d3d3;\n"
"}\n"
"\n"
"/* QCheckBox styling */\n"
"QCheckBox {\n"
"    "
                        "spacing: 5px;\n"
"    font-size: 14px;\n"
"    color: #333333;\n"
"}\n"
"\n"
"QCheckBox::indicator {\n"
"    width: 16px;\n"
"    height: 16px;\n"
"}\n"
"\n"
"/* QLabel styling */\n"
"QLabel {\n"
"    font-size: 14px;\n"
"    color: #333333;\n"
"    padding: 5px;\n"
"    border: none; /* Remove border if not needed */\n"
"    border-radius: 5px;         /* Add border-radius for rounded corners */\n"
"}\n"
""));
        id_rech = new QLineEdit(widget_7);
        id_rech->setObjectName("id_rech");
        id_rech->setGeometry(QRect(268, 19, 141, 31));
        id_rech->setStyleSheet(QString::fromUtf8("QLineEdit {\n"
"    border: 2px solid #4e1764;  /* Default thicker border */\n"
"    border-radius: 5px;\n"
"    background-color: white;  /* Ensure background stays white */\n"
"    padding: 4px;  /* Adjust padding for better spacing */\n"
"}\n"
"\n"
"QLineEdit:focus {\n"
"    border: 3px solid #9f86c0;  /* Highlight border when focused */\n"
"    background-color: white;  /* Keep background white */\n"
"}\n"
""));
        chercher_2 = new QPushButton(widget_7);
        chercher_2->setObjectName("chercher_2");
        chercher_2->setGeometry(QRect(430, 19, 91, 31));
        chercher_2->setStyleSheet(QString::fromUtf8("QPushButton#chercher_2 {\n"
"    background-color: rgb(255, 255, 255);\n"
"	border: 2px solid #9f86c0 ;/* Default thicker border */\n"
"    border-radius: 5px;\n"
"}"));
        supprimer = new QPushButton(widget_7);
        supprimer->setObjectName("supprimer");
        supprimer->setGeometry(QRect(630, 470, 161, 41));
        supprimer->setStyleSheet(QString::fromUtf8("QPushButton#pdf_2 {\n"
"    background-color: rgb(255, 255, 255);\n"
"	border: 2px solid #9f86c0 ;/* Default thicker border */\n"
"    border-radius: 5px;\n"
"}\n"
"QPushButton#pdf_2:hover {\n"
"    background-color: #9f86c0; \n"
"}"));
        label_166 = new QLabel(widget_7);
        label_166->setObjectName("label_166");
        label_166->setGeometry(QRect(20, 10, 241, 41));
        QFont font1;
        font1.setFamilies({QString::fromUtf8("Roboto")});
        label_166->setFont(font1);
        comboBox_tri_3 = new QComboBox(widget_7);
        comboBox_tri_3->addItem(QString());
        comboBox_tri_3->addItem(QString());
        comboBox_tri_3->addItem(QString());
        comboBox_tri_3->addItem(QString());
        comboBox_tri_3->addItem(QString());
        comboBox_tri_3->addItem(QString());
        comboBox_tri_3->setObjectName("comboBox_tri_3");
        comboBox_tri_3->setGeometry(QRect(600, 20, 141, 28));
        comboBox_tri_3->setAutoFillBackground(false);
        comboBox_tri_3->setStyleSheet(QString::fromUtf8("\n"
"\n"
"    border: 2px solid #9f86c0;  /* Default thicker border */\n"
"    border-radius: 5px;\n"
"    background-color: white;  /* Ensure background stays white */\n"
"\n"
"\n"
"\n"
""));
        comboBox_tri_3->setDuplicatesEnabled(false);
        comboBox_tri_3->setFrame(true);
        tableWidget = new QTableWidget(widget_7);
        tableWidget->setObjectName("tableWidget");
        tableWidget->setGeometry(QRect(30, 80, 681, 331));
        tableWidget->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);\n"
"font: 9pt \"Segoe UI\";\n"
"color: rgb(0, 0, 0);"));
        pdf_3 = new QPushButton(widget_7);
        pdf_3->setObjectName("pdf_3");
        pdf_3->setGeometry(QRect(70, 440, 161, 41));
        pdf_3->setStyleSheet(QString::fromUtf8("QPushButton#pdf_2 {\n"
"    background-color: rgb(255, 255, 255);\n"
"	border: 2px solid #9f86c0 ;/* Default thicker border */\n"
"    border-radius: 5px;\n"
"}\n"
"QPushButton#pdf_2:hover {\n"
"    background-color: #9f86c0; \n"
"}"));
        aceuille_2->addTab(tab_6, QString());
        tab_7 = new QWidget();
        tab_7->setObjectName("tab_7");
        pie_2 = new QGraphicsView(tab_7);
        pie_2->setObjectName("pie_2");
        pie_2->setGeometry(QRect(10, 10, 471, 631));
        bar_2 = new QGraphicsView(tab_7);
        bar_2->setObjectName("bar_2");
        bar_2->setGeometry(QRect(10, 10, 1161, 701));
        aceuille_2->addTab(tab_7, QString());
        frame = new QFrame(centralwidget);
        frame->setObjectName("frame");
        frame->setGeometry(QRect(0, 0, 201, 791));
        frame->setStyleSheet(QString::fromUtf8("background-color: #4E1764\n"
""));
        frame->setFrameShape(QFrame::Shape::StyledPanel);
        frame->setFrameShadow(QFrame::Shadow::Raised);
        label = new QLabel(frame);
        label->setObjectName("label");
        label->setGeometry(QRect(0, 0, 201, 191));
        label->setPixmap(QPixmap(QString::fromUtf8(":/ressources/images/logot.png")));
        label->setScaledContents(true);
        label->setWordWrap(false);
        layoutWidget_2 = new QWidget(frame);
        layoutWidget_2->setObjectName("layoutWidget_2");
        layoutWidget_2->setGeometry(QRect(0, 220, 191, 331));
        verticalLayout = new QVBoxLayout(layoutWidget_2);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        pushButton = new QPushButton(layoutWidget_2);
        pushButton->setObjectName("pushButton");
        pushButton->setMinimumSize(QSize(0, 0));
        QFont font2;
        font2.setFamilies({QString::fromUtf8("Roboto")});
        font2.setPointSize(13);
        pushButton->setFont(font2);
        pushButton->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: #4e1764;\n"
"    color: white;\n"
"    padding: 5px;\n"
"    border: none;\n"
"}\n"
"QPushButton:hover, QPushButton:pressed {\n"
"    background-color: #BE95C4; /* Couleur au survol et au clic */\n"
"}\n"
""));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/ressources/images/employes.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        icon.addFile(QString::fromUtf8(":/ressources/images/employes.png"), QSize(), QIcon::Mode::Normal, QIcon::State::On);
        pushButton->setIcon(icon);
        pushButton->setIconSize(QSize(25, 25));

        verticalLayout->addWidget(pushButton);

        pushButton_4 = new QPushButton(layoutWidget_2);
        pushButton_4->setObjectName("pushButton_4");
        pushButton_4->setMinimumSize(QSize(0, 0));
        QFont font3;
        font3.setPointSize(13);
        pushButton_4->setFont(font3);
        pushButton_4->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: #4e1764;\n"
"    color: white;\n"
"    padding: 5px;\n"
"    border: none;\n"
"}\n"
"QPushButton:hover, QPushButton:pressed {\n"
"    background-color: #BE95C4; /* Couleur au survol et au clic */\n"
"}\n"
""));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/ressources/images/clients.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        icon1.addFile(QString::fromUtf8(":/ressources/images/clients.png"), QSize(), QIcon::Mode::Normal, QIcon::State::On);
        pushButton_4->setIcon(icon1);
        pushButton_4->setIconSize(QSize(25, 25));

        verticalLayout->addWidget(pushButton_4);

        pushButton_3 = new QPushButton(layoutWidget_2);
        pushButton_3->setObjectName("pushButton_3");
        pushButton_3->setMinimumSize(QSize(0, 0));
        pushButton_3->setFont(font2);
        pushButton_3->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: #4e1764;\n"
"    color: white;\n"
"    padding: 5px;\n"
"    border: none;\n"
"}\n"
"QPushButton:hover, QPushButton:pressed {\n"
"    background-color: #BE95C4; /* Couleur au survol et au clic */\n"
"}\n"
""));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/ressources/images/project.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        icon2.addFile(QString::fromUtf8(":/ressources/images/project.png"), QSize(), QIcon::Mode::Normal, QIcon::State::On);
        pushButton_3->setIcon(icon2);
        pushButton_3->setIconSize(QSize(25, 25));

        verticalLayout->addWidget(pushButton_3);

        pushButton_2 = new QPushButton(layoutWidget_2);
        pushButton_2->setObjectName("pushButton_2");
        pushButton_2->setMinimumSize(QSize(0, 0));
        pushButton_2->setFont(font2);
        pushButton_2->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: #4e1764;\n"
"    color: white;\n"
"    padding: 5px;\n"
"    border: none;\n"
"}\n"
"QPushButton:hover, QPushButton:pressed {\n"
"    background-color: #BE95C4; /* Couleur au survol et au clic */\n"
"}\n"
""));
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/ressources/images/desk.ico"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        icon3.addFile(QString::fromUtf8(":/ressources/images/desk.ico"), QSize(), QIcon::Mode::Normal, QIcon::State::On);
        pushButton_2->setIcon(icon3);
        pushButton_2->setIconSize(QSize(25, 25));

        verticalLayout->addWidget(pushButton_2);

        pushButton_5 = new QPushButton(layoutWidget_2);
        pushButton_5->setObjectName("pushButton_5");
        pushButton_5->setMinimumSize(QSize(0, 0));
        pushButton_5->setFont(font2);
        pushButton_5->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: #4e1764;\n"
"    color: white;\n"
"    padding: 5px;\n"
"    border: none;\n"
"}\n"
"QPushButton:hover, QPushButton:pressed {\n"
"    background-color: #BE95C4; /* Couleur au survol et au clic */\n"
"}\n"
""));
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/ressources/images/contrats.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        icon4.addFile(QString::fromUtf8(":/ressources/images/contrats.png"), QSize(), QIcon::Mode::Normal, QIcon::State::On);
        pushButton_5->setIcon(icon4);
        pushButton_5->setIconSize(QSize(25, 25));

        verticalLayout->addWidget(pushButton_5);

        pushButton_6 = new QPushButton(layoutWidget_2);
        pushButton_6->setObjectName("pushButton_6");
        pushButton_6->setMinimumSize(QSize(0, 0));
        pushButton_6->setFont(font2);
        pushButton_6->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: #4e1764;\n"
"    color: white;\n"
"    padding: 5px;\n"
"    border: none;\n"
"}\n"
"QPushButton:hover, QPushButton:pressed {\n"
"    background-color: #BE95C4; /* Couleur au survol et au clic */\n"
"}\n"
""));
        QIcon icon5;
        icon5.addFile(QString::fromUtf8(":/ressources/images/architect.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        icon5.addFile(QString::fromUtf8(":/ressources/images/architect.png"), QSize(), QIcon::Mode::Normal, QIcon::State::On);
        pushButton_6->setIcon(icon5);
        pushButton_6->setIconSize(QSize(25, 25));

        verticalLayout->addWidget(pushButton_6);

        layoutWidget_2->raise();
        label->raise();
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 1397, 25));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        demande_conge_2->setCurrentIndex(0);
        aceuille_2->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        demande_conge_2->setTabText(demande_conge_2->indexOf(tab_8), QCoreApplication::translate("MainWindow", "demande_conge", nullptr));
        annuler_histo_2->setText(QCoreApplication::translate("MainWindow", "Annuler", nullptr));
        id_conge_2->setPlaceholderText(QCoreApplication::translate("MainWindow", "id_cong\303\251", nullptr));
        rechercher_2->setText(QCoreApplication::translate("MainWindow", "rechercher", nullptr));
        label_185->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p align=\"center\"><span style=\" font-size:20pt;\">Historique Cong\303\251s</span></p></body></html>", nullptr));
        demande_conge_2->setTabText(demande_conge_2->indexOf(tab_37), QCoreApplication::translate("MainWindow", "Historique conge", nullptr));
        label_186->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p align=\"center\"><span style=\" font-size:20pt;\">Accepter/Refuser</span></p></body></html>", nullptr));
        annule_conge_2->setText(QCoreApplication::translate("MainWindow", "Annuler", nullptr));
        label_10->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-size:14pt; font-weight:700;\">Rechercher :</span></p></body></html>", nullptr));
        recherche_conge_2->setText(QCoreApplication::translate("MainWindow", "Recherche", nullptr));
        demande_conge_2->setTabText(demande_conge_2->indexOf(tab_38), QCoreApplication::translate("MainWindow", "accepter/refuser", nullptr));
#if QT_CONFIG(whatsthis)
        aceuille_2->setWhatsThis(QCoreApplication::translate("MainWindow", "<html><head/><body><p><br/></p></body></html>", nullptr));
#endif // QT_CONFIG(whatsthis)
        label_146->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-size:9pt; font-weight:700;\">Id contrat :</span></p></body></html>", nullptr));
        id->setText(QString());
        id->setPlaceholderText(QCoreApplication::translate("MainWindow", "Id contrat", nullptr));
        label_155->setText(QString());
        montant->setPlaceholderText(QCoreApplication::translate("MainWindow", "montant", nullptr));
        label_149->setText(QString());
        label_160->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-weight:700;\">Date de debut :</span></p><p><br/></p></body></html>", nullptr));
        label_162->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-weight:700;\">Montant :</span></p></body></html>", nullptr));
        modifier->setText(QCoreApplication::translate("MainWindow", "Modifier", nullptr));
        ajouter->setText(QCoreApplication::translate("MainWindow", "Ajouter", nullptr));
        annuler->setText(QCoreApplication::translate("MainWindow", "Annuler", nullptr));
        label_163->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-weight:700;\">Date de fin :</span></p></body></html>", nullptr));
        iclient_2->setText(QString());
        iclient_2->setPlaceholderText(QCoreApplication::translate("MainWindow", "id client", nullptr));
        iclient->setText(QString());
        iclient->setPlaceholderText(QCoreApplication::translate("MainWindow", "Nom", nullptr));
        label_147->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-size:9pt; font-weight:700;\">Id client :</span></p></body></html>", nullptr));
        label_148->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-size:9pt; font-weight:700;\">Nom client :</span></p></body></html>", nullptr));
        label_157->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-weight:700;\">Statut de paiement :</span></p></body></html>", nullptr));
        status_2->setItemText(0, QCoreApplication::translate("MainWindow", "pay\303\251", nullptr));
        status_2->setItemText(1, QCoreApplication::translate("MainWindow", "en attente", nullptr));
        status_2->setItemText(2, QCoreApplication::translate("MainWindow", "retard", nullptr));

        label_156->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p align=\"center\">Ajout &amp; Modifier</p><p align=\"center\"><br/></p></body></html>", nullptr));
        id_rech->setPlaceholderText(QCoreApplication::translate("MainWindow", "identifiant", nullptr));
        chercher_2->setText(QCoreApplication::translate("MainWindow", "chercher", nullptr));
        supprimer->setText(QCoreApplication::translate("MainWindow", "Exportation pdf", nullptr));
        label_166->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-size:12pt; font-weight:700;\">Recherche contract :</span></p></body></html>", nullptr));
        comboBox_tri_3->setItemText(0, QCoreApplication::translate("MainWindow", "Trier selon ", nullptr));
        comboBox_tri_3->setItemText(1, QString());
        comboBox_tri_3->setItemText(2, QCoreApplication::translate("MainWindow", "Salaire d\303\251croissant", nullptr));
        comboBox_tri_3->setItemText(3, QCoreApplication::translate("MainWindow", "salaire croissant", nullptr));
        comboBox_tri_3->setItemText(4, QCoreApplication::translate("MainWindow", "date d'emboche d\303\251c", nullptr));
        comboBox_tri_3->setItemText(5, QCoreApplication::translate("MainWindow", "date d'emboche croi", nullptr));

        pdf_3->setText(QCoreApplication::translate("MainWindow", "Supprimer", nullptr));
        aceuille_2->setTabText(aceuille_2->indexOf(tab_6), QCoreApplication::translate("MainWindow", "Consulter", nullptr));
        aceuille_2->setTabText(aceuille_2->indexOf(tab_7), QCoreApplication::translate("MainWindow", "Statistique", nullptr));
        label->setText(QString());
        pushButton->setText(QCoreApplication::translate("MainWindow", " Employ\303\251s", nullptr));
        pushButton_4->setText(QCoreApplication::translate("MainWindow", " Clients", nullptr));
        pushButton_3->setText(QCoreApplication::translate("MainWindow", " Projets", nullptr));
        pushButton_2->setText(QCoreApplication::translate("MainWindow", " Ressources", nullptr));
        pushButton_5->setText(QCoreApplication::translate("MainWindow", " Contrats", nullptr));
        pushButton_6->setText(QCoreApplication::translate("MainWindow", " Contracteurs", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
