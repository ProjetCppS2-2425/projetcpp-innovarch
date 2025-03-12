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
#include <QtWidgets/QCalendarWidget>
#include <QtWidgets/QCheckBox>
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
#include <QtWidgets/QRadioButton>
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
    QDateEdit *date_emboche;
    QLineEdit *email;
    QLineEdit *nom;
    QLabel *label_155;
    QLineEdit *salaire;
    QLineEdit *prenom;
    QLabel *label_149;
    QRadioButton *homme;
    QRadioButton *femme_2;
    QLabel *label_154;
    QLabel *label_160;
    QLabel *label_161;
    QLabel *label_162;
    QComboBox *poste;
    QLabel *label_165;
    QPushButton *modifier;
    QPushButton *ajouter;
    QPushButton *annuler;
    QLabel *label_156;
    QWidget *widget_7;
    QLineEdit *id_rech;
    QPushButton *chercher_2;
    QPushButton *pdf_2;
    QLabel *label_166;
    QComboBox *comboBox_tri_3;
    QTableWidget *tableWidget;
    QWidget *tab_7;
    QGraphicsView *pie_2;
    QGraphicsView *bar_2;
    QLabel *label_184;
    QWidget *widget_8;
    QLineEdit *prenom_conge_2;
    QLineEdit *nom_conge_2;
    QCalendarWidget *calendarWidget_5;
    QDateEdit *date_debut_2;
    QCheckBox *confiramtion_conge_2;
    QPushButton *soumettre_2;
    QDateEdit *date_fin_2;
    QLabel *label_168;
    QLabel *label_169;
    QLabel *label_174;
    QLabel *label_175;
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout_3;
    QVBoxLayout *verticalLayout_2;
    QLabel *label_167;
    QLineEdit *id_emp_4;
    QLabel *label_170;
    QLineEdit *email_conge_2;
    QLabel *label_171;
    QComboBox *departement_conge_3;
    QLabel *label_172;
    QComboBox *poste_conge_2;
    QLabel *label_173;
    QComboBox *raison_conge_2;
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
        MainWindow->resize(1741, 983);
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
        date_emboche = new QDateEdit(widget_6);
        date_emboche->setObjectName("date_emboche");
        date_emboche->setGeometry(QRect(10, 120, 131, 31));
        date_emboche->setStyleSheet(QString::fromUtf8("\n"
"    border: 2px solid #4e1764;  /* Default thicker border */\n"
"    border-radius: 5px;\n"
"    background-color: white;  /* Ensure background stays white */\n"
"\n"
"\n"
"\n"
""));
        email = new QLineEdit(widget_6);
        email->setObjectName("email");
        email->setGeometry(QRect(10, 280, 141, 31));
        email->setStyleSheet(QString::fromUtf8("QLineEdit {\n"
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
        nom = new QLineEdit(widget_6);
        nom->setObjectName("nom");
        nom->setGeometry(QRect(10, 40, 131, 31));
        nom->setStyleSheet(QString::fromUtf8("QLineEdit {\n"
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
        salaire = new QLineEdit(widget_6);
        salaire->setObjectName("salaire");
        salaire->setGeometry(QRect(160, 280, 141, 31));
        salaire->setStyleSheet(QString::fromUtf8("QLineEdit {\n"
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
        prenom = new QLineEdit(widget_6);
        prenom->setObjectName("prenom");
        prenom->setGeometry(QRect(160, 40, 141, 31));
        prenom->setStyleSheet(QString::fromUtf8("QLineEdit {\n"
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
        homme = new QRadioButton(widget_6);
        homme->setObjectName("homme");
        homme->setGeometry(QRect(10, 360, 121, 41));
        homme->setStyleSheet(QString::fromUtf8("border : transparent;\n"
"color: rgb(0, 0, 0);"));
        femme_2 = new QRadioButton(widget_6);
        femme_2->setObjectName("femme_2");
        femme_2->setGeometry(QRect(160, 360, 141, 41));
        femme_2->setStyleSheet(QString::fromUtf8("border : transparent;\n"
"color: rgb(0, 0, 0);"));
        label_154 = new QLabel(widget_6);
        label_154->setObjectName("label_154");
        label_154->setGeometry(QRect(10, 160, 101, 31));
        label_154->setStyleSheet(QString::fromUtf8(""));
        label_160 = new QLabel(widget_6);
        label_160->setObjectName("label_160");
        label_160->setGeometry(QRect(10, 80, 141, 35));
        label_160->setStyleSheet(QString::fromUtf8(""));
        label_161 = new QLabel(widget_6);
        label_161->setObjectName("label_161");
        label_161->setGeometry(QRect(10, 240, 101, 31));
        label_161->setStyleSheet(QString::fromUtf8(""));
        label_162 = new QLabel(widget_6);
        label_162->setObjectName("label_162");
        label_162->setGeometry(QRect(160, 240, 101, 31));
        label_162->setStyleSheet(QString::fromUtf8(""));
        poste = new QComboBox(widget_6);
        poste->addItem(QString());
        poste->addItem(QString());
        poste->addItem(QString());
        poste->addItem(QString());
        poste->addItem(QString());
        poste->addItem(QString());
        poste->addItem(QString());
        poste->setObjectName("poste");
        poste->setGeometry(QRect(10, 200, 131, 31));
        poste->setStyleSheet(QString::fromUtf8("\n"
"    border: 2px solid #4e1764;  /* Default thicker border */\n"
"    border-radius: 5px;\n"
"    background-color: white;  /* Ensure background stays white */\n"
"\n"
"\n"
"\n"
""));
        label_165 = new QLabel(widget_6);
        label_165->setObjectName("label_165");
        label_165->setGeometry(QRect(10, 330, 101, 31));
        label_165->setStyleSheet(QString::fromUtf8(""));
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
        widget_7->setGeometry(QRect(350, 110, 1171, 591));
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
        pdf_2 = new QPushButton(widget_7);
        pdf_2->setObjectName("pdf_2");
        pdf_2->setGeometry(QRect(780, 490, 161, 41));
        pdf_2->setStyleSheet(QString::fromUtf8("QPushButton#pdf_2 {\n"
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
        if (tableWidget->columnCount() < 8)
            tableWidget->setColumnCount(8);
        QFont font2;
        font2.setPointSize(14);
        font2.setBold(true);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        __qtablewidgetitem->setFont(font2);
        tableWidget->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        __qtablewidgetitem1->setFont(font2);
        tableWidget->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        __qtablewidgetitem2->setFont(font2);
        tableWidget->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        __qtablewidgetitem3->setFont(font2);
        tableWidget->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        __qtablewidgetitem4->setFont(font2);
        tableWidget->setHorizontalHeaderItem(4, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        __qtablewidgetitem5->setFont(font2);
        tableWidget->setHorizontalHeaderItem(5, __qtablewidgetitem5);
        QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
        __qtablewidgetitem6->setFont(font2);
        tableWidget->setHorizontalHeaderItem(6, __qtablewidgetitem6);
        QTableWidgetItem *__qtablewidgetitem7 = new QTableWidgetItem();
        __qtablewidgetitem7->setFont(font2);
        tableWidget->setHorizontalHeaderItem(7, __qtablewidgetitem7);
        tableWidget->setObjectName("tableWidget");
        tableWidget->setGeometry(QRect(30, 80, 1001, 391));
        tableWidget->setStyleSheet(QString::fromUtf8("ui->tableWidget->setStyleSheet(\n"
"    \"QTableWidget {\"\n"
"    \"    background-color: black;\"  // Set the background color of the table to white\n"
"    \"    color: black;\"  // Set the text color to black\n"
"    \"    border: 1px solid #dcdcdc;\"  // Add a light border around the table\n"
"    \"    font-size: 14px;\"  // Set font size for readability\n"
"    \"}\"\n"
"    \"QTableWidget::item {\"\n"
"    \"    color: black;\"  // Set item text color to black\n"
"    \"}\"\n"
"    \"QHeaderView::section {\"\n"
"    \"    background-color: purple;\"  // Set header background color to purple\n"
"    \"    color: white;\"  // Set text color in the headers to white\n"
"    \"    font-weight: bold;\"  // Make header text bold\n"
"    \"    padding: 8px;\"  // Add some padding around the header text\n"
"    \"    text-align: center;\"  // Center align the header text\n"
"    \"} \"\n"
"    \"QHeaderView::section:pressed {\"\n"
"    \"    background-color: darkpurple;\"  // Darken header color when pressed\n"
""
                        "    \"}\"\n"
");\n"
""));
        aceuille_2->addTab(tab_6, QString());
        tab_7 = new QWidget();
        tab_7->setObjectName("tab_7");
        pie_2 = new QGraphicsView(tab_7);
        pie_2->setObjectName("pie_2");
        pie_2->setGeometry(QRect(10, 10, 471, 631));
        bar_2 = new QGraphicsView(tab_7);
        bar_2->setObjectName("bar_2");
        bar_2->setGeometry(QRect(10, 10, 471, 701));
        label_184 = new QLabel(tab_7);
        label_184->setObjectName("label_184");
        label_184->setGeometry(QRect(860, 20, 431, 81));
        label_184->setFont(font);
        label_184->setStyleSheet(QString::fromUtf8("/* QLabel styling */\n"
"QLabel {\n"
"    background: white;          /* Set background to white */\n"
"    color: #333333;             /* Text color */\n"
"    font-size: 25px;            /* Font size */\n"
"    padding: 5px;               /* Padding around the text */\n"
"    border: 2px solid #4e1764;  /* Optional: Add a border */\n"
"    border-radius: 14px;\n"
"}\n"
""));
        widget_8 = new QWidget(tab_7);
        widget_8->setObjectName("widget_8");
        widget_8->setGeometry(QRect(520, 130, 1211, 561));
        widget_8->setStyleSheet(QString::fromUtf8("/* QLineEdit styling */\n"
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
        prenom_conge_2 = new QLineEdit(widget_8);
        prenom_conge_2->setObjectName("prenom_conge_2");
        prenom_conge_2->setGeometry(QRect(270, 37, 151, 31));
        prenom_conge_2->setStyleSheet(QString::fromUtf8("QLineEdit {\n"
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
        nom_conge_2 = new QLineEdit(widget_8);
        nom_conge_2->setObjectName("nom_conge_2");
        nom_conge_2->setGeometry(QRect(430, 37, 171, 31));
        nom_conge_2->setStyleSheet(QString::fromUtf8("QLineEdit {\n"
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
        calendarWidget_5 = new QCalendarWidget(widget_8);
        calendarWidget_5->setObjectName("calendarWidget_5");
        calendarWidget_5->setGeometry(QRect(740, 110, 451, 271));
        calendarWidget_5->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 0);"));
        date_debut_2 = new QDateEdit(widget_8);
        date_debut_2->setObjectName("date_debut_2");
        date_debut_2->setGeometry(QRect(6, 450, 171, 41));
        date_debut_2->setStyleSheet(QString::fromUtf8("\n"
"    border: 2px solid #4e1764;  /* Default thicker border */\n"
"    border-radius: 5px;\n"
"    background-color: white;  /* Ensure background stays white */\n"
"\n"
"\n"
"\n"
""));
        confiramtion_conge_2 = new QCheckBox(widget_8);
        confiramtion_conge_2->setObjectName("confiramtion_conge_2");
        confiramtion_conge_2->setGeometry(QRect(0, 510, 631, 41));
        soumettre_2 = new QPushButton(widget_8);
        soumettre_2->setObjectName("soumettre_2");
        soumettre_2->setGeometry(QRect(980, 460, 221, 51));
        soumettre_2->setStyleSheet(QString::fromUtf8("QPushButton#modifier2 {\n"
"    background-color: rgb(255, 255, 255);\n"
"\n"
"	border: 2px solid #9f86c0 ;/* Default thicker border */\n"
"    border-radius: 5px;\n"
"}\n"
"\n"
"QPushButton#modifier2:hover {\n"
"    background-color: #9f86c0; \n"
"}"));
        date_fin_2 = new QDateEdit(widget_8);
        date_fin_2->setObjectName("date_fin_2");
        date_fin_2->setGeometry(QRect(200, 450, 171, 41));
        date_fin_2->setStyleSheet(QString::fromUtf8("\n"
"    border: 2px solid #4e1764;  /* Default thicker border */\n"
"    border-radius: 5px;\n"
"    background-color: white;  /* Ensure background stays white */\n"
"\n"
"\n"
"\n"
""));
        label_168 = new QLabel(widget_8);
        label_168->setObjectName("label_168");
        label_168->setGeometry(QRect(430, 0, 101, 31));
        label_168->setStyleSheet(QString::fromUtf8(""));
        label_169 = new QLabel(widget_8);
        label_169->setObjectName("label_169");
        label_169->setGeometry(QRect(270, 0, 101, 31));
        label_169->setStyleSheet(QString::fromUtf8(""));
        label_174 = new QLabel(widget_8);
        label_174->setObjectName("label_174");
        label_174->setGeometry(QRect(-5, 410, 181, 29));
        label_174->setStyleSheet(QString::fromUtf8(""));
        label_175 = new QLabel(widget_8);
        label_175->setObjectName("label_175");
        label_175->setGeometry(QRect(200, 410, 254, 29));
        label_175->setStyleSheet(QString::fromUtf8(""));
        layoutWidget = new QWidget(widget_8);
        layoutWidget->setObjectName("layoutWidget");
        layoutWidget->setGeometry(QRect(0, 0, 256, 383));
        verticalLayout_3 = new QVBoxLayout(layoutWidget);
        verticalLayout_3->setObjectName("verticalLayout_3");
        verticalLayout_3->setContentsMargins(0, 0, 0, 0);
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName("verticalLayout_2");
        label_167 = new QLabel(layoutWidget);
        label_167->setObjectName("label_167");
        label_167->setStyleSheet(QString::fromUtf8(""));

        verticalLayout_2->addWidget(label_167);

        id_emp_4 = new QLineEdit(layoutWidget);
        id_emp_4->setObjectName("id_emp_4");
        id_emp_4->setStyleSheet(QString::fromUtf8("QLineEdit {\n"
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

        verticalLayout_2->addWidget(id_emp_4);

        label_170 = new QLabel(layoutWidget);
        label_170->setObjectName("label_170");
        label_170->setStyleSheet(QString::fromUtf8(""));

        verticalLayout_2->addWidget(label_170);

        email_conge_2 = new QLineEdit(layoutWidget);
        email_conge_2->setObjectName("email_conge_2");
        email_conge_2->setStyleSheet(QString::fromUtf8("QLineEdit {\n"
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

        verticalLayout_2->addWidget(email_conge_2);

        label_171 = new QLabel(layoutWidget);
        label_171->setObjectName("label_171");
        label_171->setStyleSheet(QString::fromUtf8(""));

        verticalLayout_2->addWidget(label_171);

        departement_conge_3 = new QComboBox(layoutWidget);
        departement_conge_3->setObjectName("departement_conge_3");
        departement_conge_3->setStyleSheet(QString::fromUtf8("\n"
"    border: 2px solid #4e1764;  /* Default thicker border */\n"
"    border-radius: 5px;\n"
"    background-color: white;  /* Ensure background stays white */\n"
"\n"
"\n"
"\n"
""));

        verticalLayout_2->addWidget(departement_conge_3);

        label_172 = new QLabel(layoutWidget);
        label_172->setObjectName("label_172");
        label_172->setStyleSheet(QString::fromUtf8(""));

        verticalLayout_2->addWidget(label_172);

        poste_conge_2 = new QComboBox(layoutWidget);
        poste_conge_2->setObjectName("poste_conge_2");
        poste_conge_2->setStyleSheet(QString::fromUtf8("\n"
"    border: 2px solid #4e1764;  /* Default thicker border */\n"
"    border-radius: 5px;\n"
"    background-color: white;  /* Ensure background stays white */\n"
"\n"
"\n"
"\n"
""));

        verticalLayout_2->addWidget(poste_conge_2);


        verticalLayout_3->addLayout(verticalLayout_2);

        label_173 = new QLabel(layoutWidget);
        label_173->setObjectName("label_173");
        label_173->setStyleSheet(QString::fromUtf8(""));

        verticalLayout_3->addWidget(label_173);

        raison_conge_2 = new QComboBox(layoutWidget);
        raison_conge_2->addItem(QString());
        raison_conge_2->addItem(QString());
        raison_conge_2->addItem(QString());
        raison_conge_2->addItem(QString());
        raison_conge_2->addItem(QString());
        raison_conge_2->addItem(QString());
        raison_conge_2->setObjectName("raison_conge_2");
        raison_conge_2->setStyleSheet(QString::fromUtf8("\n"
"    border: 2px solid #4e1764;  /* Default thicker border */\n"
"    border-radius: 5px;\n"
"    background-color: white;  /* Ensure background stays white */\n"
"\n"
"\n"
"\n"
""));

        verticalLayout_3->addWidget(raison_conge_2);

        layoutWidget->raise();
        prenom_conge_2->raise();
        nom_conge_2->raise();
        calendarWidget_5->raise();
        date_debut_2->raise();
        confiramtion_conge_2->raise();
        date_fin_2->raise();
        soumettre_2->raise();
        label_168->raise();
        label_169->raise();
        label_174->raise();
        label_175->raise();
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
        QFont font3;
        font3.setFamilies({QString::fromUtf8("Roboto")});
        font3.setPointSize(13);
        pushButton->setFont(font3);
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
        QFont font4;
        font4.setPointSize(13);
        pushButton_4->setFont(font4);
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
        pushButton_3->setFont(font3);
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
        pushButton_2->setFont(font3);
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
        pushButton_5->setFont(font3);
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
        pushButton_6->setFont(font3);
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
        menubar->setGeometry(QRect(0, 0, 1741, 25));
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
        label_146->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-size:9pt; font-weight:700;\">nom &amp; prenom :</span></p></body></html>", nullptr));
        email->setText(QString());
        email->setPlaceholderText(QCoreApplication::translate("MainWindow", "email", nullptr));
        nom->setText(QString());
        nom->setPlaceholderText(QCoreApplication::translate("MainWindow", "Nom", nullptr));
        label_155->setText(QString());
        salaire->setPlaceholderText(QCoreApplication::translate("MainWindow", "salaire", nullptr));
        prenom->setText(QString());
        prenom->setPlaceholderText(QCoreApplication::translate("MainWindow", "prenom", nullptr));
        label_149->setText(QString());
        homme->setText(QCoreApplication::translate("MainWindow", "homme", nullptr));
        femme_2->setText(QCoreApplication::translate("MainWindow", "femme", nullptr));
        label_154->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-weight:700;\">Poste :</span></p></body></html>", nullptr));
        label_160->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-weight:700;\">Date D'embauche :</span></p></body></html>", nullptr));
        label_161->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-weight:700;\">Email :</span></p></body></html>", nullptr));
        label_162->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-weight:700;\">Salaire :</span></p></body></html>", nullptr));
        poste->setItemText(0, QCoreApplication::translate("MainWindow", "choisir poste", nullptr));
        poste->setItemText(1, QCoreApplication::translate("MainWindow", "RH ", nullptr));
        poste->setItemText(2, QCoreApplication::translate("MainWindow", "Directeur", nullptr));
        poste->setItemText(3, QCoreApplication::translate("MainWindow", "Architechte", nullptr));
        poste->setItemText(4, QCoreApplication::translate("MainWindow", "Secretaire", nullptr));
        poste->setItemText(5, QString());
        poste->setItemText(6, QString());

        label_165->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-weight:700;\">Sexe :</span></p></body></html>", nullptr));
        modifier->setText(QCoreApplication::translate("MainWindow", "Modifier", nullptr));
        ajouter->setText(QCoreApplication::translate("MainWindow", "Ajouter", nullptr));
        annuler->setText(QCoreApplication::translate("MainWindow", "Annuler", nullptr));
        label_156->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p align=\"center\">Ajout &amp; Modifier</p><p align=\"center\"><br/></p></body></html>", nullptr));
        id_rech->setPlaceholderText(QCoreApplication::translate("MainWindow", "identifiant", nullptr));
        chercher_2->setText(QCoreApplication::translate("MainWindow", "chercher", nullptr));
        pdf_2->setText(QCoreApplication::translate("MainWindow", "Exportation pdf", nullptr));
        label_166->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-size:12pt; font-weight:700;\">Recherche employ\303\251 :</span></p></body></html>", nullptr));
        comboBox_tri_3->setItemText(0, QCoreApplication::translate("MainWindow", "Trier selon ", nullptr));
        comboBox_tri_3->setItemText(1, QString());
        comboBox_tri_3->setItemText(2, QCoreApplication::translate("MainWindow", "Salaire d\303\251croissant", nullptr));
        comboBox_tri_3->setItemText(3, QCoreApplication::translate("MainWindow", "salaire croissant", nullptr));
        comboBox_tri_3->setItemText(4, QCoreApplication::translate("MainWindow", "date d'emboche d\303\251c", nullptr));
        comboBox_tri_3->setItemText(5, QCoreApplication::translate("MainWindow", "date d'emboche croi", nullptr));

        QTableWidgetItem *___qtablewidgetitem = tableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("MainWindow", "id", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("MainWindow", "name", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidget->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("MainWindow", "Prenom", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidget->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("MainWindow", "Date", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = tableWidget->horizontalHeaderItem(4);
        ___qtablewidgetitem4->setText(QCoreApplication::translate("MainWindow", "Poste", nullptr));
        QTableWidgetItem *___qtablewidgetitem5 = tableWidget->horizontalHeaderItem(5);
        ___qtablewidgetitem5->setText(QCoreApplication::translate("MainWindow", "Email", nullptr));
        QTableWidgetItem *___qtablewidgetitem6 = tableWidget->horizontalHeaderItem(6);
        ___qtablewidgetitem6->setText(QCoreApplication::translate("MainWindow", "Salaire", nullptr));
        QTableWidgetItem *___qtablewidgetitem7 = tableWidget->horizontalHeaderItem(7);
        ___qtablewidgetitem7->setText(QCoreApplication::translate("MainWindow", "Sexe", nullptr));
        aceuille_2->setTabText(aceuille_2->indexOf(tab_6), QCoreApplication::translate("MainWindow", "Consulter", nullptr));
        label_184->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p align=\"center\"><span style=\" font-size:20pt;\">Demande Cong\303\251s</span></p></body></html>", nullptr));
        prenom_conge_2->setPlaceholderText(QCoreApplication::translate("MainWindow", "Pr\303\251nom", nullptr));
        nom_conge_2->setPlaceholderText(QCoreApplication::translate("MainWindow", "Nom", nullptr));
        confiramtion_conge_2->setText(QCoreApplication::translate("MainWindow", "Je comprends que  prendre cong\303\251 peut entra\303\256ner une baisse de salaire horaire/journalier", nullptr));
        soumettre_2->setText(QCoreApplication::translate("MainWindow", "Soumettre", nullptr));
        label_168->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-weight:700;\">Nom :</span></p></body></html>", nullptr));
        label_169->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-weight:700;\">Prenom :</span></p></body></html>", nullptr));
        label_174->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-weight:700;\">Date de d\303\251but du cong\303\251 :</span></p></body></html>", nullptr));
        label_175->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-weight:700;\">Date de fin de cong\303\251 :</span></p></body></html>", nullptr));
        label_167->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-weight:700;\">ID Employ\303\251 :</span></p></body></html>", nullptr));
        id_emp_4->setPlaceholderText(QCoreApplication::translate("MainWindow", "Id", nullptr));
        label_170->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-weight:700;\">Email Employ\303\251 :</span></p></body></html>", nullptr));
        email_conge_2->setText(QString());
        email_conge_2->setPlaceholderText(QCoreApplication::translate("MainWindow", "email", nullptr));
        label_171->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-weight:700;\">Departement de l'Employ\303\251 :</span></p></body></html>", nullptr));
        label_172->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-weight:700;\">Poste de  l'Employ\303\251 :</span></p></body></html>", nullptr));
        label_173->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-weight:700;\">La raison de la demande de cong\303\251 :</span></p></body></html>", nullptr));
        raison_conge_2->setItemText(0, QCoreApplication::translate("MainWindow", "veuillez s\303\251lectionner", nullptr));
        raison_conge_2->setItemText(1, QCoreApplication::translate("MainWindow", "cong\303\251 de maladie", nullptr));
        raison_conge_2->setItemText(2, QCoreApplication::translate("MainWindow", "Raison familiales", nullptr));
        raison_conge_2->setItemText(3, QCoreApplication::translate("MainWindow", "Funr\303\251eilles/deuil", nullptr));
        raison_conge_2->setItemText(4, QCoreApplication::translate("MainWindow", "Vacances", nullptr));
        raison_conge_2->setItemText(5, QCoreApplication::translate("MainWindow", "Autre", nullptr));

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
