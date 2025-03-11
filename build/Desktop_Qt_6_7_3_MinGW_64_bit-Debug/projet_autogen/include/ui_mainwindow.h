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
#include <QtWidgets/QFrame>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
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
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout_7;
    QVBoxLayout *verticalLayout_31;
    QVBoxLayout *verticalLayout_32;
    QTabWidget *aceuille_2;
    QWidget *tab_6;
    QWidget *widget_7;
    QComboBox *comboBox_tri_2;
    QPushButton *supprimer;
    QLabel *label_158;
    QLineEdit *id_rech_2;
    QPushButton *chercher_2;
    QTableView *tableView_2;
    QPushButton *modifier2;
    QPushButton *pdf_2;
    QFrame *frame;
    QWidget *layoutWidget1;
    QVBoxLayout *verticalLayout;
    QPushButton *pushButton;
    QPushButton *pushButton_4;
    QPushButton *pushButton_3;
    QPushButton *pushButton_2;
    QPushButton *pushButton_5;
    QPushButton *pushButton_6;
    QLabel *label;
    QFrame *frame_6;
    QLabel *label_146;
    QLineEdit *lineEdit_2;
    QLineEdit *lineEdit_3;
    QLabel *label_149;
    QLabel *label_150;
    QLabel *label_154;
    QComboBox *comboBox;
    QLabel *label_155;
    QLineEdit *lineEdit_7;
    QPushButton *modifier;
    QPushButton *annuler;
    QPushButton *ajouter;
    QLineEdit *lineEdit_13;
    QLabel *label_168;
    QSpinBox *spinBox;
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
        MainWindow->resize(1501, 766);
        MainWindow->setMinimumSize(QSize(800, 600));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        layoutWidget = new QWidget(centralwidget);
        layoutWidget->setObjectName("layoutWidget");
        layoutWidget->setGeometry(QRect(0, -30, 1461, 769));
        horizontalLayout_7 = new QHBoxLayout(layoutWidget);
        horizontalLayout_7->setObjectName("horizontalLayout_7");
        horizontalLayout_7->setContentsMargins(0, 0, 0, 0);
        verticalLayout_31 = new QVBoxLayout();
        verticalLayout_31->setObjectName("verticalLayout_31");
        verticalLayout_32 = new QVBoxLayout();
        verticalLayout_32->setObjectName("verticalLayout_32");
        aceuille_2 = new QTabWidget(layoutWidget);
        aceuille_2->setObjectName("aceuille_2");
        aceuille_2->setMinimumSize(QSize(300, 300));
        aceuille_2->setAutoFillBackground(false);
        aceuille_2->setStyleSheet(QString::fromUtf8("background-color: #383254;"));
        tab_6 = new QWidget();
        tab_6->setObjectName("tab_6");
        widget_7 = new QWidget(tab_6);
        widget_7->setObjectName("widget_7");
        widget_7->setGeometry(QRect(620, 110, 811, 551));
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
        comboBox_tri_2->addItem(QString());
        comboBox_tri_2->addItem(QString());
        comboBox_tri_2->addItem(QString());
        comboBox_tri_2->setObjectName("comboBox_tri_2");
        comboBox_tri_2->setGeometry(QRect(580, 21, 141, 28));
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
"    background-color:#D74C4C; \n"
"}\n"
""));
        label_158 = new QLabel(widget_7);
        label_158->setObjectName("label_158");
        label_158->setGeometry(QRect(10, 20, 261, 31));
        QFont font;
        font.setFamilies({QString::fromUtf8("Roboto")});
        label_158->setFont(font);
        id_rech_2 = new QLineEdit(widget_7);
        id_rech_2->setObjectName("id_rech_2");
        id_rech_2->setGeometry(QRect(290, 20, 141, 31));
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
        chercher_2->setGeometry(QRect(440, 20, 91, 31));
        chercher_2->setStyleSheet(QString::fromUtf8("QPushButton#chercher_2 {\n"
"    background-color: rgb(255, 255, 255);\n"
"	border: 2px solid #9f86c0 ;/* Default thicker border */\n"
"    border-radius: 5px;\n"
"}"));
        tableView_2 = new QTableView(widget_7);
        tableView_2->setObjectName("tableView_2");
        tableView_2->setGeometry(QRect(20, 70, 621, 371));
        tableView_2->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        modifier2 = new QPushButton(widget_7);
        modifier2->setObjectName("modifier2");
        modifier2->setGeometry(QRect(460, 501, 181, 40));
        modifier2->setStyleSheet(QString::fromUtf8("QPushButton#modifier2 {\n"
"    background-color: rgb(255, 255, 255);\n"
"\n"
"	border: 2px solid #9f86c0 ;/* Default thicker border */\n"
"    border-radius: 5px;\n"
"}\n"
"\n"
"QPushButton#modifier2:hover {\n"
"    background-color: #e7e7e7; \n"
"}"));
        pdf_2 = new QPushButton(widget_7);
        pdf_2->setObjectName("pdf_2");
        pdf_2->setGeometry(QRect(20, 472, 161, 41));
        pdf_2->setStyleSheet(QString::fromUtf8("QPushButton#pdf_2 {\n"
"    background-color: rgb(255, 255, 255);\n"
"	border: 2px solid #9f86c0 ;/* Default thicker border */\n"
"    border-radius: 5px;\n"
"}"));
        frame = new QFrame(tab_6);
        frame->setObjectName("frame");
        frame->setGeometry(QRect(0, 0, 221, 741));
        frame->setStyleSheet(QString::fromUtf8("background-color: rgb(58, 42, 111);\n"
""));
        frame->setFrameShape(QFrame::Shape::StyledPanel);
        frame->setFrameShadow(QFrame::Shadow::Raised);
        layoutWidget1 = new QWidget(frame);
        layoutWidget1->setObjectName("layoutWidget1");
        layoutWidget1->setGeometry(QRect(10, 200, 191, 331));
        verticalLayout = new QVBoxLayout(layoutWidget1);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        pushButton = new QPushButton(layoutWidget1);
        pushButton->setObjectName("pushButton");
        pushButton->setMinimumSize(QSize(0, 0));
        QFont font1;
        font1.setFamilies({QString::fromUtf8("Roboto")});
        font1.setPointSize(13);
        pushButton->setFont(font1);
        pushButton->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    \n"
"	background-color: 231942;\n"
"    color: white;\n"
"    padding: 5px;\n"
"    border: none;\n"
"}\n"
"QPushButton:hover {\n"
"	background-color: rgb(86, 49, 139);\n"
"}\n"
"QPushButton:pressed {\n"
"    /*background-color: #BE95C4; */\n"
" 	/* Couleur au survol et au clic */\n"
"	background-color: rgb(60, 30, 86);\n"
"}\n"
""));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/ressources/images/employes.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        icon.addFile(QString::fromUtf8(":/ressources/images/employes.png"), QSize(), QIcon::Mode::Normal, QIcon::State::On);
        pushButton->setIcon(icon);
        pushButton->setIconSize(QSize(25, 25));

        verticalLayout->addWidget(pushButton);

        pushButton_4 = new QPushButton(layoutWidget1);
        pushButton_4->setObjectName("pushButton_4");
        pushButton_4->setMinimumSize(QSize(0, 0));
        QFont font2;
        font2.setPointSize(13);
        pushButton_4->setFont(font2);
        pushButton_4->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    \n"
"	background-color: 231942;\n"
"    color: white;\n"
"    padding: 5px;\n"
"    border: none;\n"
"}\n"
"QPushButton:hover {\n"
"	background-color: rgb(86, 49, 139);\n"
"}\n"
"QPushButton:pressed {\n"
"    /*background-color: #BE95C4; */\n"
" 	/* Couleur au survol et au clic */\n"
"	background-color: rgb(60, 30, 86);\n"
"}\n"
""));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/ressources/images/clients.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        icon1.addFile(QString::fromUtf8(":/ressources/images/clients.png"), QSize(), QIcon::Mode::Normal, QIcon::State::On);
        pushButton_4->setIcon(icon1);
        pushButton_4->setIconSize(QSize(25, 25));

        verticalLayout->addWidget(pushButton_4);

        pushButton_3 = new QPushButton(layoutWidget1);
        pushButton_3->setObjectName("pushButton_3");
        pushButton_3->setMinimumSize(QSize(0, 0));
        pushButton_3->setFont(font1);
        pushButton_3->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    \n"
"	background-color: 231942;\n"
"    color: white;\n"
"    padding: 5px;\n"
"    border: none;\n"
"}\n"
"QPushButton:hover {\n"
"	background-color: rgb(86, 49, 139);\n"
"}\n"
"QPushButton:pressed {\n"
"    /*background-color: #BE95C4; */\n"
" 	/* Couleur au survol et au clic */\n"
"	background-color: rgb(60, 30, 86);\n"
"}\n"
""));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/ressources/images/project.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        icon2.addFile(QString::fromUtf8(":/ressources/images/project.png"), QSize(), QIcon::Mode::Normal, QIcon::State::On);
        pushButton_3->setIcon(icon2);
        pushButton_3->setIconSize(QSize(25, 25));

        verticalLayout->addWidget(pushButton_3);

        pushButton_2 = new QPushButton(layoutWidget1);
        pushButton_2->setObjectName("pushButton_2");
        pushButton_2->setMinimumSize(QSize(0, 0));
        pushButton_2->setFont(font1);
        pushButton_2->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    \n"
"	background-color: 231942;\n"
"    color: white;\n"
"    padding: 5px;\n"
"    border: none;\n"
"}\n"
"QPushButton:hover {\n"
"	background-color: rgb(86, 49, 139);\n"
"}\n"
"QPushButton:pressed {\n"
"    /*background-color: #BE95C4; */\n"
" 	/* Couleur au survol et au clic */\n"
"	background-color: rgb(60, 30, 86);\n"
"}\n"
""));
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/ressources/images/desk.ico"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        icon3.addFile(QString::fromUtf8(":/ressources/images/desk.ico"), QSize(), QIcon::Mode::Normal, QIcon::State::On);
        pushButton_2->setIcon(icon3);
        pushButton_2->setIconSize(QSize(25, 25));

        verticalLayout->addWidget(pushButton_2);

        pushButton_5 = new QPushButton(layoutWidget1);
        pushButton_5->setObjectName("pushButton_5");
        pushButton_5->setMinimumSize(QSize(0, 0));
        pushButton_5->setFont(font1);
        pushButton_5->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    \n"
"	background-color: 231942;\n"
"    color: white;\n"
"    padding: 5px;\n"
"    border: none;\n"
"}\n"
"QPushButton:hover {\n"
"	background-color: rgb(86, 49, 139);\n"
"}\n"
"QPushButton:pressed {\n"
"    /*background-color: #BE95C4; */\n"
" 	/* Couleur au survol et au clic */\n"
"	background-color: rgb(60, 30, 86);\n"
"}\n"
""));
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/ressources/images/contrats.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        icon4.addFile(QString::fromUtf8(":/ressources/images/contrats.png"), QSize(), QIcon::Mode::Normal, QIcon::State::On);
        pushButton_5->setIcon(icon4);
        pushButton_5->setIconSize(QSize(25, 25));

        verticalLayout->addWidget(pushButton_5);

        pushButton_6 = new QPushButton(layoutWidget1);
        pushButton_6->setObjectName("pushButton_6");
        pushButton_6->setMinimumSize(QSize(0, 0));
        pushButton_6->setFont(font1);
        pushButton_6->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    \n"
"	background-color: 231942;\n"
"    color: white;\n"
"    padding: 5px;\n"
"    border: none;\n"
"}\n"
"QPushButton:hover {\n"
"	background-color: rgb(86, 49, 139);\n"
"}\n"
"QPushButton:pressed {\n"
"    /*background-color: #BE95C4; */\n"
" 	/* Couleur au survol et au clic */\n"
"	background-color: rgb(60, 30, 86);\n"
"}\n"
""));
        QIcon icon5;
        icon5.addFile(QString::fromUtf8(":/ressources/images/architect.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        icon5.addFile(QString::fromUtf8(":/ressources/images/architect.png"), QSize(), QIcon::Mode::Normal, QIcon::State::On);
        pushButton_6->setIcon(icon5);
        pushButton_6->setIconSize(QSize(25, 25));

        verticalLayout->addWidget(pushButton_6);

        label = new QLabel(frame);
        label->setObjectName("label");
        label->setGeometry(QRect(20, 20, 181, 111));
        label->setPixmap(QPixmap(QString::fromUtf8(":/ressources/images/logo trans.png")));
        label->setScaledContents(true);
        label->setWordWrap(false);
        frame_6 = new QFrame(tab_6);
        frame_6->setObjectName("frame_6");
        frame_6->setGeometry(QRect(250, 110, 311, 551));
        frame_6->setStyleSheet(QString::fromUtf8("/* QWidget styling */\n"
"QWidget {\n"
"    border: 2px solid #4e1764;  /* Set border width and color */\n"
"    padding: 10px;              /* Set padding inside the widget */\n"
"	border-radius: 5px;\n"
"	\n"
"	background-color: rgb(248, 237, 235);\n"
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
"    "
                        "subcontrol-origin: padding;\n"
"    subcontrol-position: top right;\n"
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
""
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
        label_146->setGeometry(QRect(2, 10, 121, 31));
        label_146->setStyleSheet(QString::fromUtf8(""));
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
        label_149 = new QLabel(frame_6);
        label_149->setObjectName("label_149");
        label_149->setGeometry(QRect(2, 80, 141, 31));
        label_149->setStyleSheet(QString::fromUtf8(""));
        label_150 = new QLabel(frame_6);
        label_150->setObjectName("label_150");
        label_150->setGeometry(QRect(2, 148, 101, 35));
        label_150->setStyleSheet(QString::fromUtf8(""));
        label_154 = new QLabel(frame_6);
        label_154->setObjectName("label_154");
        label_154->setGeometry(QRect(10, 230, 221, 61));
        label_154->setStyleSheet(QString::fromUtf8(""));
        comboBox = new QComboBox(frame_6);
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
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
        label_155->setGeometry(QRect(168, 148, 141, 31));
        label_155->setStyleSheet(QString::fromUtf8(""));
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
        annuler->setGeometry(QRect(20, 493, 81, 31));
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
        ajouter->setGeometry(QRect(208, 493, 78, 31));
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
        lineEdit_13 = new QLineEdit(frame_6);
        lineEdit_13->setObjectName("lineEdit_13");
        lineEdit_13->setGeometry(QRect(160, 120, 113, 26));
        lineEdit_13->setStyleSheet(QString::fromUtf8("QLineEdit {\n"
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
        label_168 = new QLabel(frame_6);
        label_168->setObjectName("label_168");
        label_168->setGeometry(QRect(153, 80, 141, 31));
        label_168->setStyleSheet(QString::fromUtf8(""));
        spinBox = new QSpinBox(frame_6);
        spinBox->setObjectName("spinBox");
        spinBox->setGeometry(QRect(10, 300, 101, 29));
        label_156 = new QLabel(tab_6);
        label_156->setObjectName("label_156");
        label_156->setGeometry(QRect(288, 70, 231, 51));
        QFont font3;
        font3.setBold(true);
        font3.setItalic(true);
        label_156->setFont(font3);
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
        stat1_2->setGeometry(QRect(950, 130, 161, 61));
        stat2_2 = new QPushButton(tab_7);
        stat2_2->setObjectName("stat2_2");
        stat2_2->setGeometry(QRect(950, 360, 161, 71));
        aceuille_2->addTab(tab_7, QString());

        verticalLayout_32->addWidget(aceuille_2);


        verticalLayout_31->addLayout(verticalLayout_32);


        horizontalLayout_7->addLayout(verticalLayout_31);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 1501, 25));
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
        comboBox_tri_2->setItemText(3, QCoreApplication::translate("MainWindow", "Date d'ajout", nullptr));
        comboBox_tri_2->setItemText(4, QCoreApplication::translate("MainWindow", "Type des projets", nullptr));
        comboBox_tri_2->setItemText(5, QCoreApplication::translate("MainWindow", "Cat\303\251gorie", nullptr));

        supprimer->setText(QCoreApplication::translate("MainWindow", "Supprimer", nullptr));
        label_158->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-size:12pt; font-weight:700; color:#ffffff;\">Recherche contracteur :</span></p></body></html>", nullptr));
        id_rech_2->setPlaceholderText(QCoreApplication::translate("MainWindow", "ID", nullptr));
        chercher_2->setText(QCoreApplication::translate("MainWindow", "Chercher", nullptr));
        modifier2->setText(QCoreApplication::translate("MainWindow", "Modifier", nullptr));
        pdf_2->setText(QCoreApplication::translate("MainWindow", "exportation pdf", nullptr));
        pushButton->setText(QCoreApplication::translate("MainWindow", " Employ\303\251s", nullptr));
        pushButton_4->setText(QCoreApplication::translate("MainWindow", " Clients", nullptr));
        pushButton_3->setText(QCoreApplication::translate("MainWindow", " Projets", nullptr));
        pushButton_2->setText(QCoreApplication::translate("MainWindow", " Ressources", nullptr));
        pushButton_5->setText(QCoreApplication::translate("MainWindow", " Contrats", nullptr));
        pushButton_6->setText(QCoreApplication::translate("MainWindow", " Contracteurs", nullptr));
        label->setText(QString());
        label_146->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-weight:700;\">Id contracteur:</span></p></body></html>", nullptr));
        lineEdit_2->setPlaceholderText(QCoreApplication::translate("MainWindow", "Nom", nullptr));
#if QT_CONFIG(tooltip)
        lineEdit_3->setToolTip(QCoreApplication::translate("MainWindow", "<html><head/><body><p>dhzbebcl</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(whatsthis)
        lineEdit_3->setWhatsThis(QCoreApplication::translate("MainWindow", "<html><head/><body><p>vj j;</p></body></html>", nullptr));
#endif // QT_CONFIG(whatsthis)
        lineEdit_3->setPlaceholderText(QCoreApplication::translate("MainWindow", "ID", nullptr));
        label_149->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-weight:700;\">Nom contracteur :</span></p></body></html>", nullptr));
        label_150->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-weight:700;\">Domaine :</span></p></body></html>", nullptr));
        label_154->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-weight:700;\">Nombre des projets realis\303\251es :</span></p></body></html>", nullptr));
        comboBox->setItemText(0, QCoreApplication::translate("MainWindow", "Cat\303\251gorie", nullptr));
        comboBox->setItemText(1, QCoreApplication::translate("MainWindow", "Eclairage", nullptr));
        comboBox->setItemText(2, QCoreApplication::translate("MainWindow", "Technologie", nullptr));
        comboBox->setItemText(3, QCoreApplication::translate("MainWindow", "Papeterie", nullptr));
        comboBox->setItemText(4, QCoreApplication::translate("MainWindow", "Nettoyage", nullptr));
        comboBox->setItemText(5, QCoreApplication::translate("MainWindow", "Mobilier", nullptr));
        comboBox->setItemText(6, QCoreApplication::translate("MainWindow", "Electrique", nullptr));
        comboBox->setItemText(7, QCoreApplication::translate("MainWindow", "Outils", nullptr));

        comboBox->setPlaceholderText(QCoreApplication::translate("MainWindow", "Domaine", nullptr));
        label_155->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-size:7pt; font-weight:700;\">Num\303\251ro de telephone :</span></p></body></html>", nullptr));
        lineEdit_7->setPlaceholderText(QCoreApplication::translate("MainWindow", "+*** ** *** ***", nullptr));
        modifier->setText(QCoreApplication::translate("MainWindow", "Modifier", nullptr));
        annuler->setText(QCoreApplication::translate("MainWindow", "Annuler", nullptr));
        ajouter->setText(QCoreApplication::translate("MainWindow", "Ajouter", nullptr));
        lineEdit_13->setPlaceholderText(QCoreApplication::translate("MainWindow", "Prenom", nullptr));
        label_168->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-size:7pt; font-weight:700;\">Prenom contracteur :</span></p></body></html>", nullptr));
        label_156->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p align=\"center\"><span style=\" font-style:normal;\">Ajout Contracteur</span></p><p align=\"center\"><br/></p></body></html>", nullptr));
        aceuille_2->setTabText(aceuille_2->indexOf(tab_6), QCoreApplication::translate("MainWindow", "Consulter", nullptr));
        stat1_2->setText(QCoreApplication::translate("MainWindow", "statistique sexe", nullptr));
        stat2_2->setText(QCoreApplication::translate("MainWindow", "statistique conge", nullptr));
        aceuille_2->setTabText(aceuille_2->indexOf(tab_7), QCoreApplication::translate("MainWindow", "Statistique", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
