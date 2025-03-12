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
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QTabWidget *aceuille_2;
    QWidget *tab_6;
    QWidget *widget_7;
    QComboBox *comboBox_tri_2;
    QPushButton *supprimer;
    QLineEdit *id_rech_2;
    QPushButton *chercher_2;
    QTableView *tableView;
    QPushButton *modifier2;
    QPushButton *pdf_2;
    QComboBox *comboBox_2;
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
    QLabel *label_146;
    QLineEdit *lineEdit;
    QLineEdit *lineEdit_2;
    QDateEdit *dateEdit;
    QLineEdit *lineEdit_3;
    QLabel *label_148;
    QLabel *label_149;
    QLabel *label_150;
    QLineEdit *lineEdit_5;
    QLabel *label_154;
    QComboBox *comboBox;
    QLabel *label_155;
    QLabel *label_151;
    QDateEdit *dateEdit_2;
    QLineEdit *lineEdit_6;
    QLabel *label_160;
    QLabel *label_161;
    QLineEdit *lineEdit_7;
    QPushButton *modifier;
    QPushButton *annuler;
    QPushButton *ajouter;
    QLabel *label_152;
    QLineEdit *lineEdit_4;
    QLabel *label_156;
    QWidget *tab_7;
    QGraphicsView *pie_2;
    QFrame *line_2;
    QGraphicsView *bar_2;
    QPushButton *stat1_2;
    QPushButton *stat2_2;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(1350, 822);
        MainWindow->setMinimumSize(QSize(800, 600));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        QSizePolicy sizePolicy(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(centralwidget->sizePolicy().hasHeightForWidth());
        centralwidget->setSizePolicy(sizePolicy);
        aceuille_2 = new QTabWidget(centralwidget);
        aceuille_2->setObjectName("aceuille_2");
        aceuille_2->setGeometry(QRect(0, 0, 1351, 811));
        aceuille_2->setMinimumSize(QSize(300, 300));
        aceuille_2->setAutoFillBackground(false);
        aceuille_2->setStyleSheet(QString::fromUtf8("background-color:#F8EDEB;\n"
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
        comboBox_tri_2 = new QComboBox(widget_7);
        comboBox_tri_2->addItem(QString());
        comboBox_tri_2->addItem(QString());
        comboBox_tri_2->addItem(QString());
        comboBox_tri_2->setObjectName("comboBox_tri_2");
        comboBox_tri_2->setGeometry(QRect(500, 21, 141, 28));
        comboBox_tri_2->setAutoFillBackground(false);
        comboBox_tri_2->setStyleSheet(QString::fromUtf8("\n"
"\n"
"    border: 2px solid #9f86c0;  /* Default thicker border */\n"
"    border-radius: 5px;\n"
"    background-color: white;  /* Ensure background stays white */\n"
"\n"
"\n"
"\n"
""));
        comboBox_tri_2->setDuplicatesEnabled(false);
        comboBox_tri_2->setFrame(true);
        supprimer = new QPushButton(widget_7);
        supprimer->setObjectName("supprimer");
        supprimer->setGeometry(QRect(460, 450, 181, 41));
        supprimer->setStyleSheet(QString::fromUtf8("QPushButton#supprimer {\n"
"    background-color: rgb(255, 255, 255);\n"
"   border: 2px solid #D74C4C; /* Default thicker border */\n"
"    border-radius: 5px;\n"
"}\n"
"\n"
"QPushButton#supprimer:hover {\n"
"    background-color:#D74C4C;\n"
"}\n"
""));
        id_rech_2 = new QLineEdit(widget_7);
        id_rech_2->setObjectName("id_rech_2");
        id_rech_2->setGeometry(QRect(210, 20, 141, 31));
        id_rech_2->setStyleSheet(QString::fromUtf8("QLineEdit {\n"
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
        chercher_2->setGeometry(QRect(360, 20, 91, 31));
        chercher_2->setStyleSheet(QString::fromUtf8("QPushButton#chercher_2 {\n"
"    background-color: rgb(255, 255, 255);\n"
"        border: 2px solid #9f86c0 ;/* Default thicker border */\n"
"    border-radius: 5px;\n"
"}"));
        tableView = new QTableView(widget_7);
        tableView->setObjectName("tableView");
        tableView->setGeometry(QRect(20, 70, 621, 371));
        tableView->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        modifier2 = new QPushButton(widget_7);
        modifier2->setObjectName("modifier2");
        modifier2->setGeometry(QRect(460, 501, 181, 40));
        modifier2->setStyleSheet(QString::fromUtf8("QPushButton#modifier2 {\n"
"    background-color: rgb(255, 255, 255);\n"
"\n"
"        border: 2px solid #9f86c0 ;/* Default thicker border */\n"
"    border-radius: 5px;\n"
"}\n"
"\n"
"QPushButton#modifier2:hover {\n"
"    background-color: #9f86c0;\n"
"}"));
        pdf_2 = new QPushButton(widget_7);
        pdf_2->setObjectName("pdf_2");
        pdf_2->setGeometry(QRect(20, 472, 161, 41));
        pdf_2->setStyleSheet(QString::fromUtf8("QPushButton#pdf_2 {\n"
"    background-color: rgb(255, 255, 255);\n"
"        border: 2px solid #9f86c0 ;/* Default thicker border */\n"
"    border-radius: 5px;\n"
"}\n"
"QPushButton#pdf_2:hover {\n"
"    background-color: #9f86c0;\n"
"}"));
        comboBox_2 = new QComboBox(widget_7);
        comboBox_2->addItem(QString());
        comboBox_2->addItem(QString());
        comboBox_2->addItem(QString());
        comboBox_2->addItem(QString());
        comboBox_2->setObjectName("comboBox_2");
        comboBox_2->setGeometry(QRect(51, 20, 141, 28));
        frame = new QFrame(tab_6);
        frame->setObjectName("frame");
        frame->setGeometry(QRect(0, 0, 191, 741));
        frame->setStyleSheet(QString::fromUtf8("background-color: #4E1764\n"
""));
        frame->setFrameShape(QFrame::Shape::StyledPanel);
        frame->setFrameShadow(QFrame::Shadow::Raised);
        label = new QLabel(frame);
        label->setObjectName("label");
        label->setGeometry(QRect(0, 0, 191, 191));
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
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/ressources/images/employes.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        icon.addFile(QString::fromUtf8(":/ressources/images/employes.png"), QSize(), QIcon::Mode::Normal, QIcon::State::On);
        pushButton->setIcon(icon);
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
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/ressources/images/clients.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        icon1.addFile(QString::fromUtf8(":/ressources/images/clients.png"), QSize(), QIcon::Mode::Normal, QIcon::State::On);
        pushButton_4->setIcon(icon1);
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
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/ressources/images/project.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        icon2.addFile(QString::fromUtf8(":/ressources/images/project.png"), QSize(), QIcon::Mode::Normal, QIcon::State::On);
        pushButton_3->setIcon(icon2);
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
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/ressources/images/desk.ico"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        icon3.addFile(QString::fromUtf8(":/ressources/images/desk.ico"), QSize(), QIcon::Mode::Normal, QIcon::State::On);
        pushButton_2->setIcon(icon3);
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
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/ressources/images/contrats.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        icon4.addFile(QString::fromUtf8(":/ressources/images/contrats.png"), QSize(), QIcon::Mode::Normal, QIcon::State::On);
        pushButton_5->setIcon(icon4);
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
        QIcon icon5;
        icon5.addFile(QString::fromUtf8(":/ressources/images/architect.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        icon5.addFile(QString::fromUtf8(":/ressources/images/architect.png"), QSize(), QIcon::Mode::Normal, QIcon::State::On);
        pushButton_6->setIcon(icon5);
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
"        border-radius: 5px;\n"
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
"    subcon"
                        "trol-position: top right;\n"
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
"    border: 1px solid black; /* Change "
                        "border color when pressed */\n"
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
        label_146 = new QLabel(frame_6);
        label_146->setObjectName("label_146");
        label_146->setGeometry(QRect(2, 10, 101, 31));
        label_146->setStyleSheet(QString::fromUtf8(""));
        lineEdit = new QLineEdit(frame_6);
        lineEdit->setObjectName("lineEdit");
        lineEdit->setGeometry(QRect(10, 430, 111, 31));
        lineEdit->setStyleSheet(QString::fromUtf8("QLineEdit {\n"
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
        lineEdit_2 = new QLineEdit(frame_6);
        lineEdit_2->setObjectName("lineEdit_2");
        lineEdit_2->setGeometry(QRect(10, 120, 113, 26));
        lineEdit_2->setStyleSheet(QString::fromUtf8("QLineEdit {\n"
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
        dateEdit = new QDateEdit(frame_6);
        dateEdit->setObjectName("dateEdit");
        dateEdit->setGeometry(QRect(160, 350, 121, 31));
        dateEdit->setStyleSheet(QString::fromUtf8("\n"
"    border: 2px solid #4e1764;  /* Default thicker border */\n"
"    border-radius: 5px;\n"
"    background-color: white;  /* Ensure background stays white */\n"
"\n"
"\n"
"\n"
""));
        lineEdit_3 = new QLineEdit(frame_6);
        lineEdit_3->setObjectName("lineEdit_3");
        lineEdit_3->setGeometry(QRect(10, 50, 113, 26));
        lineEdit_3->setStyleSheet(QString::fromUtf8("QLineEdit {\n"
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
        label_148 = new QLabel(frame_6);
        label_148->setObjectName("label_148");
        label_148->setGeometry(QRect(10, 310, 141, 31));
        label_148->setStyleSheet(QString::fromUtf8(""));
        label_149 = new QLabel(frame_6);
        label_149->setObjectName("label_149");
        label_149->setGeometry(QRect(2, 80, 121, 31));
        label_149->setStyleSheet(QString::fromUtf8(""));
        label_150 = new QLabel(frame_6);
        label_150->setObjectName("label_150");
        label_150->setGeometry(QRect(2, 148, 101, 35));
        label_150->setStyleSheet(QString::fromUtf8(""));
        lineEdit_5 = new QLineEdit(frame_6);
        lineEdit_5->setObjectName("lineEdit_5");
        lineEdit_5->setGeometry(QRect(20, 270, 111, 31));
        lineEdit_5->setStyleSheet(QString::fromUtf8("QLineEdit {\n"
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
        label_154->setGeometry(QRect(20, 230, 111, 31));
        label_154->setStyleSheet(QString::fromUtf8(""));
        comboBox = new QComboBox(frame_6);
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->setObjectName("comboBox");
        comboBox->setGeometry(QRect(10, 190, 141, 32));
        comboBox->setStyleSheet(QString::fromUtf8("\n"
"    border: 2px solid #4e1764;  /* Default thicker border */\n"
"    border-radius: 5px;\n"
"    background-color: white;  /* Ensure background stays white */\n"
"\n"
"\n"
"\n"
""));
        label_155 = new QLabel(frame_6);
        label_155->setObjectName("label_155");
        label_155->setGeometry(QRect(172, 150, 91, 31));
        label_155->setStyleSheet(QString::fromUtf8(""));
        label_151 = new QLabel(frame_6);
        label_151->setObjectName("label_151");
        label_151->setGeometry(QRect(170, 310, 131, 31));
        label_151->setStyleSheet(QString::fromUtf8(""));
        dateEdit_2 = new QDateEdit(frame_6);
        dateEdit_2->setObjectName("dateEdit_2");
        dateEdit_2->setGeometry(QRect(20, 350, 111, 31));
        dateEdit_2->setStyleSheet(QString::fromUtf8("\n"
"    border: 2px solid #4e1764;  /* Default thicker border */\n"
"    border-radius: 5px;\n"
"    background-color: white;  /* Ensure background stays white */\n"
"\n"
"\n"
"\n"
""));
        lineEdit_6 = new QLineEdit(frame_6);
        lineEdit_6->setObjectName("lineEdit_6");
        lineEdit_6->setGeometry(QRect(180, 271, 113, 29));
        lineEdit_6->setStyleSheet(QString::fromUtf8("QLineEdit {\n"
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
        label_160->setGeometry(QRect(172, 228, 121, 31));
        label_160->setStyleSheet(QString::fromUtf8(""));
        label_161 = new QLabel(frame_6);
        label_161->setObjectName("label_161");
        label_161->setGeometry(QRect(2, 390, 121, 30));
        label_161->setStyleSheet(QString::fromUtf8(""));
        lineEdit_7 = new QLineEdit(frame_6);
        lineEdit_7->setObjectName("lineEdit_7");
        lineEdit_7->setGeometry(QRect(180, 190, 111, 31));
        lineEdit_7->setStyleSheet(QString::fromUtf8("QLineEdit {\n"
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
        modifier->setGeometry(QRect(111, 493, 85, 31));
        modifier->setStyleSheet(QString::fromUtf8("QPushButton#modifier {\n"
"        border-color: rgb(78, 23, 100);\n"
"    background-color:  #4e1764;  /* Vibrant mauve */\n"
"    border: none;\n"
"    font-size: 13.1px;\n"
"    font-weight: bold;\n"
"        color: white;\n"
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
        annuler->setGeometry(QRect(20, 493, 81, 31));
        annuler->setStyleSheet(QString::fromUtf8("QPushButton#annuler {\n"
"        border-color: rgb(78, 23, 100);\n"
"    background-color:  #4e1764;  /* Vibrant mauve */\n"
"    border: none;\n"
"    font-size: 13.1px;\n"
"    font-weight: bold;\n"
"        color: white;\n"
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
        ajouter->setGeometry(QRect(208, 493, 78, 31));
        ajouter->setStyleSheet(QString::fromUtf8("QPushButton#ajouter {\n"
"        border-color: rgb(78, 23, 100);\n"
"    background-color:  #4e1764;  /* Vibrant mauve */\n"
"   border: none;\n"
"    font-size: 13.1px;\n"
"    font-weight: bold;\n"
"        color: white;\n"
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
        label_152 = new QLabel(frame_6);
        label_152->setObjectName("label_152");
        label_152->setGeometry(QRect(150, 80, 121, 31));
        label_152->setStyleSheet(QString::fromUtf8(""));
        lineEdit_4 = new QLineEdit(frame_6);
        lineEdit_4->setObjectName("lineEdit_4");
        lineEdit_4->setGeometry(QRect(160, 120, 113, 26));
        lineEdit_4->setStyleSheet(QString::fromUtf8("QLineEdit {\n"
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
        aceuille_2->addTab(tab_6, QString());
        tab_7 = new QWidget();
        tab_7->setObjectName("tab_7");
        pie_2 = new QGraphicsView(tab_7);
        pie_2->setObjectName("pie_2");
        pie_2->setGeometry(QRect(10, 10, 911, 631));
        line_2 = new QFrame(tab_7);
        line_2->setObjectName("line_2");
        line_2->setGeometry(QRect(930, 10, 20, 631));
        line_2->setFrameShape(QFrame::Shape::VLine);
        line_2->setFrameShadow(QFrame::Shadow::Sunken);
        bar_2 = new QGraphicsView(tab_7);
        bar_2->setObjectName("bar_2");
        bar_2->setGeometry(QRect(10, 10, 911, 631));
        stat1_2 = new QPushButton(tab_7);
        stat1_2->setObjectName("stat1_2");
        stat1_2->setGeometry(QRect(750, 140, 161, 61));
        stat2_2 = new QPushButton(tab_7);
        stat2_2->setObjectName("stat2_2");
        stat2_2->setGeometry(QRect(750, 270, 161, 71));
        aceuille_2->addTab(tab_7, QString());
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 1350, 25));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        aceuille_2->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        comboBox_tri_2->setItemText(0, QCoreApplication::translate("MainWindow", "Trier selon ", nullptr));
        comboBox_tri_2->setItemText(1, QCoreApplication::translate("MainWindow", "Id decroissant ", nullptr));
        comboBox_tri_2->setItemText(2, QCoreApplication::translate("MainWindow", "Id croissant", nullptr));

        supprimer->setText(QCoreApplication::translate("MainWindow", "Supprimer", nullptr));
        id_rech_2->setPlaceholderText(QCoreApplication::translate("MainWindow", "Entrez l'id recherch\303\251", nullptr));
        chercher_2->setText(QCoreApplication::translate("MainWindow", "Chercher", nullptr));
        modifier2->setText(QCoreApplication::translate("MainWindow", "Modifier", nullptr));
        pdf_2->setText(QCoreApplication::translate("MainWindow", "Exportation pdf", nullptr));
        comboBox_2->setItemText(0, QCoreApplication::translate("MainWindow", "rechercher selon", nullptr));
        comboBox_2->setItemText(1, QCoreApplication::translate("MainWindow", "id", nullptr));
        comboBox_2->setItemText(2, QCoreApplication::translate("MainWindow", "nom", nullptr));
        comboBox_2->setItemText(3, QCoreApplication::translate("MainWindow", "prenom", nullptr));

        label->setText(QString());
        pushButton->setText(QCoreApplication::translate("MainWindow", " Employ\303\251s", nullptr));
        pushButton_4->setText(QCoreApplication::translate("MainWindow", " Clients", nullptr));
        pushButton_3->setText(QCoreApplication::translate("MainWindow", " Projets", nullptr));
        pushButton_2->setText(QCoreApplication::translate("MainWindow", " Ressources", nullptr));
        pushButton_5->setText(QCoreApplication::translate("MainWindow", " Contrats", nullptr));
        pushButton_6->setText(QCoreApplication::translate("MainWindow", " Contracteurs", nullptr));
        label_146->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-weight:700;\">Id client:</span></p></body></html>", nullptr));
        lineEdit->setPlaceholderText(QCoreApplication::translate("MainWindow", "Entrez le nom du projet", nullptr));
        lineEdit_2->setPlaceholderText(QCoreApplication::translate("MainWindow", "Entrez le nom ", nullptr));
#if QT_CONFIG(tooltip)
        lineEdit_3->setToolTip(QCoreApplication::translate("MainWindow", "<html><head/><body><p>dhzbebcl</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(whatsthis)
        lineEdit_3->setWhatsThis(QCoreApplication::translate("MainWindow", "<html><head/><body><p>vj j;</p></body></html>", nullptr));
#endif // QT_CONFIG(whatsthis)
        lineEdit_3->setPlaceholderText(QCoreApplication::translate("MainWindow", "Entrez l'id", nullptr));
        label_148->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-weight:700;\">Date debut projet :</span></p></body></html>", nullptr));
        label_149->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-weight:700;\">Nom client :</span></p></body></html>", nullptr));
        label_150->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-weight:700;\">Sexe :</span></p></body></html>", nullptr));
        lineEdit_5->setPlaceholderText(QCoreApplication::translate("MainWindow", "Entrez l'adresse", nullptr));
        label_154->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-weight:700;\">Adresse :</span></p></body></html>", nullptr));
        comboBox->setItemText(0, QCoreApplication::translate("MainWindow", "homme", nullptr));
        comboBox->setItemText(1, QCoreApplication::translate("MainWindow", "femme", nullptr));

        comboBox->setCurrentText(QString());
        comboBox->setPlaceholderText(QCoreApplication::translate("MainWindow", "S\303\251lectionnez le sexe", nullptr));
        label_155->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-weight:700;\">Telephone :</span></p></body></html>", nullptr));
        label_151->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-weight:700;\">Date fin projet :</span></p></body></html>", nullptr));
        lineEdit_6->setPlaceholderText(QCoreApplication::translate("MainWindow", "entrez l'email", nullptr));
        label_160->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-weight:700;\">email :</span></p></body></html>", nullptr));
        label_161->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-weight:700;\">nom du projet :</span></p></body></html>", nullptr));
        lineEdit_7->setPlaceholderText(QCoreApplication::translate("MainWindow", "Entrez le num", nullptr));
        modifier->setText(QCoreApplication::translate("MainWindow", "Modifier", nullptr));
        annuler->setText(QCoreApplication::translate("MainWindow", "Annuler", nullptr));
        ajouter->setText(QCoreApplication::translate("MainWindow", "Ajouter", nullptr));
        label_152->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-weight:700;\">Prenom client :</span></p></body></html>", nullptr));
        lineEdit_4->setPlaceholderText(QCoreApplication::translate("MainWindow", "Entrez le prenom", nullptr));
        label_156->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p align=\"center\"><span style=\" font-style:normal;\">Ajout clients</span></p><p align=\"center\"><br/></p></body></html>", nullptr));
        aceuille_2->setTabText(aceuille_2->indexOf(tab_6), QCoreApplication::translate("MainWindow", "Consulter", nullptr));
        stat1_2->setText(QCoreApplication::translate("MainWindow", "statistique sexe", nullptr));
        stat2_2->setText(QCoreApplication::translate("MainWindow", "statistique date", nullptr));
        aceuille_2->setTabText(aceuille_2->indexOf(tab_7), QCoreApplication::translate("MainWindow", "Statistique", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
