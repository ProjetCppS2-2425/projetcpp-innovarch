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
#include <QtWidgets/QListView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableView>
#include <QtWidgets/QTreeView>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *contracteur_2;
    QWidget *layoutWidget1;
    QHBoxLayout *horizontalLayout_7;
    QVBoxLayout *verticalLayout_31;
    QVBoxLayout *verticalLayout_32;
    QTabWidget *contracteur;
    QWidget *tab_6;
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
    QLineEdit *lineEdit_2contracteur;
    QLineEdit *lineEdit_3contracteur;
    QLabel *label_149;
    QLabel *label_150;
    QLabel *label_154;
    QComboBox *comboBoxcontracteur;
    QLabel *label_155;
    QLineEdit *lineEdit_7contracteur;
    QPushButton *modifiercontracteur;
    QPushButton *annulercontracteur;
    QPushButton *ajoutercontracteur;
    QLineEdit *lineEdit_13contracteur;
    QLabel *label_168;
    QSpinBox *spinBoxcontracteur;
    QLineEdit *lineEdit_4contracteur;
    QLabel *label_151;
    QLineEdit *lineEdit_5contracteur;
    QLabel *label_152;
    QLabel *label_156;
    QTabWidget *tabWidgetcontracteur;
    QWidget *recherche;
    QWidget *widget_7;
    QComboBox *comboBox_tri_2contracteur;
    QPushButton *supprimercontracteur;
    QLabel *label_158;
    QLineEdit *id_rech_2contracteur;
    QPushButton *chercher_2contracteur;
    QTableView *tableView_2contracteur;
    QPushButton *pdf_2contracteur;
    QComboBox *comboBox_2contracteur;
    QWidget *statistics;
    QWidget *widget_8;
    QComboBox *comboBox_stat_3;
    QLabel *label_159;
    QPushButton *pdf_3contracteur;
    QGraphicsView *graphicsViewcontracteur;
    QPushButton *statbuttcontracteur;
    QWidget *calendrier;
    QWidget *widget;
    QTableView *tableViewcontracteur;
    QPushButton *affichertreecontracteur;
    QTreeView *treeViewcontracteur;
    QWidget *todolist;
    QWidget *widget_2;
    QListView *taskslistcontracteur;
    QPushButton *addtaskcontracteur;
    QPushButton *completedtaskcontracteur;
    QPushButton *rmtaskcontracteur;
    QLineEdit *tasktextcontracteur;
    QTableView *contractorlisttablecontracteur;
    QLabel *label_161;
    QLabel *label_162;
    QLabel *label_164;
    QWidget *architect;
    QWidget *widget_3;
    QListView *achitectviewcontracteur;
    QListView *presenceviewcontracteur;
    QLabel *label_160;
    QLabel *label_163;
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
        contracteur_2 = new QWidget(MainWindow);
        contracteur_2->setObjectName("contracteur_2");
        layoutWidget1 = new QWidget(contracteur_2);
        layoutWidget1->setObjectName("layoutWidget1");
        layoutWidget1->setGeometry(QRect(0, -30, 1461, 769));
        horizontalLayout_7 = new QHBoxLayout(layoutWidget1);
        horizontalLayout_7->setObjectName("horizontalLayout_7");
        horizontalLayout_7->setContentsMargins(0, 0, 0, 0);
        verticalLayout_31 = new QVBoxLayout();
        verticalLayout_31->setObjectName("verticalLayout_31");
        verticalLayout_32 = new QVBoxLayout();
        verticalLayout_32->setObjectName("verticalLayout_32");
        contracteur = new QTabWidget(layoutWidget1);
        contracteur->setObjectName("contracteur");
        contracteur->setMinimumSize(QSize(300, 300));
        contracteur->setAutoFillBackground(false);
        contracteur->setStyleSheet(QString::fromUtf8("background-color:#F8EDEB;"));
        tab_6 = new QWidget();
        tab_6->setObjectName("tab_6");
        frame = new QFrame(tab_6);
        frame->setObjectName("frame");
        frame->setGeometry(QRect(0, 0, 191, 741));
        frame->setStyleSheet(QString::fromUtf8("background-color: #4E1764"));
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
"}"));
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
"}"));
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
"}"));
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
"}"));
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
"}"));
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
"}"));
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
        label_146 = new QLabel(frame_6);
        label_146->setObjectName("label_146");
        label_146->setGeometry(QRect(2, 10, 121, 31));
        label_146->setStyleSheet(QString::fromUtf8(""));
        lineEdit_2contracteur = new QLineEdit(frame_6);
        lineEdit_2contracteur->setObjectName("lineEdit_2contracteur");
        lineEdit_2contracteur->setGeometry(QRect(10, 120, 113, 26));
        lineEdit_2contracteur->setStyleSheet(QString::fromUtf8("QLineEdit {\n"
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
        lineEdit_3contracteur = new QLineEdit(frame_6);
        lineEdit_3contracteur->setObjectName("lineEdit_3contracteur");
        lineEdit_3contracteur->setGeometry(QRect(10, 50, 113, 26));
        lineEdit_3contracteur->setStyleSheet(QString::fromUtf8("QLineEdit {\n"
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
        label_154->setGeometry(QRect(10, 330, 221, 31));
        label_154->setStyleSheet(QString::fromUtf8(""));
        comboBoxcontracteur = new QComboBox(frame_6);
        comboBoxcontracteur->addItem(QString());
        comboBoxcontracteur->addItem(QString());
        comboBoxcontracteur->addItem(QString());
        comboBoxcontracteur->addItem(QString());
        comboBoxcontracteur->addItem(QString());
        comboBoxcontracteur->addItem(QString());
        comboBoxcontracteur->addItem(QString());
        comboBoxcontracteur->setObjectName("comboBoxcontracteur");
        comboBoxcontracteur->setGeometry(QRect(10, 190, 141, 32));
        comboBoxcontracteur->setStyleSheet(QString::fromUtf8("\n"
"    border: 2px solid #4e1764;  /* Default thicker border */\n"
"    border-radius: 5px;\n"
"    background-color: white;  /* Ensure background stays white */\n"
"	\n"
"	color: rgb(0, 0, 0);\n"
"\n"
"\n"
"\n"
""));
        label_155 = new QLabel(frame_6);
        label_155->setObjectName("label_155");
        label_155->setGeometry(QRect(150, 148, 151, 31));
        label_155->setStyleSheet(QString::fromUtf8(""));
        lineEdit_7contracteur = new QLineEdit(frame_6);
        lineEdit_7contracteur->setObjectName("lineEdit_7contracteur");
        lineEdit_7contracteur->setGeometry(QRect(160, 190, 111, 31));
        lineEdit_7contracteur->setStyleSheet(QString::fromUtf8("QLineEdit {\n"
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
        modifiercontracteur = new QPushButton(frame_6);
        modifiercontracteur->setObjectName("modifiercontracteur");
        modifiercontracteur->setGeometry(QRect(111, 493, 85, 31));
        modifiercontracteur->setStyleSheet(QString::fromUtf8("QPushButton#modifier {\n"
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
        annulercontracteur = new QPushButton(frame_6);
        annulercontracteur->setObjectName("annulercontracteur");
        annulercontracteur->setGeometry(QRect(20, 493, 81, 31));
        annulercontracteur->setStyleSheet(QString::fromUtf8("QPushButton#annuler {\n"
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
        ajoutercontracteur = new QPushButton(frame_6);
        ajoutercontracteur->setObjectName("ajoutercontracteur");
        ajoutercontracteur->setGeometry(QRect(208, 493, 78, 31));
        ajoutercontracteur->setStyleSheet(QString::fromUtf8("QPushButton#ajouter {\n"
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
        lineEdit_13contracteur = new QLineEdit(frame_6);
        lineEdit_13contracteur->setObjectName("lineEdit_13contracteur");
        lineEdit_13contracteur->setGeometry(QRect(160, 120, 113, 26));
        lineEdit_13contracteur->setStyleSheet(QString::fromUtf8("QLineEdit {\n"
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
        label_168->setGeometry(QRect(150, 80, 141, 31));
        label_168->setStyleSheet(QString::fromUtf8(""));
        spinBoxcontracteur = new QSpinBox(frame_6);
        spinBoxcontracteur->setObjectName("spinBoxcontracteur");
        spinBoxcontracteur->setGeometry(QRect(10, 370, 51, 41));
        spinBoxcontracteur->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);\n"
"font: 9pt \"Segoe UI\";\n"
"color: rgb(0, 0, 0);"));
        lineEdit_4contracteur = new QLineEdit(frame_6);
        lineEdit_4contracteur->setObjectName("lineEdit_4contracteur");
        lineEdit_4contracteur->setGeometry(QRect(10, 270, 113, 26));
        lineEdit_4contracteur->setStyleSheet(QString::fromUtf8("QLineEdit {\n"
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
        label_151 = new QLabel(frame_6);
        label_151->setObjectName("label_151");
        label_151->setGeometry(QRect(4, 230, 81, 31));
        label_151->setStyleSheet(QString::fromUtf8(""));
        lineEdit_5contracteur = new QLineEdit(frame_6);
        lineEdit_5contracteur->setObjectName("lineEdit_5contracteur");
        lineEdit_5contracteur->setGeometry(QRect(160, 270, 113, 26));
        lineEdit_5contracteur->setStyleSheet(QString::fromUtf8("QLineEdit {\n"
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
        label_152 = new QLabel(frame_6);
        label_152->setObjectName("label_152");
        label_152->setGeometry(QRect(150, 230, 141, 31));
        label_152->setStyleSheet(QString::fromUtf8(""));
        label_146->raise();
        lineEdit_2contracteur->raise();
        label_149->raise();
        label_150->raise();
        label_154->raise();
        comboBoxcontracteur->raise();
        label_155->raise();
        lineEdit_7contracteur->raise();
        modifiercontracteur->raise();
        annulercontracteur->raise();
        ajoutercontracteur->raise();
        lineEdit_13contracteur->raise();
        label_168->raise();
        spinBoxcontracteur->raise();
        lineEdit_4contracteur->raise();
        label_151->raise();
        lineEdit_5contracteur->raise();
        label_152->raise();
        lineEdit_3contracteur->raise();
        label_156 = new QLabel(tab_6);
        label_156->setObjectName("label_156");
        label_156->setGeometry(QRect(288, 70, 231, 51));
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
        tabWidgetcontracteur = new QTabWidget(tab_6);
        tabWidgetcontracteur->setObjectName("tabWidgetcontracteur");
        tabWidgetcontracteur->setGeometry(QRect(610, 100, 771, 551));
        tabWidgetcontracteur->setStyleSheet(QString::fromUtf8("background-color: rgb(231, 219, 209);\n"
"color: rgb(0, 0, 0);"));
        recherche = new QWidget();
        recherche->setObjectName("recherche");
        widget_7 = new QWidget(recherche);
        widget_7->setObjectName("widget_7");
        widget_7->setGeometry(QRect(0, -10, 811, 551));
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
        comboBox_tri_2contracteur = new QComboBox(widget_7);
        comboBox_tri_2contracteur->addItem(QString());
        comboBox_tri_2contracteur->addItem(QString());
        comboBox_tri_2contracteur->addItem(QString());
        comboBox_tri_2contracteur->addItem(QString());
        comboBox_tri_2contracteur->addItem(QString());
        comboBox_tri_2contracteur->setObjectName("comboBox_tri_2contracteur");
        comboBox_tri_2contracteur->setGeometry(QRect(540, 22, 141, 28));
        comboBox_tri_2contracteur->setAutoFillBackground(false);
        comboBox_tri_2contracteur->setStyleSheet(QString::fromUtf8("\n"
"\n"
"    border: 2px solid #9f86c0;  /* Default thicker border */\n"
"    border-radius: 5px;\n"
"    background-color: white;  /* Ensure background stays white */\n"
"font: 9pt \"Segoe UI\";\n"
"color: rgb(0, 0, 0);\n"
"\n"
"\n"
""));
        comboBox_tri_2contracteur->setDuplicatesEnabled(false);
        comboBox_tri_2contracteur->setFrame(true);
        supprimercontracteur = new QPushButton(widget_7);
        supprimercontracteur->setObjectName("supprimercontracteur");
        supprimercontracteur->setGeometry(QRect(460, 450, 181, 41));
        supprimercontracteur->setStyleSheet(QString::fromUtf8("QPushButton#supprimer {\n"
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
        label_158->setGeometry(QRect(10, 20, 191, 31));
        QFont font3;
        font3.setFamilies({QString::fromUtf8("Roboto")});
        label_158->setFont(font3);
        id_rech_2contracteur = new QLineEdit(widget_7);
        id_rech_2contracteur->setObjectName("id_rech_2contracteur");
        id_rech_2contracteur->setGeometry(QRect(290, 20, 141, 31));
        id_rech_2contracteur->setStyleSheet(QString::fromUtf8("QLineEdit {\n"
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
        chercher_2contracteur = new QPushButton(widget_7);
        chercher_2contracteur->setObjectName("chercher_2contracteur");
        chercher_2contracteur->setGeometry(QRect(440, 20, 91, 31));
        chercher_2contracteur->setStyleSheet(QString::fromUtf8("QPushButton#chercher_2 {\n"
"    background-color: rgb(255, 255, 255);\n"
"	border: 2px solid #9f86c0 ;/* Default thicker border */\n"
"    border-radius: 5px;\n"
"}"));
        tableView_2contracteur = new QTableView(widget_7);
        tableView_2contracteur->setObjectName("tableView_2contracteur");
        tableView_2contracteur->setGeometry(QRect(20, 70, 621, 371));
        tableView_2contracteur->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);\n"
"font: 9pt \"Segoe UI\";\n"
"color: rgb(0, 0, 0);"));
        pdf_2contracteur = new QPushButton(widget_7);
        pdf_2contracteur->setObjectName("pdf_2contracteur");
        pdf_2contracteur->setGeometry(QRect(20, 450, 161, 41));
        pdf_2contracteur->setStyleSheet(QString::fromUtf8("QPushButton#pdf_2 {\n"
"    background-color: rgb(255, 255, 255);\n"
"	border: 2px solid #9f86c0 ;/* Default thicker border */\n"
"    border-radius: 5px;\n"
"}"));
        comboBox_2contracteur = new QComboBox(widget_7);
        comboBox_2contracteur->addItem(QString());
        comboBox_2contracteur->addItem(QString());
        comboBox_2contracteur->addItem(QString());
        comboBox_2contracteur->addItem(QString());
        comboBox_2contracteur->setObjectName("comboBox_2contracteur");
        comboBox_2contracteur->setGeometry(QRect(200, 22, 82, 28));
        comboBox_2contracteur->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);\n"
"font: 9pt \"Segoe UI\";\n"
"color: rgb(0, 0, 0);"));
        comboBox_tri_2contracteur->raise();
        supprimercontracteur->raise();
        label_158->raise();
        id_rech_2contracteur->raise();
        chercher_2contracteur->raise();
        pdf_2contracteur->raise();
        comboBox_2contracteur->raise();
        tableView_2contracteur->raise();
        tabWidgetcontracteur->addTab(recherche, QString());
        statistics = new QWidget();
        statistics->setObjectName("statistics");
        widget_8 = new QWidget(statistics);
        widget_8->setObjectName("widget_8");
        widget_8->setGeometry(QRect(0, -10, 781, 531));
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
        comboBox_stat_3 = new QComboBox(widget_8);
        comboBox_stat_3->addItem(QString());
        comboBox_stat_3->setObjectName("comboBox_stat_3");
        comboBox_stat_3->setGeometry(QRect(200, 20, 141, 28));
        comboBox_stat_3->setAutoFillBackground(false);
        comboBox_stat_3->setStyleSheet(QString::fromUtf8("\n"
"\n"
"    border: 2px solid #9f86c0;  /* Default thicker border */\n"
"    border-radius: 5px;\n"
"    background-color: white;  /* Ensure background stays white */\n"
"font: 9pt \"Segoe UI\";\n"
"color: rgb(0, 0, 0);\n"
"\n"
"\n"
""));
        comboBox_stat_3->setDuplicatesEnabled(false);
        comboBox_stat_3->setFrame(true);
        label_159 = new QLabel(widget_8);
        label_159->setObjectName("label_159");
        label_159->setGeometry(QRect(10, 20, 191, 31));
        label_159->setFont(font3);
        pdf_3contracteur = new QPushButton(widget_8);
        pdf_3contracteur->setObjectName("pdf_3contracteur");
        pdf_3contracteur->setGeometry(QRect(20, 470, 161, 41));
        pdf_3contracteur->setStyleSheet(QString::fromUtf8("QPushButton#pdf_2 {\n"
"    background-color: rgb(255, 255, 255);\n"
"	border: 2px solid #9f86c0 ;/* Default thicker border */\n"
"    border-radius: 5px;\n"
"}"));
        graphicsViewcontracteur = new QGraphicsView(widget_8);
        graphicsViewcontracteur->setObjectName("graphicsViewcontracteur");
        graphicsViewcontracteur->setGeometry(QRect(5, 51, 761, 411));
        statbuttcontracteur = new QPushButton(widget_8);
        statbuttcontracteur->setObjectName("statbuttcontracteur");
        statbuttcontracteur->setGeometry(QRect(590, 470, 161, 41));
        statbuttcontracteur->setStyleSheet(QString::fromUtf8("QPushButton#pdf_2 {\n"
"    background-color: rgb(255, 255, 255);\n"
"	border: 2px solid #9f86c0 ;/* Default thicker border */\n"
"    border-radius: 5px;\n"
"}"));
        comboBox_stat_3->raise();
        label_159->raise();
        graphicsViewcontracteur->raise();
        statbuttcontracteur->raise();
        pdf_3contracteur->raise();
        tabWidgetcontracteur->addTab(statistics, QString());
        calendrier = new QWidget();
        calendrier->setObjectName("calendrier");
        widget = new QWidget(calendrier);
        widget->setObjectName("widget");
        widget->setGeometry(QRect(-10, -10, 801, 531));
        tableViewcontracteur = new QTableView(widget);
        tableViewcontracteur->setObjectName("tableViewcontracteur");
        tableViewcontracteur->setGeometry(QRect(470, 60, 256, 411));
        tableViewcontracteur->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);\n"
"font: 9pt \"Segoe UI\";\n"
"color: rgb(0, 0, 0);"));
        affichertreecontracteur = new QPushButton(widget);
        affichertreecontracteur->setObjectName("affichertreecontracteur");
        affichertreecontracteur->setGeometry(QRect(160, 460, 83, 29));
        affichertreecontracteur->setStyleSheet(QString::fromUtf8("QPushButton#pdf_2 {\n"
"    background-color: rgb(255, 255, 255);\n"
"	border: 2px solid #9f86c0 ;/* Default thicker border */\n"
"    border-radius: 5px;\n"
"}"));
        treeViewcontracteur = new QTreeView(widget);
        treeViewcontracteur->setObjectName("treeViewcontracteur");
        treeViewcontracteur->setGeometry(QRect(70, 60, 256, 361));
        tabWidgetcontracteur->addTab(calendrier, QString());
        todolist = new QWidget();
        todolist->setObjectName("todolist");
        widget_2 = new QWidget(todolist);
        widget_2->setObjectName("widget_2");
        widget_2->setGeometry(QRect(-11, -21, 791, 551));
        taskslistcontracteur = new QListView(widget_2);
        taskslistcontracteur->setObjectName("taskslistcontracteur");
        taskslistcontracteur->setGeometry(QRect(60, 90, 256, 271));
        taskslistcontracteur->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);\n"
"font: 9pt \"Segoe UI\";\n"
"color: rgb(0, 0, 0);"));
        addtaskcontracteur = new QPushButton(widget_2);
        addtaskcontracteur->setObjectName("addtaskcontracteur");
        addtaskcontracteur->setGeometry(QRect(60, 450, 111, 29));
        addtaskcontracteur->setStyleSheet(QString::fromUtf8("QPushButton#pdf_2 {\n"
"    background-color: rgb(255, 255, 255);\n"
"	border: 2px solid #9f86c0 ;/* Default thicker border */\n"
"    border-radius: 5px;\n"
"}"));
        completedtaskcontracteur = new QPushButton(widget_2);
        completedtaskcontracteur->setObjectName("completedtaskcontracteur");
        completedtaskcontracteur->setGeometry(QRect(180, 450, 141, 29));
        rmtaskcontracteur = new QPushButton(widget_2);
        rmtaskcontracteur->setObjectName("rmtaskcontracteur");
        rmtaskcontracteur->setGeometry(QRect(330, 450, 151, 29));
        tasktextcontracteur = new QLineEdit(widget_2);
        tasktextcontracteur->setObjectName("tasktextcontracteur");
        tasktextcontracteur->setGeometry(QRect(60, 380, 161, 28));
        tasktextcontracteur->setStyleSheet(QString::fromUtf8("QLineEdit {\n"
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
        contractorlisttablecontracteur = new QTableView(widget_2);
        contractorlisttablecontracteur->setObjectName("contractorlisttablecontracteur");
        contractorlisttablecontracteur->setGeometry(QRect(390, 90, 271, 271));
        contractorlisttablecontracteur->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);\n"
"font: 9pt \"Segoe UI\";\n"
"color: rgb(0, 0, 0);"));
        label_161 = new QLabel(todolist);
        label_161->setObjectName("label_161");
        label_161->setGeometry(QRect(380, 30, 191, 31));
        label_161->setFont(font3);
        label_162 = new QLabel(todolist);
        label_162->setObjectName("label_162");
        label_162->setGeometry(QRect(50, 30, 191, 31));
        label_162->setFont(font3);
        label_164 = new QLabel(todolist);
        label_164->setObjectName("label_164");
        label_164->setGeometry(QRect(220, 357, 191, 31));
        label_164->setFont(font3);
        tabWidgetcontracteur->addTab(todolist, QString());
        architect = new QWidget();
        architect->setObjectName("architect");
        widget_3 = new QWidget(architect);
        widget_3->setObjectName("widget_3");
        widget_3->setGeometry(QRect(10, -10, 791, 551));
        achitectviewcontracteur = new QListView(widget_3);
        achitectviewcontracteur->setObjectName("achitectviewcontracteur");
        achitectviewcontracteur->setGeometry(QRect(30, 70, 281, 431));
        achitectviewcontracteur->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);\n"
"font: 9pt \"Segoe UI\";\n"
"color: rgb(0, 0, 0);"));
        presenceviewcontracteur = new QListView(widget_3);
        presenceviewcontracteur->setObjectName("presenceviewcontracteur");
        presenceviewcontracteur->setGeometry(QRect(340, 70, 281, 431));
        presenceviewcontracteur->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);\n"
"font: 9pt \"Segoe UI\";\n"
"color: rgb(0, 0, 0);"));
        label_160 = new QLabel(widget_3);
        label_160->setObjectName("label_160");
        label_160->setGeometry(QRect(30, 30, 191, 31));
        label_160->setFont(font3);
        label_163 = new QLabel(widget_3);
        label_163->setObjectName("label_163");
        label_163->setGeometry(QRect(340, 30, 231, 31));
        label_163->setFont(font3);
        tabWidgetcontracteur->addTab(architect, QString());
        contracteur->addTab(tab_6, QString());
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
        contracteur->addTab(tab_7, QString());

        verticalLayout_32->addWidget(contracteur);


        verticalLayout_31->addLayout(verticalLayout_32);


        horizontalLayout_7->addLayout(verticalLayout_31);

        MainWindow->setCentralWidget(contracteur_2);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 1501, 25));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);
        QObject::connect(tabWidgetcontracteur, SIGNAL(currentChanged(int)), MainWindow, SLOT(on_tabWidget_currentChanged(int)));

        contracteur->setCurrentIndex(0);
        tabWidgetcontracteur->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        label->setText(QString());
        pushButton->setText(QCoreApplication::translate("MainWindow", " Employ\303\251s", nullptr));
        pushButton_4->setText(QCoreApplication::translate("MainWindow", " Clients", nullptr));
        pushButton_3->setText(QCoreApplication::translate("MainWindow", " Projets", nullptr));
        pushButton_2->setText(QCoreApplication::translate("MainWindow", " Ressources", nullptr));
        pushButton_5->setText(QCoreApplication::translate("MainWindow", " Contrats", nullptr));
        pushButton_6->setText(QCoreApplication::translate("MainWindow", " Contracteurs", nullptr));
        label_146->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-weight:700;\">Id contracteur:</span></p></body></html>", nullptr));
        lineEdit_2contracteur->setPlaceholderText(QCoreApplication::translate("MainWindow", "Nom", nullptr));
#if QT_CONFIG(tooltip)
        lineEdit_3contracteur->setToolTip(QCoreApplication::translate("MainWindow", "<html><head/><body><p>dhzbebcl</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(whatsthis)
        lineEdit_3contracteur->setWhatsThis(QCoreApplication::translate("MainWindow", "<html><head/><body><p>vj j;</p></body></html>", nullptr));
#endif // QT_CONFIG(whatsthis)
        lineEdit_3contracteur->setPlaceholderText(QCoreApplication::translate("MainWindow", "ID", nullptr));
        label_149->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-weight:700;\">Nom contracteur :</span></p></body></html>", nullptr));
        label_150->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-weight:700;\">Domaine :</span></p></body></html>", nullptr));
        label_154->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-weight:700;\">Nombre des projets realis\303\251es :</span></p></body></html>", nullptr));
        comboBoxcontracteur->setItemText(0, QCoreApplication::translate("MainWindow", "Eclairage", nullptr));
        comboBoxcontracteur->setItemText(1, QCoreApplication::translate("MainWindow", "Technologie", nullptr));
        comboBoxcontracteur->setItemText(2, QCoreApplication::translate("MainWindow", "Papeterie", nullptr));
        comboBoxcontracteur->setItemText(3, QCoreApplication::translate("MainWindow", "Nettoyage", nullptr));
        comboBoxcontracteur->setItemText(4, QCoreApplication::translate("MainWindow", "Mobilier", nullptr));
        comboBoxcontracteur->setItemText(5, QCoreApplication::translate("MainWindow", "Electrique", nullptr));
        comboBoxcontracteur->setItemText(6, QCoreApplication::translate("MainWindow", "Outils", nullptr));

        comboBoxcontracteur->setPlaceholderText(QCoreApplication::translate("MainWindow", "Domaine", nullptr));
        label_155->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-size:8pt; font-weight:700;\">Num\303\251ro de telephone :</span></p></body></html>", nullptr));
        lineEdit_7contracteur->setPlaceholderText(QCoreApplication::translate("MainWindow", "+*** ** *** ***", nullptr));
        modifiercontracteur->setText(QCoreApplication::translate("MainWindow", "Modifier", nullptr));
        annulercontracteur->setText(QCoreApplication::translate("MainWindow", "Annuler", nullptr));
        ajoutercontracteur->setText(QCoreApplication::translate("MainWindow", "Ajouter", nullptr));
        lineEdit_13contracteur->setPlaceholderText(QCoreApplication::translate("MainWindow", "Prenom", nullptr));
        label_168->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-size:8pt; font-weight:700;\">Prenom contracteur :</span></p></body></html>", nullptr));
        lineEdit_4contracteur->setPlaceholderText(QCoreApplication::translate("MainWindow", "Adresse", nullptr));
        label_151->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-weight:700;\">Adresse :</span></p></body></html>", nullptr));
        lineEdit_5contracteur->setPlaceholderText(QCoreApplication::translate("MainWindow", "Email", nullptr));
        label_152->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-weight:700;\">Email :</span></p></body></html>", nullptr));
        label_156->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p align=\"center\"><span style=\" font-style:normal;\">Ajout Contracteur</span></p><p align=\"center\"><br/></p></body></html>", nullptr));
        comboBox_tri_2contracteur->setItemText(0, QCoreApplication::translate("MainWindow", "Trier selon ", nullptr));
        comboBox_tri_2contracteur->setItemText(1, QCoreApplication::translate("MainWindow", "Domaine", nullptr));
        comboBox_tri_2contracteur->setItemText(2, QCoreApplication::translate("MainWindow", "Id d\303\251croissant ", nullptr));
        comboBox_tri_2contracteur->setItemText(3, QCoreApplication::translate("MainWindow", "Id croissant", nullptr));
        comboBox_tri_2contracteur->setItemText(4, QCoreApplication::translate("MainWindow", "Nom", nullptr));

        supprimercontracteur->setText(QCoreApplication::translate("MainWindow", "Supprimer", nullptr));
        label_158->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-size:9pt; font-weight:700;\">Recherche contracteur :</span></p></body></html>", nullptr));
        id_rech_2contracteur->setPlaceholderText(QCoreApplication::translate("MainWindow", "Recherche", nullptr));
        chercher_2contracteur->setText(QCoreApplication::translate("MainWindow", "Chercher", nullptr));
        pdf_2contracteur->setText(QCoreApplication::translate("MainWindow", "Exportation PDF", nullptr));
        comboBox_2contracteur->setItemText(0, QCoreApplication::translate("MainWindow", "ID", nullptr));
        comboBox_2contracteur->setItemText(1, QCoreApplication::translate("MainWindow", "Date d'ajout", nullptr));
        comboBox_2contracteur->setItemText(2, QCoreApplication::translate("MainWindow", "Domaine", nullptr));
        comboBox_2contracteur->setItemText(3, QCoreApplication::translate("MainWindow", "Nom", nullptr));

        tabWidgetcontracteur->setTabText(tabWidgetcontracteur->indexOf(recherche), QCoreApplication::translate("MainWindow", "Recherche Et Tri", nullptr));
        comboBox_stat_3->setItemText(0, QCoreApplication::translate("MainWindow", "Type des projets", nullptr));

        label_159->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-size:9pt; font-weight:700;\">Statistique bas\303\251e sur :</span></p></body></html>", nullptr));
        pdf_3contracteur->setText(QCoreApplication::translate("MainWindow", "exportation pdf", nullptr));
        statbuttcontracteur->setText(QCoreApplication::translate("MainWindow", "Generer Statistiques", nullptr));
        tabWidgetcontracteur->setTabText(tabWidgetcontracteur->indexOf(statistics), QCoreApplication::translate("MainWindow", "Statistiques", nullptr));
        affichertreecontracteur->setText(QCoreApplication::translate("MainWindow", "Afficher", nullptr));
        tabWidgetcontracteur->setTabText(tabWidgetcontracteur->indexOf(calendrier), QCoreApplication::translate("MainWindow", "Informations", nullptr));
        addtaskcontracteur->setText(QCoreApplication::translate("MainWindow", "Ajout de tache", nullptr));
        completedtaskcontracteur->setText(QCoreApplication::translate("MainWindow", "Marquer comme fait", nullptr));
        rmtaskcontracteur->setText(QCoreApplication::translate("MainWindow", "Suppression de tache", nullptr));
        tasktextcontracteur->setInputMask(QString());
        tasktextcontracteur->setText(QString());
        tasktextcontracteur->setPlaceholderText(QCoreApplication::translate("MainWindow", "Tache", nullptr));
        label_161->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-weight:700;\">Liste des contracteurs :</span></p></body></html>", nullptr));
        label_162->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-weight:700;\">Taches \303\240 faire :</span></p></body></html>", nullptr));
        label_164->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-weight:700;\">Tache \303\240 ajouter</span></p></body></html>", nullptr));
        tabWidgetcontracteur->setTabText(tabWidgetcontracteur->indexOf(todolist), QCoreApplication::translate("MainWindow", "To Do List", nullptr));
        label_160->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-weight:700;\">Liste des architects :</span></p></body></html>", nullptr));
        label_163->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-weight:700;\">Liste des architects presents :</span></p></body></html>", nullptr));
        tabWidgetcontracteur->setTabText(tabWidgetcontracteur->indexOf(architect), QCoreApplication::translate("MainWindow", "Pr\303\251sence", nullptr));
        contracteur->setTabText(contracteur->indexOf(tab_6), QCoreApplication::translate("MainWindow", "Consulter", nullptr));
        stat1_2->setText(QCoreApplication::translate("MainWindow", "statistique sexe", nullptr));
        stat2_2->setText(QCoreApplication::translate("MainWindow", "statistique conge", nullptr));
        contracteur->setTabText(contracteur->indexOf(tab_7), QCoreApplication::translate("MainWindow", "Statistique", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
