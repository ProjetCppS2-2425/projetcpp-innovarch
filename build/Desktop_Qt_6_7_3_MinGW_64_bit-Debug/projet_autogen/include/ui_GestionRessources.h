/********************************************************************************
** Form generated from reading UI file 'GestionRessources.ui'
**
** Created by: Qt User Interface Compiler version 6.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GESTIONRESSOURCES_H
#define UI_GESTIONRESSOURCES_H

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
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_GestionRessources
{
public:
    QWidget *centralwidget;
    QTabWidget *acceuil1;
    QWidget *tab_6;
    QWidget *widget_7;
    QComboBox *triCb;
    QLineEdit *recherche;
    QPushButton *chercher;
    QTableView *tableView;
    QPushButton *exportPdf;
    QComboBox *rechercheCb;
    QPushButton *triButton;
    QFrame *frame;
    QLabel *label;
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout;
    QPushButton *pushButton;
    QPushButton *pushButton_4;
    QPushButton *pushButton_3;
    QPushButton *pushButton_2;
    QPushButton *pushButton_5;
    QPushButton *pushButton_6;
    QFrame *frame_6;
    QLineEdit *nomRessource;
    QDateEdit *dateAjout;
    QLabel *label_148;
    QLabel *label_149;
    QLabel *label_150;
    QLineEdit *coutRessource;
    QLabel *label_154;
    QComboBox *categorieRessource;
    QLabel *label_155;
    QLabel *label_151;
    QDateEdit *dateEntretien;
    QLineEdit *fournisseurRessource;
    QLabel *label_160;
    QLabel *label_161;
    QLineEdit *quantiteRessource;
    QPushButton *modifier;
    QPushButton *annuler;
    QPushButton *ajouter;
    QComboBox *etatRessource;
    QLabel *label_156;
    QWidget *tab_7;
    QGraphicsView *acceuil2;
    QPushButton *statpb;
    QGraphicsView *acceuil3;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *GestionRessources)
    {
        if (GestionRessources->objectName().isEmpty())
            GestionRessources->setObjectName("GestionRessources");
        GestionRessources->resize(1371, 866);
        GestionRessources->setMinimumSize(QSize(800, 600));
        centralwidget = new QWidget(GestionRessources);
        centralwidget->setObjectName("centralwidget");
        QSizePolicy sizePolicy(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(centralwidget->sizePolicy().hasHeightForWidth());
        centralwidget->setSizePolicy(sizePolicy);
        acceuil1 = new QTabWidget(centralwidget);
        acceuil1->setObjectName("acceuil1");
        acceuil1->setGeometry(QRect(0, 0, 1371, 841));
        acceuil1->setMinimumSize(QSize(300, 300));
        acceuil1->setAutoFillBackground(false);
        acceuil1->setStyleSheet(QString::fromUtf8("background-color:#F8EDEB;\n"
""));
        tab_6 = new QWidget();
        tab_6->setObjectName("tab_6");
        widget_7 = new QWidget(tab_6);
        widget_7->setObjectName("widget_7");
        widget_7->setGeometry(QRect(620, 110, 781, 541));
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
        triCb = new QComboBox(widget_7);
        triCb->addItem(QString());
        triCb->addItem(QString());
        triCb->addItem(QString());
        triCb->addItem(QString());
        triCb->setObjectName("triCb");
        triCb->setGeometry(QRect(460, 21, 111, 31));
        triCb->setAutoFillBackground(false);
        triCb->setStyleSheet(QString::fromUtf8("border: 2px solid #9f86c0;  /* Default thicker border */\n"
"border-radius: 5px;\n"
"background-color: white;  /* Ensure background stays white */\n"
"\n"
"\n"
"\n"
""));
        triCb->setDuplicatesEnabled(false);
        triCb->setFrame(true);
        recherche = new QLineEdit(widget_7);
        recherche->setObjectName("recherche");
        recherche->setGeometry(QRect(140, 20, 141, 31));
        recherche->setStyleSheet(QString::fromUtf8("QLineEdit {\n"
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
        chercher = new QPushButton(widget_7);
        chercher->setObjectName("chercher");
        chercher->setGeometry(QRect(290, 20, 41, 31));
        chercher->setStyleSheet(QString::fromUtf8("QPushButton#chercher{\n"
"	 border: 1.5px solid #9f86c0;/* Default thicker border */\n"
"    border-radius: 5px;\n"
"	background-color: white;\n"
"}\n"
"QPushButton#chercher:hover {\n"
"    background-color: #be95c4; \n"
"}"));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/ressources/images/search.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        chercher->setIcon(icon);
        chercher->setIconSize(QSize(16, 16));
        tableView = new QTableView(widget_7);
        tableView->setObjectName("tableView");
        tableView->setGeometry(QRect(20, 70, 621, 371));
        tableView->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        exportPdf = new QPushButton(widget_7);
        exportPdf->setObjectName("exportPdf");
        exportPdf->setGeometry(QRect(470, 472, 161, 41));
        exportPdf->setStyleSheet(QString::fromUtf8("QPushButton#exportPdf{\n"
"    background-color: rgb(255, 255, 255);\n"
"	border: 2px solid #9f86c0 ;/* Default thicker border */\n"
"    border-radius: 5px;\n"
"}\n"
"QPushButton#exportPdf:hover {\n"
"    background-color: #9f86c0; \n"
"}"));
        rechercheCb = new QComboBox(widget_7);
        rechercheCb->addItem(QString());
        rechercheCb->addItem(QString());
        rechercheCb->addItem(QString());
        rechercheCb->addItem(QString());
        rechercheCb->setObjectName("rechercheCb");
        rechercheCb->setGeometry(QRect(20, 20, 111, 31));
        rechercheCb->setAutoFillBackground(false);
        rechercheCb->setStyleSheet(QString::fromUtf8("\n"
"\n"
"    border: 2px solid #9f86c0;  /* Default thicker border */\n"
"    border-radius: 5px;\n"
"    background-color: white;  /* Ensure background stays white */\n"
"\n"
"\n"
"\n"
""));
        rechercheCb->setDuplicatesEnabled(false);
        rechercheCb->setFrame(true);
        triButton = new QPushButton(widget_7);
        triButton->setObjectName("triButton");
        triButton->setGeometry(QRect(590, 20, 41, 31));
        triButton->setStyleSheet(QString::fromUtf8("QPushButton#triButton{\n"
"	 border: 1.5px solid #9f86c0;/* Default thicker border */\n"
"    border-radius: 5px;\n"
"	background-color: white;\n"
"}\n"
"QPushButton#triButton:hover {\n"
"    background-color: #be95c4; \n"
"}"));
        triButton->setIconSize(QSize(16, 16));
        frame = new QFrame(tab_6);
        frame->setObjectName("frame");
        frame->setGeometry(QRect(-10, 0, 201, 791));
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
        layoutWidget = new QWidget(frame);
        layoutWidget->setObjectName("layoutWidget");
        layoutWidget->setGeometry(QRect(0, 220, 191, 331));
        verticalLayout = new QVBoxLayout(layoutWidget);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        pushButton = new QPushButton(layoutWidget);
        pushButton->setObjectName("pushButton");
        pushButton->setMinimumSize(QSize(0, 0));
        QFont font;
        font.setFamilies({QString::fromUtf8("Roboto")});
        font.setPointSize(13);
        pushButton->setFont(font);
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
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/ressources/images/employes.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        icon1.addFile(QString::fromUtf8(":/ressources/images/employes.png"), QSize(), QIcon::Mode::Normal, QIcon::State::On);
        pushButton->setIcon(icon1);
        pushButton->setIconSize(QSize(25, 25));

        verticalLayout->addWidget(pushButton);

        pushButton_4 = new QPushButton(layoutWidget);
        pushButton_4->setObjectName("pushButton_4");
        pushButton_4->setMinimumSize(QSize(0, 0));
        QFont font1;
        font1.setPointSize(13);
        pushButton_4->setFont(font1);
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
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/ressources/images/clients.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        icon2.addFile(QString::fromUtf8(":/ressources/images/clients.png"), QSize(), QIcon::Mode::Normal, QIcon::State::On);
        pushButton_4->setIcon(icon2);
        pushButton_4->setIconSize(QSize(25, 25));

        verticalLayout->addWidget(pushButton_4);

        pushButton_3 = new QPushButton(layoutWidget);
        pushButton_3->setObjectName("pushButton_3");
        pushButton_3->setMinimumSize(QSize(0, 0));
        pushButton_3->setFont(font);
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
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/ressources/images/project.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        icon3.addFile(QString::fromUtf8(":/ressources/images/project.png"), QSize(), QIcon::Mode::Normal, QIcon::State::On);
        pushButton_3->setIcon(icon3);
        pushButton_3->setIconSize(QSize(25, 25));

        verticalLayout->addWidget(pushButton_3);

        pushButton_2 = new QPushButton(layoutWidget);
        pushButton_2->setObjectName("pushButton_2");
        pushButton_2->setMinimumSize(QSize(0, 0));
        pushButton_2->setFont(font);
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
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/ressources/images/desk.ico"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        icon4.addFile(QString::fromUtf8(":/ressources/images/desk.ico"), QSize(), QIcon::Mode::Normal, QIcon::State::On);
        pushButton_2->setIcon(icon4);
        pushButton_2->setIconSize(QSize(25, 25));

        verticalLayout->addWidget(pushButton_2);

        pushButton_5 = new QPushButton(layoutWidget);
        pushButton_5->setObjectName("pushButton_5");
        pushButton_5->setMinimumSize(QSize(0, 0));
        pushButton_5->setFont(font);
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
        QIcon icon5;
        icon5.addFile(QString::fromUtf8(":/ressources/images/contrats.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        icon5.addFile(QString::fromUtf8(":/ressources/images/contrats.png"), QSize(), QIcon::Mode::Normal, QIcon::State::On);
        pushButton_5->setIcon(icon5);
        pushButton_5->setIconSize(QSize(25, 25));

        verticalLayout->addWidget(pushButton_5);

        pushButton_6 = new QPushButton(layoutWidget);
        pushButton_6->setObjectName("pushButton_6");
        pushButton_6->setMinimumSize(QSize(0, 0));
        pushButton_6->setFont(font);
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
        QIcon icon6;
        icon6.addFile(QString::fromUtf8(":/ressources/images/architect.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        icon6.addFile(QString::fromUtf8(":/ressources/images/architect.png"), QSize(), QIcon::Mode::Normal, QIcon::State::On);
        pushButton_6->setIcon(icon6);
        pushButton_6->setIconSize(QSize(25, 25));

        verticalLayout->addWidget(pushButton_6);

        layoutWidget->raise();
        label->raise();
        frame_6 = new QFrame(tab_6);
        frame_6->setObjectName("frame_6");
        frame_6->setGeometry(QRect(250, 110, 311, 551));
        frame_6->setStyleSheet(QString::fromUtf8("/* QWidget styling */\n"
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
        nomRessource = new QLineEdit(frame_6);
        nomRessource->setObjectName("nomRessource");
        nomRessource->setGeometry(QRect(10, 90, 113, 31));
        nomRessource->setStyleSheet(QString::fromUtf8("QLineEdit {\n"
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
        dateAjout = new QDateEdit(frame_6);
        dateAjout->setObjectName("dateAjout");
        dateAjout->setGeometry(QRect(10, 250, 121, 31));
        dateAjout->setStyleSheet(QString::fromUtf8("\n"
"    border: 2px solid #4e1764;  /* Default thicker border */\n"
"    border-radius: 5px;\n"
"    background-color: white;  /* Ensure background stays white */\n"
"\n"
"\n"
"\n"
""));
        label_148 = new QLabel(frame_6);
        label_148->setObjectName("label_148");
        label_148->setGeometry(QRect(2, 210, 112, 31));
        label_148->setStyleSheet(QString::fromUtf8(""));
        label_149 = new QLabel(frame_6);
        label_149->setObjectName("label_149");
        label_149->setGeometry(QRect(2, 50, 121, 31));
        label_149->setStyleSheet(QString::fromUtf8(""));
        label_150 = new QLabel(frame_6);
        label_150->setObjectName("label_150");
        label_150->setGeometry(QRect(2, 130, 101, 35));
        label_150->setStyleSheet(QString::fromUtf8(""));
        coutRessource = new QLineEdit(frame_6);
        coutRessource->setObjectName("coutRessource");
        coutRessource->setGeometry(QRect(180, 410, 111, 31));
        coutRessource->setStyleSheet(QString::fromUtf8("QLineEdit {\n"
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
        label_154 = new QLabel(frame_6);
        label_154->setObjectName("label_154");
        label_154->setGeometry(QRect(180, 370, 111, 31));
        label_154->setStyleSheet(QString::fromUtf8(""));
        categorieRessource = new QComboBox(frame_6);
        categorieRessource->addItem(QString());
        categorieRessource->addItem(QString());
        categorieRessource->addItem(QString());
        categorieRessource->addItem(QString());
        categorieRessource->addItem(QString());
        categorieRessource->addItem(QString());
        categorieRessource->addItem(QString());
        categorieRessource->addItem(QString());
        categorieRessource->addItem(QString());
        categorieRessource->setObjectName("categorieRessource");
        categorieRessource->setGeometry(QRect(10, 170, 141, 32));
        categorieRessource->setStyleSheet(QString::fromUtf8("\n"
"    border: 2px solid #4e1764;  /* Default thicker border */\n"
"    border-radius: 5px;\n"
"    background-color: white;  /* Ensure background stays white */\n"
"\n"
"\n"
"\n"
""));
        label_155 = new QLabel(frame_6);
        label_155->setObjectName("label_155");
        label_155->setGeometry(QRect(172, 130, 91, 31));
        label_155->setStyleSheet(QString::fromUtf8(""));
        label_151 = new QLabel(frame_6);
        label_151->setObjectName("label_151");
        label_151->setGeometry(QRect(2, 290, 171, 31));
        label_151->setStyleSheet(QString::fromUtf8(""));
        dateEntretien = new QDateEdit(frame_6);
        dateEntretien->setObjectName("dateEntretien");
        dateEntretien->setGeometry(QRect(10, 330, 111, 31));
        dateEntretien->setStyleSheet(QString::fromUtf8("\n"
"    border: 2px solid #4e1764;  /* Default thicker border */\n"
"    border-radius: 5px;\n"
"    background-color: white;  /* Ensure background stays white */\n"
"\n"
"\n"
"\n"
""));
        fournisseurRessource = new QLineEdit(frame_6);
        fournisseurRessource->setObjectName("fournisseurRessource");
        fournisseurRessource->setGeometry(QRect(180, 250, 113, 29));
        fournisseurRessource->setStyleSheet(QString::fromUtf8("QLineEdit {\n"
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
        label_160 = new QLabel(frame_6);
        label_160->setObjectName("label_160");
        label_160->setGeometry(QRect(172, 210, 121, 31));
        label_160->setStyleSheet(QString::fromUtf8(""));
        label_161 = new QLabel(frame_6);
        label_161->setObjectName("label_161");
        label_161->setGeometry(QRect(2, 370, 91, 30));
        label_161->setStyleSheet(QString::fromUtf8(""));
        quantiteRessource = new QLineEdit(frame_6);
        quantiteRessource->setObjectName("quantiteRessource");
        quantiteRessource->setGeometry(QRect(180, 170, 111, 31));
        quantiteRessource->setStyleSheet(QString::fromUtf8("QLineEdit {\n"
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
        modifier = new QPushButton(frame_6);
        modifier->setObjectName("modifier");
        modifier->setGeometry(QRect(115, 480, 85, 31));
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
        annuler = new QPushButton(frame_6);
        annuler->setObjectName("annuler");
        annuler->setGeometry(QRect(18, 480, 85, 31));
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
        ajouter = new QPushButton(frame_6);
        ajouter->setObjectName("ajouter");
        ajouter->setGeometry(QRect(211, 480, 85, 31));
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
        etatRessource = new QComboBox(frame_6);
        etatRessource->addItem(QString());
        etatRessource->addItem(QString());
        etatRessource->addItem(QString());
        etatRessource->addItem(QString());
        etatRessource->setObjectName("etatRessource");
        etatRessource->setGeometry(QRect(10, 410, 141, 32));
        etatRessource->setStyleSheet(QString::fromUtf8("\n"
"    border: 2px solid #4e1764;  /* Default thicker border */\n"
"    border-radius: 5px;\n"
"    background-color: white;  /* Ensure background stays white */\n"
"\n"
"\n"
"\n"
""));
        label_156 = new QLabel(tab_6);
        label_156->setObjectName("label_156");
        label_156->setGeometry(QRect(290, 70, 221, 51));
        QFont font2;
        font2.setBold(true);
        font2.setItalic(true);
        label_156->setFont(font2);
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
        acceuil1->addTab(tab_6, QString());
        tab_7 = new QWidget();
        tab_7->setObjectName("tab_7");
        acceuil2 = new QGraphicsView(tab_7);
        acceuil2->setObjectName("acceuil2");
        acceuil2->setGeometry(QRect(10, 10, 591, 631));
        statpb = new QPushButton(tab_7);
        statpb->setObjectName("statpb");
        statpb->setGeometry(QRect(240, 50, 161, 51));
        statpb->setStyleSheet(QString::fromUtf8("QPushButton#statpb{\n"
"    background-color: rgb(255, 255, 255);\n"
"	 border: 2px solid #9f86c0 ;/* Default thicker border */\n"
"    border-radius: 5px;\n"
"	 font-size: 13px;\n"
"    font-weight: bold;\n"
"}\n"
"QPushButton#statpb:hover {\n"
"    background-color: #9f86c0; \n"
"}"));
        acceuil3 = new QGraphicsView(tab_7);
        acceuil3->setObjectName("acceuil3");
        acceuil3->setGeometry(QRect(610, 10, 741, 631));
        acceuil1->addTab(tab_7, QString());
        GestionRessources->setCentralWidget(centralwidget);
        menubar = new QMenuBar(GestionRessources);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 1371, 18));
        GestionRessources->setMenuBar(menubar);
        statusbar = new QStatusBar(GestionRessources);
        statusbar->setObjectName("statusbar");
        GestionRessources->setStatusBar(statusbar);

        retranslateUi(GestionRessources);

        acceuil1->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(GestionRessources);
    } // setupUi

    void retranslateUi(QMainWindow *GestionRessources)
    {
        GestionRessources->setWindowTitle(QCoreApplication::translate("GestionRessources", "MainWindow", nullptr));
        triCb->setItemText(0, QCoreApplication::translate("GestionRessources", "Trier selon ", nullptr));
        triCb->setItemText(1, QCoreApplication::translate("GestionRessources", "Date d'achat", nullptr));
        triCb->setItemText(2, QCoreApplication::translate("GestionRessources", "Quantit\303\251", nullptr));
        triCb->setItemText(3, QCoreApplication::translate("GestionRessources", "Co\303\273t", nullptr));

        recherche->setPlaceholderText(QCoreApplication::translate("GestionRessources", "Entrez votre recherche", nullptr));
        chercher->setText(QString());
        exportPdf->setText(QCoreApplication::translate("GestionRessources", "Exportation pdf", nullptr));
        rechercheCb->setItemText(0, QCoreApplication::translate("GestionRessources", "Rechercher selon ", nullptr));
        rechercheCb->setItemText(1, QCoreApplication::translate("GestionRessources", "ID", nullptr));
        rechercheCb->setItemText(2, QCoreApplication::translate("GestionRessources", "Date d'achat", nullptr));
        rechercheCb->setItemText(3, QCoreApplication::translate("GestionRessources", "Quantit\303\251", nullptr));

        triButton->setText(QString());
        label->setText(QString());
        pushButton->setText(QCoreApplication::translate("GestionRessources", " Employ\303\251s", nullptr));
        pushButton_4->setText(QCoreApplication::translate("GestionRessources", " Clients", nullptr));
        pushButton_3->setText(QCoreApplication::translate("GestionRessources", " Projets", nullptr));
        pushButton_2->setText(QCoreApplication::translate("GestionRessources", " Ressources", nullptr));
        pushButton_5->setText(QCoreApplication::translate("GestionRessources", " Contrats", nullptr));
        pushButton_6->setText(QCoreApplication::translate("GestionRessources", " Contracteurs", nullptr));
        nomRessource->setPlaceholderText(QCoreApplication::translate("GestionRessources", "Entrez le nom de la ressource", nullptr));
        label_148->setText(QCoreApplication::translate("GestionRessources", "<html><head/><body><p><span style=\" font-weight:700;\">Date d'ajout :</span></p></body></html>", nullptr));
        label_149->setText(QCoreApplication::translate("GestionRessources", "<html><head/><body><p><span style=\" font-weight:700;\">Nom ressource :</span></p></body></html>", nullptr));
        label_150->setText(QCoreApplication::translate("GestionRessources", "<html><head/><body><p><span style=\" font-weight:700;\">Cat\303\251gorie :</span></p></body></html>", nullptr));
        coutRessource->setPlaceholderText(QCoreApplication::translate("GestionRessources", "Entrez le co\303\273t", nullptr));
        label_154->setText(QCoreApplication::translate("GestionRessources", "<html><head/><body><p><span style=\" font-weight:700;\">Co\303\273t :</span></p></body></html>", nullptr));
        categorieRessource->setItemText(0, QCoreApplication::translate("GestionRessources", "S\303\251lectionnez la cat\303\251gorie", nullptr));
        categorieRessource->setItemText(1, QCoreApplication::translate("GestionRessources", "Eclairage", nullptr));
        categorieRessource->setItemText(2, QCoreApplication::translate("GestionRessources", "Technologie", nullptr));
        categorieRessource->setItemText(3, QCoreApplication::translate("GestionRessources", "Papeterie", nullptr));
        categorieRessource->setItemText(4, QCoreApplication::translate("GestionRessources", "Nettoyage", nullptr));
        categorieRessource->setItemText(5, QCoreApplication::translate("GestionRessources", "Mobilier", nullptr));
        categorieRessource->setItemText(6, QCoreApplication::translate("GestionRessources", "Electrique", nullptr));
        categorieRessource->setItemText(7, QCoreApplication::translate("GestionRessources", "Outils", nullptr));
        categorieRessource->setItemText(8, QCoreApplication::translate("GestionRessources", "Autre", nullptr));

        categorieRessource->setPlaceholderText(QCoreApplication::translate("GestionRessources", "S\303\251lectionnez la cat\303\251gorie", nullptr));
        label_155->setText(QCoreApplication::translate("GestionRessources", "<html><head/><body><p><span style=\" font-weight:700;\">Quantit\303\251 :</span></p></body></html>", nullptr));
        label_151->setText(QCoreApplication::translate("GestionRessources", "<html><head/><body><p><span style=\" font-weight:700;\">Date dernier entretien :</span></p></body></html>", nullptr));
        fournisseurRessource->setPlaceholderText(QCoreApplication::translate("GestionRessources", "Num\303\251ro du fournisseur", nullptr));
        label_160->setText(QCoreApplication::translate("GestionRessources", "<html><head/><body><p><span style=\" font-weight:700;\">Fournisseur :</span></p></body></html>", nullptr));
        label_161->setText(QCoreApplication::translate("GestionRessources", "<html><head/><body><p><span style=\" font-weight:700;\">Etat :</span></p></body></html>", nullptr));
        quantiteRessource->setPlaceholderText(QCoreApplication::translate("GestionRessources", "Entrez sa quantit\303\251", nullptr));
        modifier->setText(QCoreApplication::translate("GestionRessources", "Modifier", nullptr));
        annuler->setText(QCoreApplication::translate("GestionRessources", "Annuler", nullptr));
        ajouter->setText(QCoreApplication::translate("GestionRessources", "Ajouter", nullptr));
        etatRessource->setItemText(0, QCoreApplication::translate("GestionRessources", "S\303\251lectionnez l'\303\251tat", nullptr));
        etatRessource->setItemText(1, QCoreApplication::translate("GestionRessources", "Disponible", nullptr));
        etatRessource->setItemText(2, QCoreApplication::translate("GestionRessources", "Sous maintenance", nullptr));
        etatRessource->setItemText(3, QCoreApplication::translate("GestionRessources", "En utilisation", nullptr));

        etatRessource->setPlaceholderText(QCoreApplication::translate("GestionRessources", "S\303\251lectionnez la cat\303\251gorie", nullptr));
        label_156->setText(QCoreApplication::translate("GestionRessources", "<html><head/><body><p align=\"center\"><span style=\" font-style:normal;\">Ajout ressources</span></p><p align=\"center\"><br/></p></body></html>", nullptr));
        acceuil1->setTabText(acceuil1->indexOf(tab_6), QCoreApplication::translate("GestionRessources", "Consulter", nullptr));
        statpb->setText(QCoreApplication::translate("GestionRessources", "Statistiques Ressources ", nullptr));
        acceuil1->setTabText(acceuil1->indexOf(tab_7), QCoreApplication::translate("GestionRessources", "Statistique", nullptr));
    } // retranslateUi

};

namespace Ui {
    class GestionRessources: public Ui_GestionRessources {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GESTIONRESSOURCES_H
